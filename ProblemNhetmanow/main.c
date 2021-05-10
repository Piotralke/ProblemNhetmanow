#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#define W 1000
#define H 1000

int counter = 0;
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
			fprintf(file,"%d\t", array[i][j]);
		}
		fprintf(file,"\n");
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


void wait_for_keypress()
{
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT event;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	do
		al_wait_for_event(event_queue, &event);
	while (event.type != ALLEGRO_EVENT_KEY_DOWN);

	al_destroy_event_queue(event_queue);
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

int main()
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* hetman = NULL;
	ALLEGRO_BITMAP* mario = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	if (!al_init()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	display = al_create_display(W, H);
	if (!display) {
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}
	if (!al_init_image_addon())
	{
		fprintf(stderr, "Failed to initialize bitmaps!\n");
		return -1;
	}
	hetman = al_load_bitmap("hetman.png");
	if (!hetman)
	{
		fprintf(stderr, "Failed to create bitmap!\n");
		return -1;
	}
	mario = al_load_bitmap("mario.png");
	if (!mario)
	{
		fprintf(stderr, "Failed to create bitmap!\n");
		return -1;
	}
	font = al_load_ttf_font("font.ttf", 28, ALLEGRO_TTF_MONOCHROME);
	if (!font)
	{
		fprintf(stderr, "Failed to initialize font!\n");
		return -1;
	}
	FILE* file;
	file = fopen("rozwiazanie.txt", "w");
	if (file == NULL)
	{
		fprintf(stderr, "Blad otwarcia pliku");
		return -1;
	}
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	bool working = 1;
	int size = 0;
	while (working)
	{
		ALLEGRO_EVENT ev;
		al_get_next_event(event_queue, &ev);
		al_draw_justified_text(font, al_map_rgb(255, 255, 255), 200, 800, 400, 4, 2, "Wybierz rozmiar szachownicy strzalkami:");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 500, 3, "%d", size);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_LEFT:
				if(size > 0)
					size--;
				break;
			case ALLEGRO_KEY_RIGHT:
				size++;
				break;
			case ALLEGRO_KEY_ENTER:
				working = 0;
				break;
			}
		}
	}
	int** array = (int**)calloc(size, sizeof(int*));
	for (int i = 0; i < size; i++)
		array[i] = (int*)calloc(size, sizeof(int));
	if (!array)
	{
		fprintf(stderr, "Blad zalokowania pamieci");
		free_ptr(array, size);
		return -1;
	}
	else
	{
		
		fill_array(array, size);
		
		if (solveNhetman(array, 0, size, hetman, file) == false) {
			fprintf(file, "Ilosc rozwiazan dla rozmiaru %d: %d\n", size, counter);
			al_draw_bitmap(mario, 0, 0, 0);
			al_draw_justified_text(font, al_map_rgb(0, 0, 0), 233, 468, 560, 4, 2, "Ilosc rozwiazan");
			al_draw_justified_textf(font, al_map_rgb(0, 0, 0), 233, 468, 600, 4, 3, "%d", counter);
			al_draw_justified_text(font, al_map_rgb(255, 0, 0), 233, 468, 640, 4, 2, "Wcisnij dowolny");
			al_draw_justified_text(font, al_map_rgb(255, 0, 0), 233, 468, 680, 4, 2, "klawisz by wyjsc");
			al_flip_display();
			wait_for_keypress();
			free_ptr(array, size);
			return false;
		}
		al_destroy_display(display);
		al_shutdown_image_addon();
		al_uninstall_keyboard();
		al_destroy_event_queue(event_queue);
		if (fclose(file))
		{
			fprintf(stderr, "Blad zamkniecia pliku\n");
			return -1;
		}
	}
	
	return 0;
}