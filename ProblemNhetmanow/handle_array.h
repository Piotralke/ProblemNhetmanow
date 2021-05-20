#ifndef HANDLE_ARRAY_H
#define HANDLE_ARRAY_H
#include "include_lib.h"

extern void fill_array(int** array, int size);
extern void print_array(int** array, int size, FILE* file);
extern void free_ptr(int** array, int size);

#endif // !HANDLE_ARRAY_H

