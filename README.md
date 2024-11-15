1.  Info
        Sebastian Myhr
        2375087
        smyhr@chapman.edu
        CPSC 350-03
        Assignment 3

2.  Files
        simulation.h
        simulation.cpp
        gamemode.h
        gamemode.cpp
        classic_mode.h
        classic_mode.cpp
        mirror_mode.h
        mirror_mode.cpp
        doughnut_mode.h
        doughnut_mode.cpp
        grid.h
        grid.cpp
        main.cpp
        makefile
        README.md

3.  Known Runtime Errors, Code Limitations, or Deviations from Assignment Specification
        - Cannot exit endless output of grids with "enter", only "ctrl+c", did not figure out how to implement this
        - If the option to output the game to a file is chosen, the only output is .txt, this is by design to ensure that any filename the user chooses is valid, without going through each possible text file type.

4.  References
        - makefile is taken from the canvas page for the course
        - RandomIndexGenerator was given during office hours
        - https://www.delftstack.com/howto/cpp/how-to-determine-if-a-string-is-number-cpp/        
                Used to check if string line is number
        - https://www.geeksforgeeks.org/converting-strings-numbers-cc/                            
                Convert string number to an int
        - https://stackoverflow.com/questions/22193550/c-input-a-char-instead-of-int-lead-to-endless-loop-how-to-check-the-wrong-inp              
                Check if input is correct
        - https://stackoverflow.com/questions/19439672/sleep-operation-in-c-on-os-x/19440500      
                Sleep without using Sleep()
        - https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input      
                Clear cin buffer
        - https://stackoverflow.com/questions/20207560/print-function-to-an-output-file           
                output to fstream in PrintGrid() overloaded function
     
5.  Instructions
        make all
        ./assignment3.out
