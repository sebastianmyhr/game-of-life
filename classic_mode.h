/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the ClassicMode Class
 */

#ifndef CLASSIC_MODE_H
#define CLASSIC_MODE_H

#include "gamemode.h"

class ClassicMode : public Gamemode {
    public:
        ClassicMode();
        ~ClassicMode();
        Grid Play(Grid *current_gen);
};
#endif