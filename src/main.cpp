#include "parser.h"
#include "Placement.h"

int main(int argc, char **argv){
    std::unordered_map<std::string, std::string> args;

    for(int i=1; i<argc; ++i){
        std::string flag = argv[i];
        if((flag[0]=='-') && ((i+1)<argc)){
            args[flag] = argv[i+1];
            ++i;
        }
        else{
            std::cout << "Usage: ./bin/cadC [-libs <libs.txt>] [-csv <design.csv>] [-pl <design.pl>] [-nets <design.nets>] [-plot <graph.plt>]" << std::endl;
            return 0;
        }
    }

    // Build a PLACEMENT instance first
    Placement placement;
    bookshelf::Parser par(placement);

    // Reading design files...
    std::string libsFileName = args.count("-libs")? args["-libs"]: "./openroad_call/dump_for_Cplus/libs.txt";
    par.parseLibsFile(libsFileName);

    std::string csvFileName = args.count("-csv")? args["-csv"]: "./testcase/aes_cipher_top/aes_cipher_top_cell_info.csv";
    par.parseCSVFile(csvFileName);

    std::string plFileName = args.count("-pl")? args["-pl"]: "./testcase/aes_cipher_top/aes_cipher_top.pl";
    par.parsePlFile(plFileName);

    std::string netsFileName = args.count("-nets")? args["-nets"]: "./testcase/aes_cipher_top/aes_cipher_top.nets";
    par.parseNetsFile(netsFileName);

    /////////////////////////
    // Output .plt if need //
    /////////////////////////
    std::string plotPlaOutFileName = args.count("-plot")? args["-plot"]: "./output_plots/init.plt";
    placement.plotPlacement(plotPlaOutFileName);
    return 0;
}