/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the MirrorMode Class
 */

#ifndef MIRROR_MODE_H
#define MIRROR_MODE_H

#include "gamemode.h"

class MirrorMode : Gamemode {
    public:
        MirrorMode();
        ~MirrorMode();
        Grid Play(Grid *current_gen);
        int MirrorCountEdgeNeighbors(int row, int column, Grid *grid);
};
#endif