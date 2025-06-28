#ifndef NET_H
#define NET_H
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

class Net{
public:
    // Constructor //
    Net(std::string name)
    : _name(name){}

    // Methods for construction //
    void addPin(Pin* p){this->_pins.push_back(p);};

    // Get //
    std::string         name()      {return _name;}
    std::vector<Pin*>   pins()      {return _pins;}
    int                 degree()    {return _pins.size();}

private:
    std::string         _name;
    std::vector<Pin*>   _pins;
};


#endif