/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the DoughnutMode Class
 */

#ifndef DOUGHNUT_MODE_H
#define DOUGHNUT_MODE_H

#include "gamemode.h"

using namespace std;

class DoughnutMode : Gamemode {
    public:
        DoughnutMode();
        ~DoughnutMode();
        Grid Play(Grid *current_gen);
        int DoughnutCountEdgeNeighbors(int row, int column, Grid *grid);
};
#endif