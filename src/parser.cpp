#include "parser.h"
#include <string>

bool bookshelf::Parser::parseNodesFile(const std::string& filename){
    std::ifstream infile(filename);
    if(!infile){
        std::cerr << "Cannot open " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(infile, line);
    std::getline(infile, line);

    int numNodes = 0;
    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string label, colon;
        iss >> label >> colon >> numNodes;
        this->setNumNodes(numNodes);
    }

    int numTerms = 0;
    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string label, colon;
        iss >> label >> colon >> numTerms;
        this->setNumTerminals(numTerms);
    }

    std::getline(infile, line);

    for(int i=0; i< numTerms; ++i){
        std::getline(infile, line);
        std::istringstream iss(line);
        std::string name;
        int w, h;
        iss >> name >> w >> h;
        std::cout<<name<<" "<<w<<" "<<h<<std::endl;
        Node node(name, true, w, h);
        
    }


    return true;
}


bool bookshelf::Parser::parseNetsFile(const std::string& filename){
    return true;
}

void bookshelf::Parser::setNumNodes(int nn){
    this->_numNodes = nn;
}

void bookshelf::Parser::setNumTerminals(int nt){
    this->_numTerminals = nt;
}