#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "ArquivoLog.h"
#include "define.h"
#include "camera.h"
void iniciarAllegro(){

	if(!al_init()){
		erro("Falha ao iniciar o Allegro.\n");
	}

	if(!al_init_image_addon()){
		erro("Falha ao iniciar a biblioteca de imagens do Allegro.\n");
	}

	if(!al_init_primitives_addon()){
		erro("Falha ao carregar primitive_addons.\n");
	}

}

void finalizarAllegro(){
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_system();
}