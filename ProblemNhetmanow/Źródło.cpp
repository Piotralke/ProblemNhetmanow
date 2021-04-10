#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_audio.h>


int main()
{
	al_install_audio;
	al_load_sample("elephant.ogg");
	al_uninstall_audio;
}