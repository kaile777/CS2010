#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

using VEC = vector<int>;
using MAT = vector<VEC>;

void printMat(const MAT& m);
void gameSim(MAT &m, MAT &m2, int rows, int cols);
void clickCells(MAT &m, int rows, int cols);

#endif
