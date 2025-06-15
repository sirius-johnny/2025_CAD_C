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
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

struct Node{
    std::string name;
    bool isTerminal = false;
    double w, h;

    Node(std::string name, bool ter, int w, int h): name(name), isTerminal(ter), w(w), h(h){};
};

#endif