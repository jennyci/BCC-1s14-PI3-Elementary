
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "../libs/inicializar.h"
#include "../libs/ArquivoLog.h"
#include "../libs/rastreamento.h"

int main(){
	//Iniciando
	iniciarAllegro();
	ArquivoLog("Jogo Iniciado!");
	Allegro();
	finalizarAllegro();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}