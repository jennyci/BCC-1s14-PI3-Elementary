#include "bibliotecas.h"
#define FPS 60

typedef struct {
  int pos_x,pos_y;
  ALLEGRO_BITMAP *elemento;
  bool status;
} Disco;

bool abrirJogo(int x, int y,int *fps,int *tempo,ALLEGRO_FONT *font,ALLEGRO_COLOR font_color){
  char seg[100];
  
  if(x >=40 && x<=200 && y <=460 && y>=360){
              *fps = *fps+1;
              sprintf(seg, "%d", *tempo); 
              al_draw_text(font, font_color, 120, 200, 0,seg);
              

              if(*fps >= 3){
                *tempo=*tempo-1;
                if(*tempo == 0){
                  
                 return true;
                }
                *fps = 0;
              }
          return false;

              
          }else if(*fps !=0 && *tempo != 5){

            *fps = 0;*tempo = 5;
          }
              al_draw_text(font, font_color, 120, 200, 0,"Escolha um elemento para iniciar!");
        
          return false;
}
void carregarDiscos(Disco **discos){
  discos[1] = malloc(sizeof(Disco));
  discos[1]->elemento = al_load_bitmap("Imagens/agua.png");
  discos[1]->pos_x = rand()%9 * 55;
  discos[1]->pos_y = 0;
  discos[1]->status = false;
  discos[2] = malloc(sizeof(Disco));
  discos[2]->elemento = al_load_bitmap("Imagens/fogo.png");
  discos[2]->pos_x = rand()%9 * 55;
  discos[2]->pos_y = 0;
  discos[2]->status = false;
  discos[3] = malloc(sizeof(Disco));
  discos[3]->elemento = al_load_bitmap("Imagens/planta.png");
  discos[3]->pos_x = rand()%9 * 55;
  discos[3]->pos_y = 0;
  discos[3]->status = false;
  discos[4] = malloc(sizeof(Disco));
  discos[4]->elemento = al_load_bitmap("Imagens/agua.png");
  discos[4]->pos_x = rand()%9 * 55;
  discos[4]->pos_y = 0;
  discos[4]->status = false;
  discos[5] = malloc(sizeof(Disco));
  discos[5]->elemento = al_load_bitmap("Imagens/fogo.png");
  discos[5]->pos_x = rand()%9 * 55;
  discos[5]->pos_y = 0;
  discos[5]->status = false;
  discos[6] = malloc(sizeof(Disco));
  discos[6]->elemento = al_load_bitmap("Imagens/planta.png");
  discos[6]->pos_x = rand()%9 * 55;
  discos[6]->pos_y = 0;
  discos[6]->status = false;
  discos[7] = malloc(sizeof(Disco));
  discos[7]->elemento = al_load_bitmap("Imagens/agua.png");
  discos[7]->pos_x = rand()%9 * 55;
  discos[7]->pos_y = 0;
  discos[7]->status = false;
  discos[8] = malloc(sizeof(Disco));
  discos[8]->elemento = al_load_bitmap("Imagens/fogo.png");
  discos[8]->pos_x = rand()%9 * 55;
  discos[8]->pos_y = 0;
  discos[8]->status = false;
  discos[9] = malloc(sizeof(Disco));
  discos[9]->elemento = al_load_bitmap("Imagens/planta.png");
  discos[9]->pos_x = rand()%9 * 55;
  discos[9]->pos_y = 0;
  discos[9]->status = false;
}
void erro(char *mensagem) {
  fputs(mensagem, stderr);

  exit(EXIT_FAILURE);
}

int main() {
  bool menu = true;

  ALLEGRO_COLOR  font_color;
  ALLEGRO_FONT *font;
  camera *cam = camera_inicializa(0);
  if(!cam)
    erro("erro na inicializacao da camera\n");
  int x = 0, y =  0;
  int largura = cam->largura;
  int altura = cam->altura;
  int fps = 0,tempo = 5;
  int ndisco = 9;

  if(!al_init())
    erro("erro na inicializacao do allegro\n");

  if(!al_init_image_addon())
    erro("erro na inicializacao do adicional de imagem\n");

  al_init_font_addon();
  al_init_ttf_addon();

    font_color = al_map_rgb(0, 0, 0);
    
    font = al_load_ttf_font("Fontes/Blokletters-Viltstift.ttf", 20, 0);

  if(!al_init_primitives_addon())
    erro("erro na inicializacao do adicional de primitivas\n");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
  if(!timer)
    erro("erro na criacao do relogio\n");

  ALLEGRO_DISPLAY *display = al_create_display(2 * largura,altura);
  if(!display)
    erro("erro na criacao da janela\n");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  if(!queue)
    erro("erro na criacao da fila\n");

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(display));

  al_start_timer(timer);
  
  unsigned char ***matriz = camera_aloca_matriz(cam);
  ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
  ALLEGRO_BITMAP *fundo = al_load_bitmap("Imagens/Elementary2.png");

  if(!fundo)
    erro("erro ao carregar Elementary.png");

  ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);
  ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);

  /**********/
  Disco *discos[9];
  carregarDiscos(discos);

  int ultimoDisco = 0;
  int distance = 0;
  int desenhar = 0;
  int terminar = 0;
  al_set_target_bitmap(esquerda);
  al_draw_bitmap(fundo,0,0,0);
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
   
    }

    if(terminar)
      break;

    if(desenhar && al_is_event_queue_empty(queue)) {
      desenhar = 0;
      camera_atualiza(cam);
      mediana(cam);
      /**********/
      al_set_target_bitmap(esquerda);
      al_draw_bitmap(fundo,0,0,0);
      
      if(!menu){
        for(int aux1 = 1; aux1 <= ndisco;aux1++){
          if((!discos[aux1]->status && distance > 200) || ultimoDisco==0 ){
            printf("%d\n",aux1 );
            al_draw_bitmap(discos[aux1]->elemento,discos[aux1]->pos_x,discos[aux1]->pos_y,0);
            discos[aux1]->status = true;
            distance = 0;
            ultimoDisco = aux1;
            printf("Ultimo disco: %d\n",aux1 );
            break;
          }else{
            discos[aux1]->pos_y+=10;
            al_draw_bitmap(discos[aux1]->elemento,discos[aux1]->pos_x,discos[aux1]->pos_y,0);
          }
            distance = discos[ultimoDisco]->pos_y;
          /*if(discos[1]->pos_y > 480){
            al_draw_text(font, al_map_rgb(255, 0, 0), 200, 200, 0,"VOCÊ PERDEU!!!");
            al_flip_display();
            al_rest(5);
            break;
          }
      al_draw_text(font, al_map_rgb(255, 255, 255), 240, 5, 0,"PONTUAÇÃO");*/
        }

      }
      if(menu){
        if(abrirJogo(x,y,&fps,&tempo,font, font_color)){
          fundo = al_load_bitmap("Imagens/galaxia.png");
          menu = false;
        }
      }
      cameraRastreia(cam,&x,&y);
      

      al_set_target_bitmap(direita);
      camera_copia(cam, cam->quadro, direita);
      al_flip_display();
    }
  }
  al_destroy_bitmap(direita);
  al_destroy_bitmap(fundo);
  al_destroy_bitmap(esquerda);
  camera_libera_matriz(cam, matriz);
int fri = 9;
while(fri != 0){
  free(discos[fri]);
  fri--;

}


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
