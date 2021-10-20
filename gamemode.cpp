/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * The Gamemode class is an abstract class for the Classic, Mirror, and Doughnut gamemodes
 */
 
#include "gamemode.h"

/**
 * Counts the number of neighbors a cell has if it is not on the outside edge of the grid
 * @param row the cell's row
 * @param column the cell's column
 * @param grid a pointer to the grid that contains the cell
 * @return int representing the number of neighbors the cell has
 */
int Gamemode::CountNeighborsIgnoreOutside(unsigned int row, unsigned int column, Grid *grid) {
    if (row >= grid->GetNumRows() | column >= grid->GetNumColumns()) {
        throw runtime_error("grid index out of bounds");
    }
    int num_neighbor_cells = 0;
    int neighbor_row;
    int neighbor_column;
    char cell_char;

    // one up and left from origin
    neighbor_row = row - 1;
    neighbor_column = column - 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one up from origin
    neighbor_row = row - 1;
    neighbor_column = column;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one up and right from origin
    neighbor_row = row - 1;
    neighbor_column = column + 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }

    // one left from origin
    neighbor_row = row;
    neighbor_column = column - 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one right from origin
    neighbor_row = row;
    neighbor_column = column + 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one down and left from origin
    neighbor_row = row + 1;
    neighbor_column = column - 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one down from origin
    neighbor_row = row + 1;
    neighbor_column = column;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    // one down and right from origin
    neighbor_row = row + 1;
    neighbor_column = column + 1;
    if (InsideBounds(neighbor_row, neighbor_column, grid)) {
        cell_char = grid->GetGridCell(neighbor_row,neighbor_column);
        if (grid->IsCellFilled(cell_char)) {
                num_neighbor_cells += 1;
        }
    }
    return num_neighbor_cells;
}

/**
 * Checks if an index on a grid is inside bounds
 * @param row
 * @param column
 * @param grid
 * @return 
 */
bool Gamemode::InsideBounds(int row, int column, Grid *grid) {
    unsigned int grid_rows = grid->GetNumRows();
    unsigned int grid_columns = grid->GetNumColumns();
    return (row < grid_rows && column < grid_columns);
}