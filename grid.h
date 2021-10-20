/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Header file for the Grid Class
 */
 
#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Grid {
    public:
        Grid();
        Grid(string filename);
        Grid(unsigned int rows, unsigned int columns);
        Grid(unsigned int rows, unsigned int columns, float density);
        ~Grid();

        void CopyGrid(Grid g1);
        void CopyGrid(Grid *g1);
        void SetGridLocation(int row, int column, char value);
        char GetGridCell(int row, int column);
        unsigned int GetNumRows();
        unsigned int GetNumColumns();
        char** GetGridArray();

        void PrintGrid();
        void PrintGrid(unsigned int gen);
        void PrintGrid(unsigned int gen, fstream& f_out);
        bool IsEqual(Grid *g1);
        bool IsCellFilled(char cell_item);

        static bool IsValidGridFile(string file);
        static int RandomIndexGenerator(int max_size);
        
    private:
        char** grid_array_;
        unsigned int num_rows_;
        unsigned int num_columns_;
        unsigned int num_cells_;
};
#endif