/* entidades.c  -  PESSOA B  (versão stub: troquem cada função pelo código real) */
#include <stdlib.h>
#include "entidades.h"

void entidadesExtrairDoMapa(Sala *sala) { (void)sala; }
Estrela *estrelaRemoverEm(Estrela **lista, int x, int y) { (void)lista; (void)x; (void)y; return NULL; }
void estrelaInserir(Estrela **lista, Estrela *e) { (void)lista; (void)e; }
int estrelaContar(const Estrela *lista) { (void)lista; return 0; }
Distracao *distracaoEm(Distracao *lista, int x, int y) { (void)lista; (void)x; (void)y; return NULL; }
Aliado *aliadoRemoverEm(Aliado **lista, int x, int y) { (void)lista; (void)x; (void)y; return NULL; }
ItemVida *itemVidaRemoverEm(ItemVida **lista, int x, int y) { (void)lista; (void)x; (void)y; return NULL; }
void entidadesDesenhar(const Sala *sala) { (void)sala; }
void salaLiberar(Sala *sala) { (void)sala; }
void estrelasLiberar(Estrela **lista) { (void)lista; }
void distracoesLiberar(Distracao **lista) { (void)lista; }
void aliadosLiberar(Aliado **lista) { (void)lista; }
void itensVidaLiberar(ItemVida **lista) { (void)lista; }
