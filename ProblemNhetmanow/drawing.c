/** @file drawing.c
* Plik drawing.c zawiera implementacje funkcji odpowiedzialnych za wyświetlanie elementów programu na ekranie.
*/

#include "drawing.h"

/**
* Funkcja draw_mario() wyświetla na ekranie Mario przedstawiającego ilość rozwiązań.
* @param mario wskaźnik na bitmapę mario
* @param font wskaźnik na czcionkę 
*/

void draw_mario(ALLEGRO_BITMAP* mario, ALLEGRO_FONT* font) 
{
	al_draw_bitmap(mario, 0, 0, 0);
	al_draw_justified_text(font, al_map_rgb(0, 0, 0), 233, 468, 560, 4, 2, "Ilosc rozwiazan");
	al_draw_justified_textf(font, al_map_rgb(0, 0, 0), 233, 468, 600, 4, 3, "%d", counter);
	al_draw_justified_text(font, al_map_rgb(255, 0, 0), 233, 468, 640, 4, 2, "Wcisnij dowolny");
	al_draw_justified_text(font, al_map_rgb(255, 0, 0), 233, 468, 680, 4, 2, "klawisz by wyjsc");
}



/**
* Funkcja draw() rysuje na ekranie szachownicę oraz hetmanów w odpowiednich miejscach. 
* @param array dynamiczna tablica dwuwymiarowa reprezentująca szachownicę
* @param size rozmiar szachownicy 
* @param hetman wskaźnik na bitmapę hetmana
*/

void draw(int** array, int size, ALLEGRO_BITMAP* hetman)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j % 2 ^ i % 2)
			{
				al_draw_filled_rectangle(
					0 + i * (W / size),
					0 + j * (H / size),
					0 + i * (W / size) + (W / size),
					0 + j * (H / size) + (H / size),
					al_map_rgb(0, 0, 0));
				if (array[i][j] == 1)
				{
					al_draw_scaled_bitmap(
						hetman, 0, 0, 1184, 1184,
						0 + i * (W / size),
						0 + j * (H / size),
						(W / size),
						(H / size), 0);
				}
			}
			else
			{
				al_draw_filled_rectangle(
					0 + i * (W / size),
					0 + j * (H / size),
					0 + i * (W / size) + (W / size),
					0 + j * (H / size) + (H / size),
					al_map_rgb(255, 255, 255));
				if (array[i][j] == 1)
				{
					al_draw_scaled_bitmap(
						hetman, 0, 0, 1184, 1184,
						0 + i * (W / size),
						0 + j * (H / size),
						(W / size),
						(H / size), 0);
				}
			}
		}
	}
}