/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * ClassicMode is a Gamemode that ignores any references outside the grid
 */

#include "classic_mode.h"

/**
 * The default constructor for Classic Mode
 */
ClassicMode::ClassicMode() {}

/**
 * The deconstructor for Classic Mode
 */
ClassicMode::~ClassicMode() {}

/**
 * Simulates one sequence of the game for Classic Mode
 * @param current_gen a pointer to a grid representing the current generation of the grid
 * @return A Grid representing the next generation of the initial Grid
 */
Grid ClassicMode::Play(Grid *current_gen) {
    Grid next_generation = Grid(current_gen->GetNumRows(), current_gen->GetNumColumns());
    unsigned int num_neighbor_cells;
    for (int i = 0; i < current_gen->GetNumRows(); ++i) {
        for (int j = 0; j < current_gen->GetNumColumns(); ++j) {
            num_neighbor_cells = CountNeighborsIgnoreOutside(i, j, current_gen);
            // cout << current_gen->GetGridCell(i, j) << ": " << num_neighbor_cells << " neighbors" << endl;
            switch (num_neighbor_cells) {
                case 0 ... 1:
                    //empty in next gen
                    next_generation.SetGridLocation(i, j, '-');
                    break;
                case 2:
                    //remains stable
                    next_generation.SetGridLocation(i, j, current_gen->GetGridCell(i, j));
                    break;
                case 3:
                    //contains cell in next generation
                    next_generation.SetGridLocation(i, j, 'X');
                    break;
                default:
                    //empty in the next generation
                    next_generation.SetGridLocation(i, j, '-');
                    break;
            }
            num_neighbor_cells = 0;
        }
    }
    return next_generation;
}