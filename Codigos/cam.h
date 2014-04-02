#include <opencv/hoghgui.h>
#include <allegro5/allegro.h>
typedef struct {
  unsigned char ***camQuadro;
  int camLargura, camAltura;
  CvCapture *camCapture;
} camera;
camera *camera_inicializa(int i);
void finalizarCamera(camera *cam);

void atualizarCamera(camera *cam);
void copiarCamera(camera *cam, unsigned char ***matriz, ALLEGRO_BITMAP *bitmap);

unsigned char ***alocarMatrizCamera(camera *cam);
void liberaMatrizCamera(camera *cam, unsigned char ***matriz);
