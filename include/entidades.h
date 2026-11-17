#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "tipos.h"

/* Pessoa B: entidades sobre o mapa. Os nos sao criados com malloc.
 * Funcoes RemoverEm transferem o no removido; elas nao dao free. */

/* Criar entidades a partir dos simbolos do mapa. */
void entidadesExtrairDoMapa(Sala *sala);

/* Estrelas. */
Estrela *estrelaRemoverEm(Estrela **lista, int x, int y);
void estrelaInserir(Estrela **lista, Estrela *e);
int estrelaContar(const Estrela *lista);

/* Distrações: consulta sem remover da lista. */
Distracao *distracaoEm(Distracao *lista, int x, int y);

/* Professores e itens de vida. */
Aliado *aliadoRemoverEm(Aliado **lista, int x, int y);
ItemVida *itemVidaRemoverEm(ItemVida **lista, int x, int y);

/* Desenho das entidades com raylib. */
void entidadesDesenhar(const Sala *sala);

/* Liberacao das listas. Todas as funcoes deixam a lista em NULL. */
void salaLiberar(Sala *sala);
void estrelasLiberar(Estrela **lista);
void distracoesLiberar(Distracao **lista);
void aliadosLiberar(Aliado **lista);
void itensVidaLiberar(ItemVida **lista);

#endif
