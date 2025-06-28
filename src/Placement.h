#ifndef PLACEMENT_H
#define PLACEMENT_H
#include "Pin.h"
#include "Cell.h"
#include "Library.h"
#include "Net.h"

class Placement{
public:
    Placement();
    // ~Placement();

    // Methods for construction //
    void addLibrary(Library* lib);
    void addNet(Net* net);
    void addCell(Cell* cell);
    void addTerminal(Cell* ter);
    void cellAddPin(int cID, Pin* pin);
    void terAddPin(int ctID, Pin* pin);

    // Display infomation //
    void showLibInfo(int libID);
    void showNetInfo(int netID);
    void showCellInfo(int cellID);

    // Plot functions //
    void plotPlacement(const std::string& filename);
    void plotBox(std::ofstream &stream, double x1, double y1, double x2, double y2);

private:

    // Design Data //
    std::vector<Library*>   _libraries;
    std::vector<Net*>       _nets;
    std::vector<Cell*>      _cells;
    std::vector<Cell*>      _terminals;

    // Design Region //
    double _boundLeft = 0;
    double _boundRight = 50000;
    double _boundBottom = 0;
    double _boundTop = 50000;
};

#endif // PLACEMENT_H