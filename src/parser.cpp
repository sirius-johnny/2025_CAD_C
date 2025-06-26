#include "parser.h"

static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::string item;
    std::istringstream ss(s);
    while (std::getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

bool bookshelf::Parser::parseCSVFile(const std::string& filename){
    std::ifstream csvFile(filename);
    if(!csvFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }
    
    std::string line;
    std::getline(csvFile, line); // Skip first line
    
    while(std::getline(csvFile, line)){
        if(line.empty()) continue;
        auto f = split(line, ',');
        if(f.size() < 7) continue;
        Cell* c = new Cell();
        c->name      = f[0];
        c->library   = f[1];
        c->type      = f[2];
        c->w         = std::stoi(f[3]);
        c->h         = std::stoi(f[4]);
        c->xCoor     = std::stoi(f[5]);
        c->yCoor     = std::stoi(f[6]);
        this->_cells.push_back(c);
    }

    // for(int i=0; i<10; ++i){
    //     std::cout   << "Cell Name: "    << _cells[i]->name 
    //                 << "|Library: "    << _cells[i]->library
    //                 << "|(w,h): "       << _cells[i]->w << ", " <<_cells[i]->h
    //                 << "|(X,Y): "       << _cells[i]->xCoor << ", " <<_cells[i]->yCoor <<std::endl;
    // }

    return true;
}

bool bookshelf::Parser::parsePlFile(const std::string& filename){
    // filename = "./testcase/aes_cipher_top/aes_cipher_top.nodes";
    std::ifstream plFile(filename);
    if(!plFile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(plFile, line);
    std::getline(plFile, line);
    
    while(std::getline(plFile, line)){
        if(line.find("/FIXED_NI")==std::string::npos){
            continue;
        }

        std::istringstream iss(line);
        Cell* t = new Cell();
        iss >> t->name >> t->xCoor >> t->yCoor;
        t->library = "";
        t->type = "terminal";
        t->w = 0;
        t->h = 0;
        this->_terminals.push_back(t);
    }

    // for(int i=0; i<10; ++i){
    //     std::cout   << "Cell Name: "    << _terminals[i]->name 
    //                 << "|Library: "    << _terminals[i]->library
    //                 << "|(w,h): "       << _terminals[i]->w << ", " <<_terminals[i]->h
    //                 << "|(X,Y): "       << _terminals[i]->xCoor << ", " <<_terminals[i]->yCoor <<std::endl;
    // }

    return true;
}


bool bookshelf::Parser::parseNetsFile(const std::string& filename){
    return true;
}
