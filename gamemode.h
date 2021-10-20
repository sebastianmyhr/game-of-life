/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the Gamemode base Class
 */

#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <iostream>
#include <exception>
#include "grid.h"

using namespace std;

class Gamemode {
    public:
        virtual Grid Play(Grid *current_gen) = 0;
        int CountNeighborsIgnoreOutside(unsigned int row, unsigned int column, Grid *grid);
        bool InsideBounds(int row, int column, Grid *grid);
};
#endif