/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * The Simulation class holds the method to start the game of life with the selected parameters
 */

#include "simulation.h"

/**
 * The default constructor for Simulation
 */
Simulation::Simulation() {}

/**
 * The default destructor for Simulation
 */
Simulation::~Simulation() {
    delete current_gen_;
    delete next_gen_;
}

/** 
 * Prompts user for the conditions of the game and sets member variables accordingly
 */
void Simulation::PromptUser() {
    cout << "Welcome to the game of life!" << endl << endl;
    bool input_condition_met = false;
    
    // Grid configuration
    while (!input_condition_met) {
        string grid_mode;
        cout << "Please select grid configuration type." << endl;
        cout << "   Type \"r\" for a random configuration." << endl;
        cout << "   Type \"f\" for a flat-file configuration." << endl;
        cout << "Input: ";
        cin >> grid_mode;
        if (grid_mode.length() > 1) {
            cout << endl << "Invalid input: try again.\n\n";
        } else if (tolower(grid_mode[0]) == 'r') {
            grid_mode_ = 'r';
            input_condition_met = true;
        } else if (tolower(grid_mode[0]) == 'f') {
            grid_mode_ = 'f';
            input_condition_met = true;
        } else {
            cout << endl << "Invalid input: try again.\n\n";
        }
    }

    cout << "\n";
    input_condition_met = false;

    // prompting for grid conditions
    while (!input_condition_met) {
        if (grid_mode_ == 'r') {
            // random grid
            bool is_numeric = false;
            int num_rows;
            int num_columns;
            double density;

            cout << "Number of rows: ";
            cin >> num_rows;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cout << "\nInvalid input: try again\n\n";
            } else {
                cout << "Number of columns: ";
                cin >> num_columns;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    cout << "\nInvalid input: try again\n\n";
                } else {
                    cout << "Density (Between 0.0-1.0): ";
                    cin >> density;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        cout << "\nInvalid input: try again\n\n";
                    } else {
                        is_numeric = true;
                    }
                }
            } 
            if (num_rows > 0 
                && num_columns > 0 
                && density > 0.0 
                && density < 1.0
                && is_numeric) {
                    input_condition_met = true;
                    this->num_selected_rows_ = num_rows;
                    this->num_selected_columns_ = num_columns;
                    this->pop_density_ = density;
                } else if (is_numeric) {
                    cout << "\nInvalid input: try again\n\n";
                }
        } else if (grid_mode_ == 'f') {
            // user provides file
            string grid_input_file;
            cout << "File to read grid from: ";
            cin >> grid_input_file;
            fstream file_exists;
            file_exists.open(grid_input_file, ios::in);
            if (!file_exists) {
                cout << "\nFile not found\n\n";
            } else if (!Grid::IsValidGridFile(grid_input_file)) {
                cout << "\nNot a valid grid file\n\n";
            } else {
                input_condition_met = true;
                this->grid_file_ = grid_input_file;
                file_exists.close();
            }
        } else {
            break;
        }
    }

    cout << "\n";
    input_condition_met = false;

    // game mode
    while (!input_condition_met) {
        string game_mode;
        cout << "Please select boundary mode." << endl;
        cout << "   Type \"c\" for classic mode." << endl;
        cout << "   Type \"m\" for mirror mode." << endl;
        cout << "   Type \"d\" for doughnut mode." << endl;
        cout << "   Type \"i\" for information about the modes" << endl;
        cout << "Input: ";
        cin >> game_mode;
        
        if (game_mode.length() > 1) {
            cout << endl << "Invalid input: try again.\n\n";
        } else if (tolower(game_mode[0]) == 'c') {
            game_mode_ = 'c';
            input_condition_met = true;
        } else if (tolower(game_mode[0]) == 'm') {
            game_mode_ = 'm';
            input_condition_met = true;
        } else if (tolower(game_mode[0]) == 'd') {
            game_mode_ = 'd';
            input_condition_met = true;
        } else if (tolower(game_mode[0]) == 'i') {
            cout << "\nINFORMATION: " << endl;
            cout << "  Classic Mode: All locations off the grid are considered to be empty." << endl;
            cout << "  Mirror Mode: References off the grid are bounced back as though the wall were a mirror." << endl;
            cout << "  Doughnut Mode: The grid is wrapped around itself horizontally and vertically, resulting in a torus (doughnut) shape.\n\n";
        } else {
            cout << endl << "Invalid input: try again.\n\n";
        }
    }

    cout << "\n";
    input_condition_met = false;

    // pause mode
    while (!input_condition_met) {
        string pause_mode;
        cout << "Please select pause mode." << endl;
        cout << "   Type \"p\" short pause between generation." << endl;
        cout << "   Type \"e\" user presses \"Enter\" to advance to the next generation." << endl;
        cout << "   Type \"f\" output into file." << endl;
        cout << "Input: ";
        cin >> pause_mode;
        if (pause_mode.length() > 1) {
            cout << endl << "Invalid input: try again.\n\n";
        } else if (tolower(pause_mode[0]) == 'p') {
            pause_mode_ = 'p';
            input_condition_met = true;
        } else if (tolower(pause_mode[0]) == 'e') {
            pause_mode_ = 'e';
            input_condition_met = true;
        } else if (tolower(pause_mode[0]) == 'f') {
            pause_mode_ = 'f';
            input_condition_met = true;
        } else {
            cout << endl << "Invalid input: try again.\n\n";
        }
    }

    cout << "\n";

    if (pause_mode_ == 'f') {
        string grid_output_file;
        cout << "Select filename of output file." << endl;
        cout << "   Note: will automatically create a file with a .txt extension." << endl;
        cout << "Input: ";
        cin >> grid_output_file;
        output_file_ = grid_output_file + ".txt";
    }
}

