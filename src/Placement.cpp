#include "Placement.h"

Placement::Placement() {

}

void Placement::addLibrary(Library* lib){
    this->_libraries.push_back(lib);
}

void Placement::addNet(Net* net){
    this->_nets.push_back(net);
}

void Placement::addCell(Cell* cell){
    this->_cells.push_back(cell);
}

void Placement::addTerminal(Cell* ter){
    this->_terminals.push_back(ter);
}

void Placement::cellAddPin(int cID, Pin* pin){
    this->_cells.at(cID)->addPin(pin);
}

void Placement::terAddPin(int tID, Pin* pin){
    this->_terminals.at(tID)->addPin(pin);
}

void Placement::showLibInfo(int libID){
    std::cout << "| Library: "  << this->_libraries.at(libID)->name()
              << " | Area: "    << this->_libraries.at(libID)->area()
              << " | NumPins:"  << this->_libraries.at(libID)->pinDef().size()
              << std::endl;
}

void Placement::showNetInfo(int netID){
    std::cout << "| Net: "      << this->_nets.at(netID)->name() 
              << " | Degree:"   << this->_nets.at(netID)->pins().size()
              << std::endl;
}

void Placement::showCellInfo(int cellID){
    std::cout << "| Cell: "     << this->_cells.at(cellID)->name ()
              << " | Library: " << this->_cells.at(cellID)->library()
              << " | (w, h): "  << this->_cells.at(cellID)->w() << ", " << this->_cells.at(cellID)->h()
              << " | (X, Y): "  << this->_cells.at(cellID)->xCoor() << ", " << this->_cells.at(cellID)->yCoor()
              << std::endl;
    std::vector<Pin*> pins = this->_cells.at(cellID)->pins();
    for(int i=0; i<pins.size(); ++i){
        std::cout << "[Pin]: " << pins.at(i)->name() << "        [I/O]: " << (pins.at(i)->dir()? "I": "O") << std::endl;
    }
}

void Placement::plotPlacement(const std::string& filename){
    std::ofstream plotFile(filename);
    std::cout << "== Write output plot ==\n";
    plotFile << " " << std::endl;
    // plotFile << "set title \"wirelength = " << _placement.computeHpwl() << "\"" << endl;
    plotFile << "set size ratio 1" << std::endl;
    plotFile << "set nokey" << std::endl
             << std::endl;
    plotFile << "plot[:][:] '-' w l lt 3 lw 2, '-' w l lt 1" << std::endl
             << std::endl;
    plotFile << "# bounding box" << std::endl;
    plotBox(plotFile, this->_boundLeft, this->_boundBottom, this->_boundRight, this->_boundTop);
    plotFile << "EOF" << std::endl;
    plotFile << "# modules" << std::endl
            << "0.00, 0.00" << std::endl
            << std::endl;
    for (size_t i=0; i < this->_cells.size(); ++i) {
        Cell* c = this->_cells.at(i);
        plotBox(plotFile, c->xCoor(), c->yCoor(), c->xCoor() + c->w(), c->yCoor() + c->h());
    }
    plotFile << "EOF" << std::endl;
    plotFile << "pause -1 'Press any key to close.'" << std::endl;
    plotFile.close();
    std::cout << "Writing " << filename << " done!\n";

}

void Placement::plotBox(std::ofstream &stream, double x1, double y1, double x2, double y2) {
    stream << x1 << ", " << y1 << std::endl
           << x2 << ", " << y1 << std::endl
           << x2 << ", " << y2 << std::endl
           << x1 << ", " << y2 << std::endl
           << x1 << ", " << y1 << std::endl
           << std::endl;
}

