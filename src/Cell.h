#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Pin.h"
#include "Library.h"

class Cell{
public:
    // Constructor //
    Cell(std::string name, std::string lib, std::string type, double w, double h, double xc, double yc)
    : _name(name), _library(lib), _type(type), _w(w), _h(h), _xCoor(xc), _yCoor(yc){}

    // Methods for construction //
    void addPin(Pin* p)     {_pins.push_back(p);}

    // Set //

    // Get //
    std::string         name()      {return _name;}
    std::string         library()   {return _library;}
    std::string         type()      {return _type;}
    double              w()         {return _w;}
    double              h()         {return _h;}
    double              xCoor()     {return _xCoor;}
    double              yCoor()     {return _yCoor;}
    std::vector<Pin*>   pins()      {return _pins;}

private:
    std::string         _name;
    std::string         _library;
    std::string         _type;
    double              _w;
    double              _h;
    double              _xCoor;
    double              _yCoor;
    std::vector<Pin*>   _pins;
};


#endif