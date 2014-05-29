#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Essa função vai capturar e registrar em um arquivo txt tudo que for colocado no parametro.

void ArquivoLog(char *msg) {
	FILE *ArquivoLog;
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	int dia = t->tm_mday;
	int mes = t->tm_mon + 1;
	int ano = t->tm_year + 1900;
	int hora = t->tm_hour;
	int minuto = t->tm_min;
	int segundo = t->tm_sec;

	ArquivoLog = fopen("LogInterno.txt", "a");
		
		fprintf(ArquivoLog, "%d:%d:%d %d/%d/%d - \"%s\"\n", hora, minuto, segundo, dia, mes, ano, msg);
		fprintf(ArquivoLog, "--\n");

	fclose(ArquivoLog);
}

void erro(char *msg){
	printf("%s\n", msg);
	ArquivoLog(msg);
	exit(EXIT_FAILURE);
}

