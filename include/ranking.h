/* =====================================================================
 * ranking.h  -  PESSOA A
 *
 * O ranking é uma lista encadeada em ordem de pontos (maior primeiro),
 * guardada no arquivo ranking.txt (uma linha por jogador: nome pontos).
 * A Pessoa A cria os nós (malloc) e também é quem libera (rankingLiberar).
 * ===================================================================== */
#ifndef RANKING_H
#define RANKING_H

#include "tipos.h"

/* Lê o arquivo e monta a lista ordenada.
 * Se o arquivo não existe (primeira partida), devolve NULL: ranking vazio, não é erro.
 * Memória: cria os nós; quem recebe a lista libera com rankingLiberar.
 * Quem usa: C, em jogoFinalizar. */
Registro *rankingCarregar(const char *arquivo);

/* Cria um nó e encaixa na posição certa (ordem de pontos).
 * Se o malloc falhar, não insere.
 * Quem usa: C, em jogoFinalizar. */
void rankingInserir(Registro **lista, const char *nome, int pontos);

/* Grava no arquivo só os 10 melhores.
 * Quem usa: C, em jogoFinalizar. */
void rankingSalvar(const Registro *lista, const char *arquivo);

/* Desenha na janela os 10 melhores ("nome - pontos"), a partir do pixel (x, y).
 * Quem usa: C, na tela de fim. */
void rankingDesenhar(const Registro *lista, int x, int y);

/* Libera todos os nós e deixa *lista = NULL.
 * Quem usa: C, em jogoLiberar. */
void rankingLiberar(Registro **lista);

#endif
