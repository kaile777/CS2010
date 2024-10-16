#include <vector>
#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "functions.h"


int main() {
    
    int rows = 42; // Including padding
    int cols = 82; // Including padding

    VEC v(cols, 0);
    MAT m(rows, v);
    MAT m2(rows, v);

    initscr();
    clickCells(m, rows, cols);

end:

    gameSim(m, m2, rows, cols);
    endwin();

    return 0;
}


