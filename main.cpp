/*
 * Sebastian Myhr
 * 2375087
 * smyhr@chapman.edu
 * CPSC 350-03
 * Assignment 3
 *
 * The main method
 */

#include "simulation.h"

int main(int argc, char** argv) {
    try {      
        Simulation *s1 = new Simulation();
        s1->Start();
        delete s1;

    } catch (runtime_error &excpt) {
        cerr << excpt.what() << endl;
    }
    return 0;
}