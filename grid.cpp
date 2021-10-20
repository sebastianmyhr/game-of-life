/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * The Grid class defines a grid and the methods relating to creating, comparing, and returning a grid
 */

#include "grid.h"

/**
 * The default constructor for a grid
 */
Grid::Grid() {
    num_rows_ = 0;
    num_columns_ = 0;
    num_cells_ = 0;
    grid_array_ = new char*[0];
}

/**
 * Constructor for a grid given an input file
 * @param filename A string representing the file to read the grid from
 */
Grid::Grid(string filename) {
    if(!IsValidGridFile(filename)) {
        throw runtime_error("invalid grid file");
    }
    string rows_str = "";
    string columns_str = "";
    fstream grid_file;
    grid_file.open(filename, ios::in);
    string line;
    int line_num = 0;

    while (getline(grid_file, line)) {
        if (line_num == 0) {
        //if the line is the first line
            for (int i = 0; i < line.length(); ++i) {
                rows_str += line[i];
            }
            stringstream rows(rows_str);
            rows >> num_rows_;
        } else if (line_num == 1) {
            //if the line is the second line
            for (int j = 0; j < line.length(); ++j) {
                columns_str += line[j]; 
            }
            stringstream columns(columns_str);
            columns >> num_columns_;

            //Creates the grid array before reading the rest of the loop
            num_cells_ = num_rows_ * num_columns_;
            grid_array_ = new char*[num_rows_];
            for (int i = 0; i < num_rows_; ++i) { //Initializes an empty grid
                grid_array_[i] = new char[num_columns_];
                for (int j = 0; j < num_columns_; ++j) {
                    grid_array_[i][j] = '-';
                }
            }
        } else {
            for (int k = 0; k < line.length(); ++k) {
                grid_array_[line_num - 2][k] = line[k];
            }
        }
        ++line_num;
    }
}

/**
 * Constructor for a grid given the number of rows and columns it has
 * @param rows An unsigned int representing the number of rows in the grid
 * @param columns An unsigned int representing the number of columns in the grid
 */
Grid::Grid(unsigned int rows, unsigned int columns) {
    num_rows_ = rows;
    num_columns_ = columns;
    num_cells_ = rows * columns;
    srand(time(NULL));

    grid_array_ = new char*[num_rows_];
    for (int i = 0; i < num_rows_; ++i) { //Initializes an empty grid
        grid_array_[i] = new char[num_columns_];
        for (int j = 0; j < num_columns_; ++j) {
            grid_array_[i][j] = '-';
        }
    }
}

/**
 * Constructor for a grid given the number of rows and columns it has and its density
 * @param rows An unsigned int representing the number of rows in the grid
 * @param columns An unsigned int representing the number of columns in the grid
 * @param density A float value between 0 and 1 representing the initial population density of the grid
 */
Grid::Grid(unsigned int rows, unsigned int columns, float density) {
    if (density < 0.0 | density > 1.0) {
        throw runtime_error("density is not in bounds");
    }
    num_rows_ = rows;
    num_columns_ = columns;
    num_cells_ = rows * columns;
    srand(time(NULL));

    grid_array_ = new char*[num_rows_];
    for (int i = 0; i < num_rows_; ++i) { //Initializes an empty grid
        grid_array_[i] = new char[num_columns_];
        for (int j = 0; j < num_columns_; ++j) {
            grid_array_[i][j] = '-';
        }
    }

    int num_populated_cells = (int) (num_cells_ * density);
    int curr_row;
    int curr_column;

    while(num_populated_cells != 0) {
        curr_row = RandomIndexGenerator(num_rows_);
        curr_column = RandomIndexGenerator(num_columns_);

        if (grid_array_[curr_row][curr_column] == 'X') {
            
            curr_row = num_rows_ % (curr_row + 1);
            curr_column = num_columns_ % (curr_column + 1);

            if(grid_array_[curr_row][curr_column] == 'X') {
                continue;
            }
        }
        grid_array_[curr_row][curr_column] = 'X';
        --num_populated_cells;
    }
}

/**
 * The destructor for grid
 */
Grid::~Grid(){
    for (int i = 0; i < num_rows_; ++i) {
            delete [] grid_array_[i];
    }
    delete [] grid_array_;
}

/**
 * Given another grid, copies all its locations into the original grid
 * @param g1 The grid to copy
 */
void Grid::CopyGrid(Grid g1) {
    if (this->num_rows_ != g1.num_rows_|| this->num_columns_ != g1.num_columns_) {
        throw runtime_error("Grids must be of same size");
    }
    for (int i = 0; i < this->num_rows_; ++i) {
        for (int j = 0; j < this->num_columns_; ++j) {
            this->grid_array_[i][j] = g1.grid_array_[i][j];
        }
    }
}

/**
 * Given another grid pointer, copies all its locations into the original grid
 * @param g1 The grid pointer to copy
 */
void Grid::CopyGrid(Grid *g1) {
    if (this->num_rows_ != g1->num_rows_|| this->num_columns_ != g1->num_columns_) {
        throw runtime_error("Grids must be of same size");
    }
    for (int i = 0; i < this->num_rows_; ++i) {
        for (int j = 0; j < this->num_columns_; ++j) {
            this->grid_array_[i][j] = g1->grid_array_[i][j];
        }
    }
}

