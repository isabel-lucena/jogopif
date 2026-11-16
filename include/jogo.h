#ifndef JOGO_H
#define JOGO_H

#include "tipos.h"

void jogoInicializar(Jogo *jogo);

void jogoNovaPartida(Jogo *jogo);

void jogoAtualizar(Jogo *jogo);

void jogoDesenhar(const Jogo *jogo);

void jogoFinalizar(Jogo *jogo);

#endif
