#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

/*
Funkcja sprawdza czy hetman moze zostac postawiony na board[row][col].
Funkcja jest przywolywana kiedy hetmany sa juz  w kolumnach od 0 do [col]-1.
Wiec musimy sprawdzac tylko lewa strone dla tych hetmanow co atakuja.
 */
bool isSafe(int** board, int row, int col, int size)
{
	int i, j;

	/* Sprawdza rzad z lewej strony */
	for (i = 0; i < col; i++)
		if (board[row][i])
			return false;

	/* Sprawdza gorna przekatna z lewej strony */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j])
			return false;

	/* Sprawdza dolna przekatna z lewej strony */
	for (i = row, j = col; j >= 0 && i < size; i++, j--)
		if (board[i][j])
			return false;

	return true;
}

/* Funkcja rekurencyjna rozwiazujaca problem N hetmanow */
bool solveNhetman(int** board, int col, int size)
{
	/* glowny warunek: jezeli wszystkie chetmany sa ustawione zwroc true */
	if (col >= size)
		return true;

	/* Sprawdza kolumne i sprawdza czy moze postawic hetmana we wszystkich wierszach po kolei */
	for (int i = 0; i < size; i++) {
		/* Sprawdza czy hetman moze zostac postawiony w board[i][col]] */
		if (isSafe(board, i, col, size)) {
			/* Stawia hetmana w board[i][col] */
			board[i][col] = 1;

			/* stawia pozostale hetmany */

			if (solveNhetman(board, col + 1, size))
			{
				counter++;
				printf("Rozwiazanie %d:\n", counter);
				print_array(board, size);
				puts("");
			}


			/* Jezeli stawianie hetmanow na planszy nie prowadzi do rozwiazania, usuwa hetmany z planszy  */
			board[i][col] = 0;

		}

	}

	/* Jezeli hetman nie moze zostac postawiony w zadnym wierszu w tej kolumnie zwraca false */
	return false;
}





int main()
{

	int size = 0;
	scanf("%d", &size);
	assert(size > 0);
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
		if (solveNhetman(array, 0, size) == false) {
			printf("Ilosc rozwiazan dla rozmiaru %d: %d", size, counter);
			free_ptr(array, size);
			return false;
		}
	}
	return 0;
}