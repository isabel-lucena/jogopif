#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"

#define MAPA_LARG 60
#define MAPA_ALT 18
#define TAM_CELULA 20
#define HUD_ALTURA 70

//conversão de coordenadas da matriz para pixels na janela
#define PIXEL_X(x) ((x) * TAM_CELULA)
#define PIXEL_Y(y) ((y) * TAM_CELULA + HUD_ALTURA)

//caracteres de cd sala
#define CH_PAREDE 'X'
#define CH_CHAO   ' '
#define CH_SAIDA  'S'

//sobre ranking
#define NOME_MAX 20
#define RANKING_TOP 10

//cores
#define COR_PAREDE (Color){ 70, 75, 90, 255 }
#define COR_PORTA  GREEN
#define COR_TEXTO  RAYWHITE
