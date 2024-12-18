#include "functions.h"


void printMat(const MAT& m) {
    clear(); // Clear the screen at the beginning of each print
    for (unsigned row = 1; row < m.size() - 1; row++) {
        for (unsigned col = 1; col < m[row].size() - 1; col++) {
            if (m[row][col] == 1) 
                mvprintw(row, col, "%c", 'X');
        }
    }
    refresh();
}

bool outOfBounds(MAT &m, int row, int col) {
    if (row == 0 || col == 0) {
        m[row][col] = 0;
        return true;
    }    
    return false;
}

void checkNeighbors(MAT &m, MAT &m2, int rows, int cols) {
    for (unsigned row = 1; row < rows - 1; row++) {
        for (unsigned col = 1; col < cols - 1; col++) {
            int count = 0;
            if (m[row-1][col-1] == 1)
                (outOfBounds(m, row-1, col-1)) ? count : count++;
            if (m[row-1][col] == 1) 
                (outOfBounds(m, row-1, col)) ? count : count++;
            if (m[row-1][col+1] == 1) 
                (outOfBounds(m, row-1, col+1)) ? count : count++;
            if (m[row][col+1] == 1) 
                (outOfBounds(m, row, col+1))   ? count : count++;
            if (m[row+1][col+1] == 1) 
                (outOfBounds(m, row+1, col+1)) ? count : count++;
            if (m[row+1][col] == 1) 
                (outOfBounds(m, row+1, col))   ? count : count++;
            if (m[row+1][col-1] == 1) 
                (outOfBounds(m, row+1, col-1)) ? count : count++;
            if (m[row][col-1] == 1) 
                (outOfBounds(m, row, col-1))   ? count : count++; 

            if (m[row][col] == 1) {
                if (count < 2 || count > 3) 
                    m2[row][col] = 0;
                else if (count == 2 || count == 3)
                    m2[row][col] = 1;
            }
            else {
                if (count == 3)
                    m2[row][col] = 1;
            }
        }
    }
}


void gameSim(MAT &m, MAT &m2, int rows, int cols) {
    while (true) {
        // checks 8 cell neighbors
        checkNeighbors(m, m2, rows, cols);

        // Print the new generation
        printMat(m2);
        this_thread::sleep_for(chrono::milliseconds(150));

        m = m2;
        VEC v (cols, 0);
        MAT m2 (rows, v);
    }
}

void clickCells(MAT &m, int rows, int cols) {
    MEVENT event;
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mouseinterval(3);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    while (true) {
        int c = getch();
        switch (c) {
            case KEY_MOUSE:
                if (getmouse(&event) == OK && (event.bstate & BUTTON1_PRESSED)) {
                    int x = event.x;  
                    int y = event.y;  

                    // Check coordinates are within bounds
                    if (x < 1) 
                        x = 1;
                    if (x > cols - 2) 
                        x = cols - 2;
                    if (y < 1) 
                        y = 1;
                    if ( y > rows - 2) 
                        y = rows - 2;

                    if (m[y][x] == 0) {
                        m[y][x] = 1;
                        mvprintw(y, x, "%c", 'X');
                    }
                    else {
                        m[y][x] = 0;
                        mvprintw(y, x, "%c", ' ');
                    }
                    refresh();
                }
                break;
            case 'q':
                return;
        }
    }
}