/**
 * Sets the value of a location of the Grid
 * @param row int representing the row of the location
 * @param column int representing the column of the location
 * @param value char representing the value of the location, which must be either ' ' or 'X'
 */
void Grid::SetGridLocation(int row, int column, char value) {
    grid_array_[row][column] = value;
}

/**
 * Returns the value of a cell in the Grid
 * @param row int representing the row of the location
 * @param column int representing the column of the location
 * @return char representing the value of the location
 */
char Grid::GetGridCell(int row, int column) {
    return grid_array_[row][column];
}

/**
 * Returns the number of rows in the Grid
 * @return The number of rows in the Grid
 */
unsigned int Grid::GetNumRows() {
    return num_rows_;
}

/**
 * Returns the number of columns in the Grid
 * @return The number of rows in the Grid
 */
unsigned int Grid::GetNumColumns() {
    return num_columns_;
}

/**
 * Returns the grid's 2D array
 * @return 2D array representing the grid
 */
char** Grid::GetGridArray() {
    return grid_array_;
}

/**
 * Prints out a visual representation of the grid
 */
void Grid::PrintGrid() {
    for (int i = 0; i < num_rows_; ++i) {
        for (int j = 0; j < num_columns_; ++j) {
            cout << grid_array_[i][j];
        }
        cout << endl;
    }
}

/**
 * Prints out a visual representation of the grid and its generation
 * @param gen unsigned int representing the grid's generation
 */
void Grid::PrintGrid(unsigned int gen) {
    cout << "Generation: " << gen << endl;
    for (int i = 0; i < num_rows_; ++i) {
        for (int j = 0; j < num_columns_; ++j) {
            cout << grid_array_[i][j];
        }
        cout << endl;
    }
}

/**
 * Prints out a visual representation of the grid to a given output and its generation
 * @param gen unsigned int representing the grid's generation
 * @param output fstream representing where the grid will be output to
 */
void Grid::PrintGrid(unsigned int gen, fstream &f_out) {
    f_out << "Generation: " << gen << endl;
    for (int i = 0; i < num_rows_; ++i) {
        for (int j = 0; j < num_columns_; ++j) {
            f_out << grid_array_[i][j];
        }
        f_out << endl;
    }
}

/**
 * Compares two grids to see if they are equal
 * @param g1 A pointer to a grid
 * @return 1 if the grids are the same, 0 if they are not the same
 */
bool Grid::IsEqual(Grid *g1) {
    if (this == g1) {
        // same memory address
        return true;
    }
    if (this->num_rows_ == g1->num_rows_ | this->num_columns_ == g1->num_columns_) {
        // they must have same number of cells 
        for (int i = 0; i < this->num_rows_; ++i) {
            for (int j = 0; j < this->num_columns_; ++j) {
                if (this->grid_array_[i][j] != g1->grid_array_[i][j]) {
                    return false;
                    break;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

/**
 * Checks if a cell on the grid is filled or empty
 * @param cell_item what the contains
 * @return 1 if the cell is filled, 0 if empty
 */
bool Grid::IsCellFilled(char cell_item) {
    if (cell_item == 'X') {
        return true;
    } else if (cell_item == '-') {
        return false;
    } else {
        throw runtime_error("invalid grid element");
    }
}

/**
 * Returns a random index given the maximum possible index
 * @param max_size int representing the max index
 * @return int representing a randomly selected index from 0 to the max index
 */
int Grid::RandomIndexGenerator(int max_size) {
    return (rand() % (max_size));
}

/**
 * Checks whether a file is a valid file for a grid
 * @param file string representing the file to read from
 * @return 1 if the file is valid, 0 if the file is not valid
 */
bool Grid::IsValidGridFile(string file) {
    bool IsValid = true;
    string expected_rows = "";
    string expected_columns = "";
    int read_rows = 0;
    int read_columns = 0;
    int r = 0;
    int c = 0;
    fstream grid_file;
    grid_file.open(file, ios::in);

    if (!grid_file) {
        IsValid = false;
    } else {
        string line;
        int line_num = 0;
        if (grid_file.is_open()) {
            
            while (getline(grid_file, line)) {
                read_columns = 0;
                if (line_num == 0) {
                    //if the line is the first line
                    for (int i = 0; i < line.length(); ++i) {
                        if (!isdigit(line[i])) {
                            IsValid = false;
                            break;
                        }
                        //adds together the number that represents the number of rows the grid has
                        expected_rows += line[i];
                        stringstream rows(expected_rows);
                        rows >> r;
                    }
                } else if (line_num == 1) {
                    //if the line is the second line
                    for (int j = 0; j < line.length(); ++j) {
                        if (!isdigit(line[j])) {
                            IsValid = false;
                            break;
                        }
                        //adds together the number that represents the number of columns the grid has
                        expected_columns += line[j]; 
                        stringstream columns(expected_columns); 
                        columns >> c;
                    }
                } else {
                    //if the line is any other line after that
                    for (int k = 0; k < line.length(); ++k) {
                        read_columns += 1;
                        if (!(line[k] == '-' | line[k] == 'X')) {
                            IsValid = false;
                            break;
                        }
                    }
                    
                    if (c != read_columns) {
                        IsValid = false;
                        break;
                    }
                }
                ++line_num;
            }
            read_rows = line_num - 2;
        }
        grid_file.close();
    }
    if (r != read_rows) {
        IsValid = false;
    } if ((r == 0 | c == 0)) {
        IsValid = false;
    }

    return IsValid;
}