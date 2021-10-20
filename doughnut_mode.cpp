/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * Doughnut Mode is a Gamemode that treats any index off the right-hand-side 
   as if it is wrapped around to the left-most column of the same row and 
   vice-versa. Any reference off the top wraps to the bottom in the same column.
 */

 #include "doughnut_mode.h"

/**
 * The default constructor for Doughnut Mode
 */
DoughnutMode::DoughnutMode() {}

/**
 * The deconstructor for Doughnut mode
 */
DoughnutMode::~DoughnutMode() {}

/**
 * Simulates one sequence of the game for Doughnut Mode
 * @param current_gen a pointer to a grid representing the current generation of the grid
 * @return A Grid representing the next generation of the initial Grid
 */
Grid DoughnutMode::Play(Grid *current_gen) {
    Grid next_generation = Grid(current_gen->GetNumRows(), current_gen->GetNumColumns());
    unsigned int num_neighbor_cells;
    for (int i = 0; i < current_gen->GetNumRows(); ++i) {
        for (int j = 0; j < current_gen->GetNumColumns(); ++j) {
            if (i == 0 | i == current_gen->GetNumRows() - 1 | j == 0 | j == current_gen->GetNumColumns() - 1) {
                // edge cell case
                num_neighbor_cells = DoughnutCountEdgeNeighbors(i, j, current_gen);
            } else {
                // inner cell case
                num_neighbor_cells = CountNeighborsIgnoreOutside(i, j, current_gen);
            }
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

/**
 * Counts the number of neighbors an edge-case location has in doughnut mode
 * @param row int representing the row of the location
 * @param column int representing the column of the location
 * @param grid point
 * @return int representing the number of neighbors the location has
 */
int DoughnutMode::DoughnutCountEdgeNeighbors(int row, int column, Grid *grid) {
    int max_row = grid->GetNumRows() - 1;
    int max_column = grid->GetNumColumns() - 1;
    int num_neighbor_cells = 0;

    if (max_row == 0 && max_column == 0) {
        // if the grid is is only one square
        if (grid->IsCellFilled(grid->GetGridCell(row, column))) {
            // wraps on 8 sides if occupied, none if not occupied
            num_neighbor_cells = 8;
        }
    } else if (max_row == 0) {  
        // if the grid only has one row
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (column == 0) {
            // first of of the only row
            if (grid->IsCellFilled(grid->GetGridCell(row, column))) {
                num_neighbor_cells += 2;
            } if (grid->IsCellFilled(grid->GetGridCell(row, max_column))) {
                num_neighbor_cells += 3;
            } if (grid->IsCellFilled(grid->GetGridCell(row, column + 1))) {
                num_neighbor_cells += 2;
            }
        } else if (column == max_column) {
            // last of of the only row
            if (grid->IsCellFilled(grid->GetGridCell(row, column))) {
                num_neighbor_cells += 2;
            } if (grid->IsCellFilled(grid->GetGridCell(row, 0))) {
                num_neighbor_cells += 3;
            } if (grid->IsCellFilled(grid->GetGridCell(row, column - 1))) {
                num_neighbor_cells += 2;
            }
        }
    } else if (max_column == 0) {
        // if the grid only has one column
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (row == 0) {
            // top of the only column
            if (grid->IsCellFilled(grid->GetGridCell(row, column))) {
                num_neighbor_cells += 2;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, column))) {
                num_neighbor_cells += 3;
            } if (grid->IsCellFilled(grid->GetGridCell(row - 1, column))) {
                num_neighbor_cells += 2;
            }
        } else if (row == max_row) {
            // bottom of the only column
            if (grid->IsCellFilled(grid->GetGridCell(0, column))) {
                num_neighbor_cells += 1;
            }
        }
    } else if (row == 0) {
        // if the index is on the top row of the grid
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (column == 0) {
            // if it is on the first column
            if (grid->IsCellFilled(grid->GetGridCell(max_row, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(1, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, 1))) {
                num_neighbor_cells += 1;
            }
        } else if (column == max_column) {
            // if it is on the last column
            if (grid->IsCellFilled(grid->GetGridCell(max_row, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(1, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, max_column - 1))) {
                num_neighbor_cells += 1;
            }
        } else {
            // anywhere in between first and last column
            if (grid->IsCellFilled(grid->GetGridCell(max_row, column - 1))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, column + 1))) {
                num_neighbor_cells += 1;
            }
        }
    } else if (row == max_row) {
        // if the index is on the bottom row
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (column == 0) {
            // if it is on the first column
            if (grid->IsCellFilled(grid->GetGridCell(0, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, 1))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row - 1, max_column))) {
                num_neighbor_cells += 1;
            }
        } else if (column == max_column) {
            // if it is on the last column
            if (grid->IsCellFilled(grid->GetGridCell(0, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(max_row - 1, 0))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, max_column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, max_column - 1))) {
                num_neighbor_cells += 1;
            }
        } else {
            // anywhere in between first and last column
            if (grid->IsCellFilled(grid->GetGridCell(0, column - 1))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, column))) {
                num_neighbor_cells += 1;
            } if (grid->IsCellFilled(grid->GetGridCell(0, column + 1))) {
                num_neighbor_cells += 1;
            }
        }
    } else if (column == 0) {
        // if the location is in the first column of the grid
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (grid->IsCellFilled(grid->GetGridCell(row, max_column))) {
            num_neighbor_cells += 1;
        } if (grid->IsCellFilled(grid->GetGridCell(row - 1, max_column))) {
            num_neighbor_cells += 1;
        } if (grid->IsCellFilled(grid->GetGridCell(row + 1, max_column))) {
            num_neighbor_cells += 1;
        }
    } else if (column == max_column) {
        // if the location is in the last column of the grid
        num_neighbor_cells += CountNeighborsIgnoreOutside(row, column, grid);
        if (grid->IsCellFilled(grid->GetGridCell(row, 0))) {
            num_neighbor_cells += 1;
        } if (grid->IsCellFilled(grid->GetGridCell(row - 1, 0))) {
            num_neighbor_cells += 1;
        } if (grid->IsCellFilled(grid->GetGridCell(row + 1, 0))) {
            num_neighbor_cells += 1;
        }
    }
    return num_neighbor_cells;
}