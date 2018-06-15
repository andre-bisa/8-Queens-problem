// Released in GNU GPL
// 8 queens  Copyright (C) 2018  Andrea Bisacchi

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>


typedef enum {
	VUOTA, REGINA
} CellaScacchiera;

#define DIM 8

void stampaScacchiera(CellaScacchiera scacchiera[DIM][DIM]);
void spostaRegina(CellaScacchiera scacchiera[DIM][DIM], int colonna);
bool validaRegina(CellaScacchiera scacchiera[DIM][DIM], int riga, int colonna);
bool valida(CellaScacchiera scacchiera[DIM][DIM]);

static struct timeval start, stop;

int main(int argc, char** argv) {
	
	CellaScacchiera scacchiera[DIM][DIM];
	
	for(int i = 0; i < DIM; i++)
		for(int j = 0; j < DIM; j++)
			scacchiera[i][j] = (i == 0) ? REGINA : VUOTA; // Inizializzo con le regine nella prima riga
	
	bool soluzioneValida = false;
	
	int numeroSoluzione = 0;
	
	gettimeofday(&start, NULL);
	
	while (!soluzioneValida) {
		spostaRegina(scacchiera, DIM-1);
		soluzioneValida = valida(scacchiera);
		if (soluzioneValida) {
			numeroSoluzione++;
			printf("Soluzione numero %d:\n", numeroSoluzione);
			stampaScacchiera(scacchiera);
			soluzioneValida = false;
		}
	}
	
}

bool valida(CellaScacchiera scacchiera[DIM][DIM]) {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (scacchiera[i][j] == REGINA) {
				if (!validaRegina(scacchiera, i, j))
					return false;
			}
		}
	}
	return true;
}

bool validaRegina(CellaScacchiera scacchiera[DIM][DIM], int riga, int colonna) {
	for (int i = 1; i < DIM; i++) {
		
		if (colonna+i<DIM && scacchiera[riga][colonna+i] == REGINA)
			return false;
		if (riga-i>=0 && scacchiera[riga-i][colonna] == REGINA)
			return false;
		if (riga+i<DIM && colonna+i<DIM && scacchiera[riga+i][colonna+i] == REGINA)
			return false;
		if (riga-i>=0 && colonna-i>=0 && scacchiera[riga-i][colonna-i] == REGINA)
			return false;
		if (riga+i<DIM && colonna-i>=0 && scacchiera[riga+i][colonna-i] == REGINA)
			return false;
		if (riga-i>=0 && colonna+i<DIM && scacchiera[riga-i][colonna+i] == REGINA)
			return false;
		
	}
	return true;
}

void spostaRegina(CellaScacchiera scacchiera[DIM][DIM], int colonna) {
	int posizioneUltimaRegina = -1;
	
	for(int i = 0; i < DIM && posizioneUltimaRegina<0; i++) {
		if (scacchiera[i][colonna] == REGINA)
			posizioneUltimaRegina = i;
	}
	
	scacchiera[posizioneUltimaRegina][colonna] = VUOTA;
	if (posizioneUltimaRegina != DIM-1) { // non sono all'ultima riga
		scacchiera[posizioneUltimaRegina+1][colonna] = REGINA;
	} else { //ultima riga -> la rimetto all'inizio
		scacchiera[0][colonna] = REGINA;
		if (colonna == 0) {
			gettimeofday(&stop, NULL);
			printf ("Tempo totale = %f secondi\n", (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double) (stop.tv_sec - start.tv_sec));
			exit(0);
		} else {
			spostaRegina(scacchiera, colonna-1);
		}
	}
}

void stampaScacchiera(CellaScacchiera scacchiera[DIM][DIM]) {
	for(int i = 0; i < DIM; i++) {
		for(int j = 0; j < DIM; j++) {
			printf("[%d]", scacchiera[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
