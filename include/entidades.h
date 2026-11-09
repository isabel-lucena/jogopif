/* =====================================================================
 * entidades.h  -  PESSOA B
 *
 * Tudo que fica "em cima" do mapa: estrelas (verdadeiras e fake),
 * distrações (5 tipos, todas paradas), professores e itens de vida.
 * Cada coisa é um nó de lista encadeada criado com malloc pela Pessoa B.
 *
 * Regra das funções "RemoverEm": elas TIRAM o nó da lista mas NÃO dão
 * free. Quem recebeu o nó decide o que fazer com ele.
 * ===================================================================== */
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "tipos.h"

/* ----- Criar ----- */

/* Varre sala->mapa e cria um nó para cada '*', 'F', 'D', 'P' e '+'.
 * Guarda a posição do '@' em sala->inicio e troca todos esses caracteres por ' '.
 * Tipo da distração e presente do professor: (sugestão) sorteados com rand().
 * Memória: cria todos os nós da sala.
 * Quem usa: C, em jogoIniciar, logo depois de mapaCarregar. */
void entidadesExtrairDoMapa(Sala *sala);

/* ----- Estrelas ----- */

/* Tira da lista a estrela que está em (x, y) e devolve ela. NULL se não tem.
 * NÃO dá free: verdadeira vai para jogador.coletadas; fake a Pessoa C libera.
 * Quem usa: C, em jogadorMover. */
Estrela *estrelaRemoverEm(Estrela **lista, int x, int y);

/* Coloca a estrela e no começo da lista.
 * Quem usa: C, para guardar em jogador.coletadas. */
void estrelaInserir(Estrela **lista, Estrela *e);

/* Conta as estrelas verdadeiras da lista (ignora as fake).
 * Quem usa: C, no HUD e na saída. */
int estrelaContar(const Estrela *lista);

/* ----- Distrações ----- */

/* Devolve a distração que está em (x, y), ou NULL.
 * Só olha: o nó continua na lista, NÃO dar free.
 * Quem usa: C, em jogadorMover. */
Distracao *distracaoEm(Distracao *lista, int x, int y);

/* ----- Professores e vida ----- */

/* Tira da lista o professor em (x, y) e devolve ele. NULL se não tem.
 * NÃO dá free: a Pessoa C aplica o presente e libera.
 * Quem usa: C, em jogadorMover. */
Aliado *aliadoRemoverEm(Aliado **lista, int x, int y);

/* Tira da lista o '+' em (x, y) e devolve ele. NULL se não tem.
 * NÃO dá free: a Pessoa C soma a vida e libera.
 * Quem usa: C, em jogadorMover. */
ItemVida *itemVidaRemoverEm(ItemVida **lista, int x, int y);

/* ----- Desenhar ----- */

/* Desenha estrelas (amarelo, fake igual), distrações (vermelho neon,
 * com a letra do tipo), professores (azul escuro) e vidas (magenta).
 * Quem usa: C, em jogoDesenhar. */
void entidadesDesenhar(const Sala *sala);

/* ----- Liberar ----- */

/* Libera as 4 listas da sala e deixa todas em NULL.
 * Não mexe em jogador.coletadas.
 * Quem usa: C, em jogoLiberar. */
void salaLiberar(Sala *sala);

/* Liberam uma lista inteira e deixam *lista = NULL.
 * Quem usa: salaLiberar; C também usa estrelasLiberar para jogador.coletadas. */
void estrelasLiberar(Estrela **lista);
void distracoesLiberar(Distracao **lista);
void aliadosLiberar(Aliado **lista);
void itensVidaLiberar(ItemVida **lista);

#endif
