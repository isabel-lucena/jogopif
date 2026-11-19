#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"

#define MAPA_ALT        18
#define MAPA_LARG       60
#define NUM_SALAS        3
#define TAM_CELULA      20
#define HUD_ALT         40
#define LARGURA_JANELA  (MAPA_LARG * TAM_CELULA)
#define ALTURA_JANELA   (MAPA_ALT * TAM_CELULA + HUD_ALT)
#define FPS             60

#define PIXEL_X(coluna) ((coluna) * TAM_CELULA)
#define PIXEL_Y(linha)  (HUD_ALT + (linha) * TAM_CELULA)

#define VIDAS_INICIAIS   3
#define META_ESTRELAS    7
#define TEMPO_LIMITE   180
#define XP_ESTRELA     120
#define XP_VIDA        300
#define XP_SEGUNDO      15
#define DESCONTO_TEMPO  20
#define QUEBRAS_PODER    3
#define TEMPO_INVENCIVEL 1.0f
#define NOME_MAX        20
#define RANKING_TOP     10
#define ARQ_RANKING     "ranking.txt"

#define CH_PAREDE     'x'
#define CH_CHAO       ' '
#define CH_JOGADOR    '@'
#define CH_ESTRELA    '*'
#define CH_FAKE       'F'
#define CH_DISTRACAO  'D'
#define CH_PROFESSOR  'P'
#define CH_VIDA       '+'
#define CH_SAIDA      '>'

#define COR_FUNDO      BLACK
#define COR_PAREDE     DARKBLUE
#define COR_DISTRACAO  (Color){ 255,  40,  60, 255 }
#define COR_JOGADOR    (Color){   0, 255, 255, 255 }
#define COR_PORTA      WHITE
#define COR_PROFESSOR  DARKBLUE
#define COR_VIDA       MAGENTA
#define COR_ESTRELA    YELLOW
#define COR_TEXTO      RAYWHITE

#define COR_HUD_FUNDO  (Color){  20,  18,  40, 255 }
#define COR_HUD_LINHA  (Color){  90,  83, 120, 255 }
#define COR_DESTAQUE   (Color){   0, 255, 255, 255 }
#define COR_SUAVE      (Color){ 150, 150, 170, 255 }
#define COR_PERIGO     (Color){ 255,  40,  60, 255 }
#define COR_VITORIA    (Color){  80, 255, 120, 255 }

#define DIST_CELULAR       0
#define DIST_REDES_SOCIAIS 1
#define DIST_SONO          2
#define DIST_CONVERSA      3
#define DIST_VIRUS         4

#define ALIADO_DA_ESTRELA  0
#define ALIADO_DA_VIDA     1
#define ALIADO_DA_TEMPO    2
#define ALIADO_DA_QUEBRA   3

#define TELA_NOME          0
#define TELA_JOGO          1
#define TELA_GAMEOVER      2
#define TELA_FIM           3

typedef struct {
    int x, y;
} Posicao;

typedef struct Estrela {
    Posicao pos;
    int fake;
    struct Estrela *prox;
} Estrela;

typedef struct Distracao {
    Posicao pos;
    int dx, dy;
    int tipo;
    struct Distracao *prox;
} Distracao;

typedef struct Aliado {
    Posicao pos;
    int tipo;
    struct Aliado *prox;
} Aliado;

typedef struct ItemVida {
    Posicao pos;
    struct ItemVida *prox;
} ItemVida;

typedef struct Registro {
    char nome[NOME_MAX];
    int pontos;
    struct Registro *prox;
} Registro;

typedef struct {
    char       mapa[MAPA_ALT][MAPA_LARG + 1];
    Estrela   *estrelas;
    Distracao *distracoes;
    Aliado    *aliados;
    ItemVida  *itensVida;
    Posicao    inicio;
} Sala;

typedef struct {
    Posicao  pos;
    Posicao  entrada;
    int      vidas;
    int      salaAtual;
    Estrela *coletadas;
    int      estrelasExtras;
    int      quebrasRestantes;
    float    invencivel;
} Jogador;

typedef struct {
    int       tela;
    Sala      salas[NUM_SALAS];
    Jogador   jogador;
    double    inicio;
    int       descontoTempo;
    int       segundosFinais;
    int       pontos;
    int       venceu;
    char      nome[NOME_MAX];
    Registro *ranking;
} Jogo;

#endif
