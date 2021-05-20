#include "include_lib.h"
#include "handle_array.h"
#include "drawing.h"
#include "algorytm.h"
#include "init_al.h"
#include "errors.h"

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
		al_destroy_event_queue(event_queue);
		if (fclose(file))
		{
			fprintf(stderr, "Blad zamkniecia pliku\n");
			return -1;
		}
	}
	
	return 0;
}