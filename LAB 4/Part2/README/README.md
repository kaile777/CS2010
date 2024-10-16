Kaile Jones

Assignment 4, Part 2 (Game of Life)

This project simulates conways game of life.

BULD:
Project was developed on Ubuntu linux distrobution and compiled using GNU g++ compiler. 
You must build this project under linux or else you will not be able to run the program since it uses
the ncurses library, which can only be run on linux. 
To compile I use:
        "g++ -o {exe_name} main.cpp functions.cpp -lncurses"
Now, with you exe file, do:
        "./{exe_name}"

HOW-TO:
After successful compilation and running of the program, you will have a blank screen.
An active game grid will be running by the dimensions of 42 rows X 82 columns. Inside this grid, 
you make click on cells to reveal an 'X'. Each cell with an 'X' will be a live cell. When you finish
placing live cells, press 'q'. Now you should see the simulation running.

