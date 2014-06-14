#include "bibliotecas.h"

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
void cameraRastreia( camera *cam,int *px, int *py){

  camera_atualiza(cam);
    int x = 0, y = 0;
    int cyr = 0;
    int cxr = 0;
    int cnr = 0;

    int h, s, v;

    for(y = 0; y < cam->altura; y++){
        for(x = 0; x < cam->largura; x++){
            RGB2HSV(cam->quadro[y][x][0], cam->quadro[y][x][1], cam->quadro[y][x][2], &h, &s, &v);

            if(h < 10 || h > 345)
              if(s > 75 && v > 75){
                  cyr += y;
                  cxr += x;
                  cnr++;
              }
        }
    }

    /**********/
  
    if(cnr > 15){
        x = cxr / cnr;
        y = cyr / cnr;
        al_draw_circle(x, y, 10, al_map_rgb(0, 0, 255),1);
        al_draw_circle(x, y, 20, al_map_rgb(0, 0, 255),1);
        al_draw_circle(x, y, 30, al_map_rgb(0, 0, 255),1);
        al_draw_circle(x, y, 40, al_map_rgb(0, 0, 255),1);
        al_draw_circle(x, y, 50, al_map_rgb(0, 0, 255),1);
        al_draw_filled_circle(x, y, 5, al_map_rgb(0, 0, 255));
    }
    *px = x;
    *py = y;
}