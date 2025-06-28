#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "Placement.h"

namespace bookshelf{

class Parser{
public:
    Parser(Placement& p): _placement(p) {};
    ~Parser() {};
    bool parseLibsFile(const std::string& filename);    // Read Libs file from python dumping
    bool parseCSVFile(const std::string& filename); 
    bool parsePlFile(const std::string& filename);      // Build terminals only
    bool parseNetsFile(const std::string& filename);

private:
    Placement& _placement;
    std::unordered_map<std::string, int> _cellName2ID;
    std::unordered_map<std::string, int> _terName2ID;
};

}

#endif