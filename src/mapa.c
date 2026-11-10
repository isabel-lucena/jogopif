/* mapa.c  -  PESSOA A  (versão stub: troquem cada função pelo código real) */
#include <stdio.h>
#include <string.h>
#include "mapa.h"

int mapaCarregar(Sala *sala, const char *arquivo) { (void)sala; (void)arquivo; return 1; }
void mapaDesenhar(const Sala *sala) { (void)sala; }
char mapaCelula(const Sala *sala, int x, int y) { (void)sala; (void)x; (void)y; return CH_CHAO; }
int mapaEhParede(const Sala *sala, int x, int y) { (void)sala; (void)x; (void)y; return 0; }
int mapaQuebrarParede(Sala *sala, int x, int y) { (void)sala; (void)x; (void)y; return 0; }
Posicao mapaAcharPorta(const Sala *sala, char destino) { (void)sala; (void)destino; Posicao p = { -1, -1 }; return p; }
