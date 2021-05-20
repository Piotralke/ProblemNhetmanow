#include "handle_array.h"

void fill_array(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			array[i][j] = 0;
	}
}

void print_array(int** array, int size, FILE* file)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fprintf(file, "%d\t", array[i][j]);
		}
		fprintf(file, "\n");
	}
}

void free_ptr(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}