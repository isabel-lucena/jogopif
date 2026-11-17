
#ifndef MAPA_H
#define MAPA_H

#include "tipos.h"

int mapaCarregar(Sala *sala, const char *arquivo);

void mapaDesenhar(const Sala *sala);

char mapaCelula(const Sala *sala, int x, int y);

int mapaEhParede(const Sala *sala, int x, int y);

int mapaQuebrarParede(Sala *sala, int x, int y);

Posicao mapaAcharPorta(const Sala *sala, char destino);

#endif
