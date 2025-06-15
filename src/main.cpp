#include "parser.h"
#include "instance.h"

int main(int argc, char **argv){
    std::string inFileName, outFileName;
    if(argc>=2){
        inFileName = argv[1];
    }
    else{
        std::cout << "Usage: ./bin/cadC <input>" << std::endl;
        return 0;
    }

    bookshelf::Parser par;
    par.parseNodesFile(inFileName);
    return 0;
}