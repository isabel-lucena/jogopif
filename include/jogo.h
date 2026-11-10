/* =====================================================================
 * jogo.h  -  PESSOA C
 *
 * O jogo em si: telas, teclado, movimento do jogador, regras,
 * pontuação e ranking no fim. É quem chama as funções de A e de B.
 * ===================================================================== */
#ifndef JOGO_H
#define JOGO_H

#include "tipos.h"

/* ----- Chamadas pelo main ----- */

/* Zera tudo, carrega as 3 salas (mapaCarregar + entidadesExtrairDoMapa)
 * e coloca o jogador no '@' da sala 1. Começa na tela do nome.
 * Devolve 1 se deu certo, 0 se algum mapa não abriu. */
int jogoIniciar(Jogo *jogo);

/* Roda 1 vez por quadro (60 por segundo): lê o teclado e aplica as regras
 * da tela atual (nome, jogo ou fim). */
void jogoAtualizar(Jogo *jogo);

/* Roda 1 vez por quadro, entre BeginDrawing e EndDrawing: desenha a tela atual. */
void jogoDesenhar(const Jogo *jogo);

/* Libera tudo: as listas das 3 salas, jogador.coletadas e o ranking.
 * Pode ser chamada mais de uma vez sem problema. */
void jogoLiberar(Jogo *jogo);

/* ----- Uso interno da Pessoa C ----- */

/* Anda 1 casa e trata o que tiver lá: parede (quebra se tiver poder),
 * estrela, estrela fake, '+', professor, distração, porta e saída. */
void jogadorMover(Jogo *jogo, int dx, int dy);

/* Estrela fake: leva o jogador de volta para jogador.entrada. */
void jogadorVoltarInicio(Jogo *jogo);

/* Aplica o presente do professor: estrela extra, vida extra,
 * -20 segundos ou 3 paredes para quebrar. Não dá free (quem dá é jogadorMover). */
void aliadoAplicar(Jogo *jogo, const Aliado *aliado);

/* Leva o jogador para a sala destino (1, 2 ou 3), em cima da porta de volta.
 * Se não achar a porta, não troca. */
void salaTrocar(Jogo *jogo, int destino);

/* Perdeu as 3 vidas: libera tudo e começa de novo, mantendo o nome.
 * Devolve 1 se deu certo, 0 se algum mapa não abriu. */
int jogoRecomecar(Jogo *jogo);

/* Segundos de jogo: agora - inicio - descontoTempo (nunca menos que 0). */
int jogoSegundos(const Jogo *jogo);

/* pontos = 120 x estrelas + 300 x vidas + 15 x (180 - segundos).
 * Depois de 180 s a parte do tempo vale 0 (não fica negativa). */
int pontuacaoCalcular(int estrelas, int vidas, int segundos);

/* Vitória: calcula os pontos e atualiza o ranking
 * (rankingCarregar, rankingInserir, rankingSalvar). Vai para a tela de fim. */
void jogoFinalizar(Jogo *jogo);

/* Desenhos das partes da tela. */
void hudDesenhar(const Jogo *jogo);       /* sala, vidas, estrelas/7, quebras, tempo */
void telaNomeDesenhar(const Jogo *jogo);  /* "Adicione seu nome" + o que já foi digitado */
void telaFimDesenhar(const Jogo *jogo);   /* vitória, pontos e ranking */

#endif
