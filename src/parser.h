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
#include "instance.h"

namespace bookshelf{

class Parser{
public:
    Parser() {};
    ~Parser() {};
    bool parseLibsFile(const std::string& filename);    // Read Libs file from python dumping
    bool parseCSVFile(const std::string& filename); 
    bool parsePlFile(const std::string& filename);      // Build terminals only
    bool parseNetsFile(const std::string& filename);

private:
    std::vector<Library*> _libraries;
    std::vector<Net*> _nets;
    std::vector<Cell*> _cells;
    std::vector<Cell*> _terminals;
};

}

#endif