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

struct Net{
    std::string name;
    int degree;
    std::vector<std::string> nodes;
};

struct Pin{
    std::string name;
    std::string gate;
    int netID;
};

struct Cell{
    std::string name;
    std::string library;
    std::string type;
    double w, h, xCoor, yCoor;
};

#endif