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
    bool parseNodesFile(const std::string& filename);
    bool parseNetsFile(const std::string& filename);

    void setNumNodes(int nn);
    void setNumTerminals(int nt);


private:
    int _numNodes; 
    int _numTerminals;
    std::vector<Net*> _nets;
    std::vector<Node*> _nodes;
};

}

#endif