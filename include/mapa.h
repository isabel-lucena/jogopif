/* =====================================================================
 * mapa.h  -  PESSOA A
 *
 * Lê o arquivo do mapa para a matriz, responde perguntas sobre as
 * células e desenha paredes e portas.
 * Nenhuma função daqui usa malloc.
 * ===================================================================== */
#ifndef MAPA_H
#define MAPA_H

#include "tipos.h"

/* Copia o arquivo de texto para sala->mapa, do jeito que está.
 * Devolve 1 se deu certo, 0 se o arquivo não abriu.
 * Quem usa: C, em jogoIniciar. */
int mapaCarregar(Sala *sala, const char *arquivo);

/* Desenha paredes (azul escuro), portas (branco) e a saída.
 * Quem usa: C, em jogoDesenhar. */
void mapaDesenhar(const Sala *sala);

/* Devolve o caractere da célula (x, y).
 * Fora do mapa devolve 'x' (parede), para ninguém sair da matriz.
 * Quem usa: C. */
char mapaCelula(const Sala *sala, int x, int y);

/* Devolve 1 se (x, y) é parede ou está fora do mapa, 0 se não.
 * Quem usa: C. */
int mapaEhParede(const Sala *sala, int x, int y);

/* (sugestão) Troca a parede (x, y) por chão.
 * Devolve 1 se quebrou, 0 se não é parede ou se é a borda (a borda nunca quebra).
 * Quem usa: C, quando o jogador tem o poder de quebrar paredes. */
int mapaQuebrarParede(Sala *sala, int x, int y);

/* Procura a porta com o caractere destino ('1', '2' ou '3').
 * Devolve a posição dela, ou {-1, -1} se não achar.
 * Quem usa: C, em salaTrocar. */
Posicao mapaAcharPorta(const Sala *sala, char destino);

#endif
