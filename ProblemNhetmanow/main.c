#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

int* make_array(int size)
{
	return (int*)calloc(size, sizeof(int));
}

void fill_array(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			array[i][j] = 0;
	}
}

void print_array(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d\t", array[i][j]);
		printf("\n");
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

/* A utility function to check if a queen can
be placed on board[row][col]. Note that this
function is called when "col" queens are
already placed in columns from 0 to col -1.
So we need to check only left side for
attacking queens */
bool isSafe(int** board, int row, int col, int size)
{
	int i, j;

	/* Check this row on left side */
	for (i = 0; i < col; i++)
		if (board[row][i])
			return false;

	/* Check upper diagonal on left side */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j])
			return false;

	/* Check lower diagonal on left side */
	for (i = row, j = col; j >= 0 && i < size; i++, j--)
		if (board[i][j])
			return false;

	return true;
}

/* A recursive utility function to solve N
Queen problem */
bool solveNQUtil(int** board, int col, int size)
{
	/* base case: If all queens are placed
	then return true */
	if (col >= size)
		return true;

	/* Consider this column and try placing
	this queen in all rows one by one */
	for (int i = 0; i < size; i++) {
		/* Check if the queen can be placed on
		board[i][col] */
		if (isSafe(board, i, col, size)) {
			/* Place this queen in board[i][col] */
			board[i][col] = 1;
			//print_array(board, size);
			//puts("");
			/* recur to place rest of the queens */
			
			if (solveNQUtil(board, col + 1, size))
			{
				counter++;
				printf("Rozwiazanie %d:\n", counter);
				print_array(board, size);
				puts("");
			}
			

			/* If placing queen in board[i][col]
			doesn't lead to a solution, then
			remove queen from board[i][col] */
			board[i][col] = 0; // BACKTRACK

		}
		
	}

	/* If the queen cannot be placed in any row in
		this colum col then return false */
	return false;
}

/* This function solves the N Queen problem using
Backtracking. It mainly uses solveNQUtil() to
solve the problem. It returns false if queens
cannot be placed, otherwise, return true and
prints placement of queens in the form of 1s.
Please note that there may be more than one
solutions, this function prints one of the
feasible solutions.*/



int main()
{

	int size = 0;
	scanf("%d", &size);
	int** array = (int**)calloc(size, sizeof(int*));
	for (int i = 0; i < size; i++)
		array[i] = (int*)calloc(size, sizeof(int));
	if (!array)
	{
		printf("Blad zalokowania pamieci");
		free_ptr(array, size);
	}
	else
	{
		fill_array(array, size);
		if (solveNQUtil(array, 0, size) == false) {
			printf("Ilosc rozwiazan dla rozmiaru %d: %d",size, counter);
			free_ptr(array, size);
			return false;
		}
	}
	return 0;
}