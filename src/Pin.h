#ifndef PIN_H
#define PIN_H
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

constexpr bool INPUT = true;
constexpr bool OUTPUT = false;

class Pin{
public: 
    // Constructor //
    Pin(std::string name, bool pd, int cID, int nID) 
    : _name(name), _dir(pd), _cellID(cID), _netID(nID){}    

    // Set //
    void        setXYOffset(int x, int y)   {_xOffset = x; _yOffset = y;}

    // Get //
    std::string name()      {return _name;}
    bool        dir()       {return _dir;}
    int         cellID()    {return _cellID;}
    int         netID()     {return _netID;}

private:
    std::string _name;
    bool        _dir;
    int         _cellID = -1;
    int         _netID = -1;
    double      _xOffset;
    double      _yOffset;
};



#endif