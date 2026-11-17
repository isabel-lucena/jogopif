
#ifndef RANKING_H
#define RANKING_H

#include "tipos.h"

Registro *rankingCarregar(const char *arquivo);

void rankingInserir(Registro **lista, const char *nome, int pontos);

void rankingSalvar(const Registro *lista, const char *arquivo);

void rankingDesenhar(const Registro *lista, int x, int y);

void rankingLiberar(Registro **lista);

#endif
