#include "errors.h"

extern int errors(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* hetman, ALLEGRO_BITMAP* mario, ALLEGRO_FONT* font, FILE* file) 
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
}