/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the Simulation Class
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <exception>
#include <fstream>
#include <thread>
#include <chrono>

#include "grid.h"
#include "classic_mode.h"
#include "mirror_mode.h"
#include "doughnut_mode.h"

using namespace std;

class Simulation {
    public:
        Simulation();
        Simulation(Grid *initial_grid);
        ~Simulation();

        void PromptUser();
        void Start();

    private:
        char grid_mode_;
        char game_mode_;
        char pause_mode_;
        string grid_file_;
        string output_file_;
        int num_selected_rows_;
        int num_selected_columns_;
        double pop_density_;
        Grid *current_gen_;
        Grid *next_gen_;
};
#endif