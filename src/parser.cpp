#include "parser.h"

static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::string item;
    std::istringstream ss(s);
    while (std::getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

bool bookshelf::Parser::parseLibsFile(const std::string& filename){
    std::ifstream libsFile(filename);
    if(!libsFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }
    else{
        std::cout << "== Reading library file from PYTHON dumping out ==\n";
    }

    std::string line;

    double a, b, c, d;
    libsFile >> a >> b >> c >> d;
    this->_placement.setBoundaryLeft(a);
    this->_placement.setBoundaryBottom(b);
    this->_placement.setBoundaryRight(c);
    this->_placement.setBoundaryTop(d);

    while(1){
        std::string libName;
        double libArea;
        int numPins = 0;
        
        if(!(libsFile >> libName >> libArea >> numPins)){
            break;
        }        
        Library* lib = new Library(libName, libArea);

        bool hasD = false;
        bool hasCLK = false;
        for(int i=0; i<numPins; ++i){
            std::pair<std::string, bool> pin;
            if(!(libsFile >> pin.first >> line)){
                std::cerr << "Something goes wrong in dumping libs file...\n";
            }
            pin.second = (line=="INPUT")? INPUT : OUTPUT;
            if((pin.first=="D")*(pin.second)){hasD = true;}
            if((pin.first=="CLK")*(pin.second)){hasCLK = true;}
            lib->addPinDef(pin);
        }
        lib->setFF(hasD*hasCLK);
        this->_placement.addLibrary(lib);

        if(lib->isFF()){std::cout << "FF: " << lib->name() << "\n";}
    }

    std::cout << "Reading " << filename << " done!\n";
    return true;
}

bool bookshelf::Parser::parseCSVFile(const std::string& filename){
    std::ifstream csvFile(filename);
    if(!csvFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }
    else{
        std::cout << "== Reading CSV file ==\n";
    }
    
    std::string line;
    std::getline(csvFile, line); // Skip first line
    
    int id = 0;
    while(std::getline(csvFile, line)){
        if(line.empty()) continue;
        auto f = split(line, ',');
        if(f.size() < 7) continue;
        Cell* c = new Cell(f[0], f[1], f[2], stoi(f[3]), stoi(f[4]), stoi(f[5]), stoi(f[6]));
        this->_placement.addCell(c);
        this->_cellName2ID[f[0]] = id;
        ++id;
    }

    std::cout << "Reading " << filename << " done!\n";
    return true;
}

bool bookshelf::Parser::parsePlFile(const std::string& filename){
    std::ifstream plFile(filename);
    if(!plFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }
    else{
        std::cout << "== Reading Bookshelf .pl file ==\n";
    }

    std::string line;
    std::getline(plFile, line);
    std::getline(plFile, line);
    
    int id = 0;
    while(std::getline(plFile, line)){
        if(line.find("/FIXED_NI")==std::string::npos){
            continue;
        }

        std::istringstream iss(line);
        std::string name;
        double xc, yc;
        iss >> name >> xc >> yc;
        Cell* t = new Cell(name, "", "terminal", 0, 0, xc, yc);
        this->_placement.addTerminal(t);
        this->_terName2ID[name] = id;
        ++id;
    }

    std::cout << "Reading " << filename << " done!\n";
    return true;
}


bool bookshelf::Parser::parseNetsFile(const std::string& filename){
    std::ifstream netFile(filename);
    if(!netFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }
    else{
        std::cout << "== Reading Bookshelf .nets file ==\n";
    }

    std::string line;
    std::string a,b,c, colon1, colon2;
    double degree, xOff, yOff, zero1, zero2;

    std::getline(netFile, line);
    std::getline(netFile, line);

    int numNets, numPins;
    netFile >> a >> colon1 >> numNets;
    netFile >> a >> colon1 >> numPins;

    for(int i=0; i<numNets; ++i){
        netFile >> a >> colon1 >> degree >> b;
        Net* net = new Net(b);
        for(int j=0; j<degree; ++j){
            netFile >> a >> b >> colon1 >> xOff >> yOff >>colon2 >> zero1 >> zero2 >> c;
            
            if(this->_cellName2ID.count(a)){
                // Build this Pin
                Pin* pin = new Pin(c.substr(2), (b=="I")? INPUT: OUTPUT, this->_cellName2ID[a], i);
                pin->setXYOffset(xOff, yOff);
                
                // Add pinter for its Net & its Cell
                this->_placement.cellAddPin(this->_cellName2ID[a], pin);
                net->addPin(pin);
            }
            else{
                // Build this Pin
                Pin* pin = new Pin(c.substr(2), (b=="I")? INPUT: OUTPUT, this->_terName2ID[a], i);
                pin->setXYOffset(xOff, yOff);
                
                // Add pinter for its Net & its Cell
                this->_placement.terAddPin(this->_terName2ID[a], pin);
                net->addPin(pin);
            }
        }
    }

    std::cout << "Reading " << filename << " done!\n";
    return true;
}

