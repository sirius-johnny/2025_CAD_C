#ifndef LIBRARY_H
#define LIBRARY_H
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

class Library{
public:
    // Constructor //
    Library(std::string name, double area)
    : _name(name), _area(area) {}

    // Methods for construction //
    void addPinDef(std::pair<std::string, bool> pd) {this->_pinDef.push_back(pd);}
    void setFF(bool f)                              {this->_isFF = f;}

    // Get //
    std::string                                 name()      {return _name;}
    double                                      area()      {return _area;}
    std::vector<std::pair<std::string, bool>>   pinDef()    {return _pinDef;}
    bool                                        isFF()      {return _isFF;}

private:
    std::string                                 _name;
    double                                      _area;
    std::vector<std::pair<std::string, bool>>   _pinDef;
    bool                                        _isFF;
};

#endif