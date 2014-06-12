#include "bibliotecas.h"

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