/** @file handle_array.c
* W pliku handle_array.c znajdują się funkcje, które wykonują operacje na dynamicznej tablicy dwuwymiarowej (inicjacja szachownicy, zapis rozwiązań do pliku i zwalnianie pamięci)
*/
#include "handle_array.h"
/**
* Funkcja fill_array() inicjuje szachownicę wypełniając ją wartościami 0, które oznaczają, że miejsce na szachownicy jest puste.
* @param array szachownica w postaci dynamicznej tablicy dwuwymiarowej.
* @param size rozmiar szachownicy.
*/
void fill_array(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			array[i][j] = 0;
	}
}
/**
* Funkcja print_array() zapisuje rozwiązanie do pliku.
* @param array szachownica w postaci dynamicznej tablicy dwuwymiarowej.
* @param size rozmiar szachownicy.
* @param file wskaźnik na plik do którego będzie zapisywane rozwiązanie.
*/
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

/**
* Funkcja free_ptr() zwalnia pamięć dynamicznej tablicy dwuwymiarowej.
* @param array szachownica w postaci dynamicznej tablicy dwuwymiarowej.
* @param size rozmiar szachownicy.
*/
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