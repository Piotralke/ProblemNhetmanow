/** @file algorytm.c
* W pliku algorytm.c znajdują się funkcje odpowiadające za działanie algorytmu.
*/
#include "algorytm.h"
/// @param counter to parametr zliczający ilość rozwiązań.
counter = 0;
/**
* Funkcja jest przywoływana kiedy hetmany są już  w kolumnach od 0 do[col] - 1.
* Więc musimy sprawdzać tylko lewą stronę dla tych hetmanów co atakują.
* Funkcja sprawdza czy hetman może zostać postawiony na board[row][col].
* Funkcja jest przywoływana kiedy hetmany są już w kolumnach od 0 do [col]-1.
* Więc musimy sprawdzac tylko lewą stronę dla tych hetmanów co atakują.
* @param board jest to dynamiczna tablica dwuwymiarowa reprezentująca szachownicę
* @param row aktualny wiersz szachownicy który jest badany 
* @param col aktualna kolumna szachownicy która jest badana
* @param size rozmiar szachownicy 
* @return false w przypadku gdy dane pole nie będzie bezpieczne 
* @return true jeżeli pole jest bezpieczne 
*/

bool isSafe(int** board, int row, int col, int size)
{
	int i, j;

	/* Sprawdza rzad z lewej strony */
	for (i = 0; i < col; i++)
		if (board[row][i])
			return false;

	/* Sprawdza gorna przekatna z lewej strony  */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j])
			return false;

	/* Sprawdza dolna przekatna z lewej strony */
	for (i = row, j = col; j >= 0 && i < size; i++, j--)
		if (board[i][j])
			return false;

	return true;
}

/** Funkcja rekurencyjna rozwiazujaca problem N hetmanow.
* @param board jest to dynamiczna tablica dwuwymiarowa reprezentująca szachownicę
* @param col aktualna kolumna szachownicy która jest badana
* @param size rozmiar szachownicy
* @param hetman jest to wskaźnik na bitmapę z obrazkiem hetmana w postaci Księżniczki Peach 
* @param file jest to wskaźnik na plik, do którego zapisują się pomyślne rozwiązania
* @return true w przypadku jeżeli wszystkie hetmany są ustawione 
* @return false jezeli hetman nie moze zostac postawiony w zadnym wierszu w tej kolumnie 
*/

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