#pragma once
#include <Vector>
#include "Types.h"

using namespace std;
class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid();

    vector<Types::GridBox> grids;

    int xLenght;
    int yLength;
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield(int Lines, int Columns);
};

