#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "inicializar.h"
#include "camera.h"
#include "define.h"
#include "ArquivoLog.h"

void captura(camera *cam, int *coordenadas);
void Ball(camera *cam, ALLEGRO_DISPLAY *display);
void Allegro(){	
		camera *cam = camera_inicializa(0);
	if(!cam)
		fprintf(stderr,"Erro ao iniciar a camera.");

	ALLEGRO_DISPLAY *display = al_create_display(LARGURA, ALTURA);
	if(!display)
		erro("Falha ao criar display.");

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		erro("Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		erro("Falha ao criar evento QUEUE");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");
	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");

	al_start_timer(temporizador);	
	
	Ball(cam, display);
	camera_finaliza(cam);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	al_destroy_display(display);



  /**********/


  al_destroy_event_queue(EventoQueue);

  al_shutdown_primitives_addon();
  al_shutdown_image_addon();
  al_uninstall_system();
	
}

void Ball(camera *cam, ALLEGRO_DISPLAY *display){
	camera_atualiza(cam);
	int raio = 5;
	int aux_x = LARGURA/2;
	int aux_y = ALTURA/2;
	int direcao_y = 1;
	int direcao_x = 1;
	int *coordenadas = malloc(sizeof(int));
	ALLEGRO_COLOR blue = al_map_rgb(0,0,255);
	ALLEGRO_COLOR green = al_map_rgb(0,255,0);
	ALLEGRO_COLOR ball = al_map_rgb(255,0,255);
	ALLEGRO_COLOR reset = al_map_rgb(0,0,0);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);		

	while(1){
		camera_copia(cam, cam->quadro, esquerda);
		captura(cam, coordenadas);
		if((coordenadas[0] <= aux_x+50) && (coordenadas[1] <= aux_y+50)){
			if((coordenadas[0] == aux_x) && (coordenadas[1] == aux_y)){
				al_draw_filled_circle(coordenadas[0],coordenadas[1], raio, ball);
			}
			al_draw_filled_circle(coordenadas[0],coordenadas[1], raio, green);
		}
		else if((coordenadas[0] > aux_x+50) && (coordenadas[1] > aux_y+50)){
			al_draw_filled_circle(coordenadas[0],coordenadas[1], raio, blue);
		}
		al_flip_display();
		al_clear_to_color(reset);
		aux_x += 1.0 * direcao_x;
		aux_y += 1.0 * direcao_y;
	
		if (aux_x > LARGURA - raio){
			direcao_x = -1;
			aux_x = LARGURA - raio;
		}
		else if ( aux_x < raio){
			direcao_x = 1;
			aux_x = raio;
		}
	
		if(aux_y > ALTURA - raio){
			direcao_y = -1;
			aux_y = ALTURA - raio;
		}
		else if(aux_y < raio){
			direcao_y = 1;
			aux_y = raio;
		}
	}
	free(coordenadas);
}

void captura(camera *cam, int *coordenadas){
	camera_atualiza(cam);
	//Iniciando
	float marca_x = 0;
	float marca_y = 0;
	
	int cn = 0;
	int y = 0;
	int x = 0;
        //Esse for esta fazendo a atualizacao da tela por frame, dessa forma ele esta atualizando os pixels de cor que esta identificando
	for(y = 0; y < ALTURA; y++){
		for(x = 0; x < LARGURA; x++){
      //Essas variaveis estao recebendo o valor que a camera esta pegando, ou seja o valor rastreado por cada cor
      int r = cam->quadro[y][x][0];
      int g = cam->quadro[y][x][1];
      int b = cam->quadro[y][x][2];

      if(
         (r > 150)
         &&
         (b < 75)
         &&
         (g < 75)
         ) {
				marca_y += y;
				marca_x += x;
				cn++;

			}

			else{
				marca_y = marca_y;
				marca_x = marca_x;
			}
		}
	}
	if(cn > 0){
		coordenadas[0] = marca_x / cn;
		coordenadas[1] = marca_y / cn;
	}
}