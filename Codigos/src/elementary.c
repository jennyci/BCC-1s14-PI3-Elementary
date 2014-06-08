#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "../libs/camera.h"



#define FPS 60
void RGB2HSV(int red, int green, int blue, int *h, int *s, int *v){
  float r = (float)red/255;
  float g = (float)green/255;
  float b = (float)blue/255;
  
    float cMax, cMin;
  
    if(r >= b && r >= g){
      if(g > b)
          cMin = b;
  
      else
          cMin = g;

      cMax = r;
    }
  
    else if(b >= g){
      if(g > r)
          cMin = r;
  
      else
          cMin = g;
  
      cMax = b;
    }
  
    else{
      if(r > b)
          cMin = b;
  
      else
          cMin = r;
  
      cMax = g;
    }
  
    float variacaoCor = cMax - cMin;

    if(variacaoCor != 0){ 
      if(cMax == r){
          if(g >= b)
            *h = 60 * ((g - b) / variacaoCor);
    
          else
            *h = 60 * ((g - b) / variacaoCor) + 360;
      }
    
      else if(cMax == g)
          *h = 60 * ((b - r) / variacaoCor) + 120;
    
      else
          *h = 60 * ((r - g) / variacaoCor) + 240;
    }

    else
      *h = 0;
  
    *s = variacaoCor/cMax * 100;
  
    *v = cMax * 100;
}
void cameraRastreia(unsigned char ***matriz, camera *cam,  ALLEGRO_BITMAP *direita){
  camera_atualiza(cam);

    int x, y;
    int cyr = 0;
    int cxr = 0;
    int cnr = 0;

    int h, s, v;

    for(y = 0; y < cam->altura; y++){
        for(x = 0; x < cam->largura; x++){
            RGB2HSV(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], &h, &s, &v);

            if(h < 25 || h > 345)
              if(s > 75 && v > 75){
                  cyr += y;
                  cxr += x;
                  cnr++;
              }
        }
    }

    /**********/
    camera_copia(cam, cam->quadro, direita);


    if(cnr > 20){
        x = cxr / cnr;
        y = cyr / cnr;
        al_draw_circle(x, y, 50, al_map_rgb(0, 0, 255),2);
        al_draw_filled_circle(x, y, 5, al_map_rgb(0, 0, 255));

    }

  
}


void erro(char *mensagem) {
  fputs(mensagem, stderr);

  exit(EXIT_FAILURE);
}



void mediana(camera *cam){
    int x, y;
    for(y = 0; y < cam->altura; y++){
	     for(x = 0; x < cam->largura; x++)
        	if(y > 0 && y < cam->largura - 1 && x > 0 && x < cam->altura - 1){
    				//Calculo da mediana
				    int aux = 0;
				    unsigned char buffer[3][9];
				    for(int dy = -1; dy < 1; dy++){
					    for(int dx = -1; dx < 1; dx++, aux++){
						    buffer[0][aux] = (double)(cam->quadro[y+dy][x+dx][0]);
                buffer[1][aux] = (double)(cam->quadro[y+dy][x+dx][1]);
                buffer[2][aux] = (double)(cam->quadro[y+dy][x+dx][2]);
					    }
				    }
				    for(aux = 0; aux <= 8; aux++){
					    for(int l = 0; l < aux; l++){
						    if(buffer[0][l] > buffer[0][l+1]){
							    int n = (int)buffer[0][l];
							    buffer[0][l] = buffer[0][l+1];
							    buffer[0][l+1] = n;
						}
            if(buffer[1][l] > buffer[1][l+1]){
              int n = buffer[1][l];
              buffer[1][l] = buffer[1][l+1];
							buffer[1][l+1] = n;
            }
            if(buffer[2][l] > buffer[2][l+1]){
              int n = buffer[2][l];
              buffer[2][l] = buffer[2][l+1];
							buffer[2][l+1] = n;
            }
					}
				}
				cam->quadro[y][x][0] = buffer[0][4];
        cam->quadro[y][x][1] = buffer[1][4];
        cam->quadro[y][x][2] = buffer[2][4];
			}
	 }
}


int main() {
  camera *cam = camera_inicializa(0);
  if(!cam)
    erro("erro na inicializacao da camera\n");

  int largura = cam->largura;
  int altura = cam->altura;

  if(!al_init())
    erro("erro na inicializacao do allegro\n");

  if(!al_init_image_addon())
    erro("erro na inicializacao do adicional de imagem\n");

  if(!al_init_primitives_addon())
    erro("erro na inicializacao do adicional de primitivas\n");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
  if(!timer)
    erro("erro na criacao do relogio\n");

  ALLEGRO_DISPLAY *display = al_create_display(2 * largura, altura);
  if(!display)
    erro("erro na criacao da janela\n");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  if(!queue)
    erro("erro na criacao da fila\n");

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(display));

  al_start_timer(timer);

  /**********/
  

  unsigned char ***matriz = camera_aloca_matriz(cam);

  ALLEGRO_COLOR cor = al_map_rgb_f(0, 255, 0);

  ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

  ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);

  ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);

  /**********/

  int desenhar = 0;
  int terminar = 0;
  while(1) {
    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      desenhar = 1;
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      terminar = 1;
      break;
    default:
      printf("evento desconhecido\n");
    }

    if(terminar)
      break;

    if(desenhar && al_is_event_queue_empty(queue)) {
      desenhar = 0;
      camera_atualiza(cam);
      mediana(cam);
      /**********/
cameraRastreia(matriz,cam,esquerda);//ONDE FICARÁ O ALLEGRO
camera_copia(cam,cam->quadro,direita);
            /**********/
            /**********/
            al_flip_display();
        }
    }

  /**********/

  al_destroy_bitmap(direita);

  al_destroy_bitmap(esquerda);

  camera_libera_matriz(cam, matriz);

  /**********/

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