/**
 * The Start function does everything necessary to play the game of life
 */
void Simulation::Start() {
    bool simulation_end = false;
    int gen_count = 0;
    PromptUser();

    if (grid_mode_ == 'r') {
        // randomly created grid
        current_gen_ = new Grid(num_selected_rows_, num_selected_columns_, pop_density_);
        next_gen_ = new Grid(num_selected_rows_, num_selected_columns_);
    } else if (grid_mode_ == 'f') {
        // open from the grid file
        current_gen_ = new Grid(grid_file_);
        next_gen_ = new Grid(current_gen_->GetNumRows(), current_gen_->GetNumColumns());
    } 
    if (pause_mode_ == 'p') {
        // short pause between generations
        if (game_mode_ == 'c') {
            // classic mode
            ClassicMode *c = new ClassicMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            this_thread::sleep_for(chrono::milliseconds(250));
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = c->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                this_thread::sleep_for(chrono::milliseconds(250)); 
            }
            delete c;
        } else if (game_mode_ == 'm') {
            // mirror mode
            MirrorMode *m = new MirrorMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            this_thread::sleep_for(chrono::milliseconds(250));
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = m->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                this_thread::sleep_for(chrono::milliseconds(250)); 
            }
            delete m;
        } else if (game_mode_ == 'd') {
            // doughnut mode
            DoughnutMode *d = new DoughnutMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            this_thread::sleep_for(chrono::milliseconds(250));
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = d->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                this_thread::sleep_for(chrono::milliseconds(250)); 
            }
            delete d;
        }
    } else if (pause_mode_ == 'e') {
        // user presses enter between generations
        if (game_mode_ == 'c') {
            // classic mode
            ClassicMode *c = new ClassicMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            cin.ignore(10000,'\n');
            if(cin.get() == '\n') {}
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = c->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                if(cin.get() == '\n') {}
            }
            delete c;
        } else if (game_mode_ == 'm') {
            // mirror mode
            MirrorMode *m = new MirrorMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            cin.ignore(10000,'\n');
            if(cin.get() == '\n') {}
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = m->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                if(cin.get() == '\n') {}
            }
            delete m;
        } else if (game_mode_ == 'd') {
            // doughnut mode
            DoughnutMode *d = new DoughnutMode();
            cout << "0" << endl;
            current_gen_->PrintGrid();
            cin.ignore(10000,'\n');
            if(cin.get() == '\n') {}
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count);
                Grid temp = d->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
                if(cin.get() == '\n') {}
            }
            delete d;
        }
    } else if (pause_mode_ == 'f') {
        // output to file
        fstream game_of_life_output;
        game_of_life_output.open(output_file_, ios::out);
        if (game_mode_ == 'c') {
            // classic mode
            ClassicMode *c = new ClassicMode();
            current_gen_->PrintGrid(0, game_of_life_output);
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count, game_of_life_output);
                Grid temp = c->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
            }
            delete c;
        } else if (game_mode_ == 'm') {
            // mirror mode
            MirrorMode *m = new MirrorMode();
            current_gen_->PrintGrid(0, game_of_life_output);
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count, game_of_life_output);
                Grid temp = m->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }
            }
            delete m;
        } else if (game_mode_ == 'd') {
            // doughnut mode
            DoughnutMode *d = new DoughnutMode();
            current_gen_->PrintGrid(0, game_of_life_output);
            while (!simulation_end) {
                ++gen_count;
                current_gen_->PrintGrid(gen_count, game_of_life_output);
                Grid temp = d->Play(current_gen_);
                next_gen_->CopyGrid(&temp);
                if (current_gen_->IsEqual(next_gen_)) {
                    simulation_end = true;
                } else {
                    current_gen_->CopyGrid(next_gen_);
                }  
            }
            delete d;
        }
        cout << "\nSuccess!" << endl;
    }   
}