#include "init_al.h"

int init_fun()
{
	if (!al_init()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}
	else {
		al_init_ttf_addon();
		al_init_primitives_addon();
		al_install_keyboard();
		al_init_image_addon();
		return 1;
	}
	
	
}