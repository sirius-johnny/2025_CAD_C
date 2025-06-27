#ifndef INSTANCE_H
#define INSTANCE_H
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

enum class PinDir {INPUT, OUTPUT};
struct Net;
struct Cell;

struct Pin{
    std::string name;
    PinDir      dir;
    Cell*       cell;
    Net*        net;
};

struct Net{
    std::string name;
    std::vector<Pin*> pins;
};

struct Library{
    std::string name;
    double      area;
    std::vector<std::pair<std::string, PinDir>> pinDef;
};

struct Cell{
    std::string name;
    std::string library;
    std::string type;
    double      w, h, xCoor, yCoor;
};

#endif