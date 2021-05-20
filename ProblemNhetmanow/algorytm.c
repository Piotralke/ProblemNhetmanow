#include "algorytm.h"

counter = 0;
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
bool solveNhetman(int** board, int col, int size, ALLEGRO_BITMAP* hetman, FILE* file)
{
	/* glowny warunek: jezeli wszystkie hetmany sa ustawione zwroc true */
	if (col >= size)
		return true;
	/* Sprawdza kolumne i sprawdza czy moze postawic hetmana we wszystkich wierszach po kolei */
	for (int i = 0; i < size; i++) {
		/* Sprawdza czy hetman moze zostac postawiony w board[i][col]] */
		if (isSafe(board, i, col, size)) {
			/* Stawia hetmana w board[i][col] */
			board[i][col] = 1;

			/* stawia pozostale hetmany */
			draw(board, size, hetman);
			al_flip_display();
			if (solveNhetman(board, col + 1, size, hetman, file))
			{
				counter++;
				fprintf(file, "Rozwiazanie %d:\n", counter);
				print_array(board, size, file);
				fprintf(file, "\n");
			}


			/* Jezeli stawianie hetmanow na planszy nie prowadzi do rozwiazania, usuwa hetmany z planszy  */
			board[i][col] = 0;

		}

	}

	/* Jezeli hetman nie moze zostac postawiony w zadnym wierszu w tej kolumnie zwraca false */
	return false;
}