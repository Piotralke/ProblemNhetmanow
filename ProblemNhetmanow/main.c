/** @file main.c
 *  Plik main.c służy do kontaktu z użytkownikiem w postaci wyboru wielkości szachownicy. Odpowiada również za inicjacje funkcji 
 *  odpowiadających między innymi za: czcionkę, wyświetlanie elementów w tym samego display oraz występowanie błedów.
 *
 */

#include "include_lib.h"
#include "handle_array.h"
#include "drawing.h"
#include "algorytm.h"
#include "init_al.h"
#include "errors.h"


/**
 * Funkcja wait_for_keypress() czeka na wciśnięcie dowolnego klawisza przez użytkownika. Jest ona wywoływana na końcu programu po wyświetleniu łącznej liczby rozwiązań.
 */
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

/**
 * Funkcja main() jest główną funkcją programu. Zawarte są w niej najważniejsze inicjacje elementów potrzebnych do działania programów np: bitmap.
 * W funkcji zawarta jest pętla while odpowiedzialna za małe menu rozmiaru szachownicy. Po pętli inicjowana jest dynamiczna tablica dwuwymiarowa zależna od wybranego przez użytkownika rozmiaru.
 * Dalej wywoływany jest główny algorytm, a po jego zakończeniu wywoływane są funkcje niszczące i odinstalowywujące.
 * 
 */
int main()
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* hetman = NULL;
	ALLEGRO_BITMAP* mario = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	FILE* file = NULL;

	if (!init_fun()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(W, H);
	hetman = al_load_bitmap("hetman.png");
	mario = al_load_bitmap("mario.png");
	font = al_load_ttf_font("font.ttf", 28, ALLEGRO_TTF_MONOCHROME);
	file = fopen("rozwiazanie.txt", "w");

	if(!errors(display, hetman, mario, font, file)) {
		fprintf(stderr, "Failed to initialize one of allegro function!\n");
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
			draw_mario(mario,font,counter);
			al_flip_display();
			wait_for_keypress();
			free_ptr(array, size);
			return false;
		}
		al_destroy_display(display);
		al_shutdown_image_addon();
		al_uninstall_keyboard();
		al_shutdown_primitives_addon();
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(hetman);
		al_destroy_bitmap(mario);
		al_destroy_font(font);
		al_uninstall_system();
		
		if (fclose(file))
		{
			fprintf(stderr, "Blad zamkniecia pliku\n");
			return -1;
		}
	}
	
	
	
	return 0;
}