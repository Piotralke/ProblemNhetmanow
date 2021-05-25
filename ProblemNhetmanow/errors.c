/// @file errors.c

#include "errors.h"

/**
* Funkcja errors() odpowiada za zakończenie programu w wypadku występującego błedu.
* @param display wskaźnik na ekran aplikacji
* @param hetman wskaźnik na bitmapę hetmana
* @param mario wskaźnik na bitmapę mario
* @param font wskaźnik na czcionkę 
* @param wskaźnik na plik z rozwiązaniami 
* @return -1 w przypadku wykrycia błedu 
* @return 1 w przypadku poprawnego działania 
*/
int errors(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* hetman, ALLEGRO_BITMAP* mario, ALLEGRO_FONT* font, FILE* file) 
{
	if (!display) {
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}

	if (!hetman)
	{
		fprintf(stderr, "Failed to create bitmap!\n");
		return -1;
	}

	if (!mario)
	{
		fprintf(stderr, "Failed to create bitmap!\n");
		return -1;
	}

	if (!font)
	{
		fprintf(stderr, "Failed to initialize font!\n");
		return -1;
	}

	if (file == NULL)
	{
		fprintf(stderr, "Blad otwarcia pliku");
		return -1;
	}
	return 1;
}