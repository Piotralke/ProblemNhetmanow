

#pragma once
#ifndef ALGORYTM_H
#define ALGORYTM_H
#include "include_lib.h"
#include "drawing.h"


int counter;


extern bool isSafe(int** board, int row, int col, int size);
extern bool solveNhetman(int** board, int col, int size, ALLEGRO_BITMAP* hetman, FILE* file);

#endif // !ALGORYTM_H
