#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "tipos.h"

void entidadesExtrairDoMapa(Sala *sala);

Estrela *estrelaRemoverEm(Estrela **lista, int x, int y);
void estrelaInserir(Estrela **lista, Estrela *e);
int estrelaContar(const Estrela *lista);

Distracao *distracaoEm(Distracao *lista, int x, int y);

Aliado *aliadoRemoverEm(Aliado **lista, int x, int y);
ItemVida *itemVidaRemoverEm(ItemVida **lista, int x, int y);

void entidadesDesenhar(const Sala *sala);

void salaLiberar(Sala *sala);
void estrelasLiberar(Estrela **lista);
void distracoesLiberar(Distracao **lista);
void aliadosLiberar(Aliado **lista);
void itensVidaLiberar(ItemVida **lista);

#endif
