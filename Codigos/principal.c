#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "cameraFunctions.h"

#define FPS 60

void errorMensage(char *mensage){
	fputs(mensage,stderr);
	exit(EXIT_FAILURE);
}

int main(){
	camera *cam=camera_inicializa(0);
	if(!cam)
		erro("Camera nao Iniciada\n");
	int x = cam->largura;
  	int y = cam->altura;
	if(!al_init())
    	erro("erro na inicializacao do allegro\n");

  	if(!al_init_image_addon())
    	erro("erro na inicializacao do adicional de imagem\n");

  	if(!al_init_primitives_addon())
    	erro("erro na inicializacao do adicional de primitivas\n");

  	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
  	if(!timer)
    	erro("erro na criacao do relogio\n");

  	ALLEGRO_DISPLAY *display = al_create_display(2 * x, y);
  	if(!display)
    	erro("erro na criacao da janela\n");

  	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  	if(!queue)
    	erro("erro na criacao da fila\n");

  	al_register_event_source(queue, al_get_timer_event_source(timer));
  	al_register_event_source(queue, al_get_display_event_source(display));
  	al_start_timer(timer);

  	unsigned char ***matriz = camera_aloca_matriz(cam);

  	ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);

 	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

 	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, x, y);

 	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, x, 0, x, y);
	/***Função para o tratamento de imagem****/
	//AGUARDE!!!
	/*****Fechando janelas e liberando matriz *****/
	al_destroy_bitmap(direita);

  	al_destroy_bitmap(esquerda);

  	camera_libera_matriz(cam, matriz);

  	/*****Finalizando aplicação*****/

  	al_stop_timer(timer);

  	al_unregister_event_source(queue, al_get_display_event_source(display));
  	al_unregister_event_source(queue, al_get_timer_event_source(timer));

  	al_destroy_event_queue(queue);
  	al_destroy_display(display);
  	al_destroy_timer(timer);

  	al_shutdown_primitives_addon();
  	al_shutdown_image_addon();
  	al_uninstall_system();

  	camera_finaliza(cam);

  return EXIT_SUCCESS;
}
