/* =====================================================================
 * tipos.h  -  arquivo do TRIO (só muda com combinado dos três)
 *
 * Aqui ficam todas as constantes e todas as structs do jogo.
 * Os outros .h incluem este arquivo.
 *
 * (sugestão) = não estava nos acordos; o trio decide se mantém.
 * ===================================================================== */
#ifndef TIPOS_H
#define TIPOS_H

#include "raylib.h"


/* ---------------------------------------------------------------------
 * 1. Tamanho do mapa e da janela
 * --------------------------------------------------------------------- */
#define MAPA_ALT        18      /* linhas do mapa */
#define MAPA_LARG       60      /* colunas do mapa */
#define NUM_SALAS        3
#define TAM_CELULA      20      /* (sugestão) cada célula vira um quadrado de 20 px */
#define HUD_ALT         40      /* (sugestão) faixa de cima da janela para o HUD */
#define LARGURA_JANELA  (MAPA_LARG * TAM_CELULA)            /* 1200 px */
#define ALTURA_JANELA   (MAPA_ALT * TAM_CELULA + HUD_ALT)   /*  400 px */
#define FPS             60

/* Converte célula do mapa em pixel da janela. Usem sempre estas duas,
 * assim mapa (A), entidades (B) e jogador (C) ficam alinhados. */
#define PIXEL_X(coluna) ((coluna) * TAM_CELULA)
#define PIXEL_Y(linha)  (HUD_ALT + (linha) * TAM_CELULA)


/* ---------------------------------------------------------------------
 * 2. Regras do jogo (acordos do trio)
 * --------------------------------------------------------------------- */
#define VIDAS_INICIAIS   3
#define META_ESTRELAS    7      /* estrelas para abrir a saída */
#define TEMPO_LIMITE   180      /* segundos; depois disso o tempo não dá xp */
#define XP_ESTRELA     120
#define XP_VIDA        300
#define XP_SEGUNDO      15
#define DESCONTO_TEMPO  20      /* presente "menos 20 segundos" */
#define QUEBRAS_PODER    3      /* presente "quebrar 3 paredes" */
#define TEMPO_INVENCIVEL 1.0f   /* (sugestão) segundos sem perder vida depois de um dano */
#define NOME_MAX        20
#define RANKING_TOP     10
#define ARQ_RANKING     "ranking.txt"


/* ---------------------------------------------------------------------
 * 3. Símbolos dos arquivos de mapa (mapas/salaN.txt)
 * --------------------------------------------------------------------- */
#define CH_PAREDE     'x'
#define CH_CHAO       ' '
#define CH_JOGADOR    '@'       /* onde o jogador começa (só na sala 1) */
#define CH_ESTRELA    '*'
#define CH_FAKE       'F'       /* (sugestão) estrela fake; na tela parece '*' */
#define CH_DISTRACAO  'D'
#define CH_PROFESSOR  'P'
#define CH_VIDA       '+'
#define CH_SAIDA      'S'       /* (sugestão) saída do prédio */
/* Portas: '1', '2', '3' = número da sala para onde a porta leva. */


/* ---------------------------------------------------------------------
 * 4. Cores (raylib usa o tipo Color)
 * --------------------------------------------------------------------- */
#define COR_FUNDO      BLACK
#define COR_PAREDE     DARKBLUE                         /* azul escuro */
#define COR_DISTRACAO  (Color){ 255,  40,  60, 255 }    /* vermelho neon */
#define COR_JOGADOR    (Color){   0, 255, 255, 255 }    /* ciano neon */
#define COR_PORTA      WHITE
#define COR_PROFESSOR  DARKBLUE                         /* azul escuro */
#define COR_VIDA       MAGENTA
#define COR_ESTRELA    YELLOW                           /* a fake também */
#define COR_TEXTO      RAYWHITE


/* ---------------------------------------------------------------------
 * 5. Tipos (enum)
 * --------------------------------------------------------------------- */

/* Os 5 tipos de distração. Todas ficam paradas. */
typedef enum {
    CELULAR,
    REDES_SOCIAIS,
    SONO,
    CONVERSA,
    VIRUS
} TipoDistracao;

/* Os 4 presentes que um professor pode dar. */
typedef enum {
    DA_ESTRELA,     /* +1 estrela extra */
    DA_VIDA,        /* +1 vida */
    DA_TEMPO,       /* -20 segundos no cronômetro */
    DA_QUEBRA       /* pode quebrar 3 paredes */
} TipoAliado;

/* Em que tela o jogo está (com raylib, até digitar o nome é na janela). */
typedef enum {
    TELA_NOME,      /* "Adicione seu nome" */
    TELA_JOGO,
    TELA_FIM        /* vitória, pontos e ranking */
} Tela;


/* ---------------------------------------------------------------------
 * 6. Structs
 *    [lista] = é nó de lista encadeada, criado com malloc.
 * --------------------------------------------------------------------- */

typedef struct {
    int x, y;                   /* x = coluna, y = linha. Acesso: mapa[y][x] */
} Posicao;

typedef struct Estrela {        /* [lista] criada pela Pessoa B */
    Posicao pos;
    int fake;                   /* 0 = verdadeira, 1 = fake */
    struct Estrela *prox;
} Estrela;

typedef struct Distracao {      /* [lista] criada pela Pessoa B */
    Posicao pos;
    TipoDistracao tipo;
    struct Distracao *prox;
} Distracao;

typedef struct Aliado {         /* [lista] professor, criado pela Pessoa B */
    Posicao pos;
    TipoAliado tipo;
    struct Aliado *prox;
} Aliado;

typedef struct ItemVida {       /* [lista] o '+' do mapa, criado pela Pessoa B */
    Posicao pos;
    struct ItemVida *prox;
} ItemVida;

typedef struct Registro {       /* [lista] uma linha do ranking, criada pela Pessoa A */
    char nome[NOME_MAX];
    int pontos;
    struct Registro *prox;
} Registro;

typedef struct {                /* uma sala. Fica dentro de Jogo (sem malloc) */
    char       mapa[MAPA_ALT][MAPA_LARG + 1];   /* +1 para o '\0' */
    Estrela   *estrelas;        /* estrelas (verdadeiras e fake) no chão */
    Distracao *distracoes;
    Aliado    *aliados;         /* professores ainda não encontrados */
    ItemVida  *itensVida;       /* '+' ainda no chão */
    Posicao    inicio;          /* onde estava o '@'; {-1,-1} se não tem */
} Sala;

typedef struct {
    Posicao  pos;
    Posicao  entrada;           /* onde entrou na sala atual (a fake manda para cá) */
    int      vidas;
    int      salaAtual;         /* 0, 1 ou 2 (sala 1 = 0) */
    Estrela *coletadas;         /* lista das estrelas verdadeiras pegas */
    int      estrelasExtras;    /* estrelas ganhas de professor */
    int      quebrasRestantes;  /* paredes que ainda pode quebrar */
    float    invencivel;        /* segundos de invencibilidade que faltam */
} Jogador;

typedef struct {                /* o jogo todo. Fica na pilha do main (sem malloc) */
    Tela      tela;
    Sala      salas[NUM_SALAS];
    Jogador   jogador;
    double    inicio;           /* GetTime() quando a partida começou */
    int       descontoTempo;    /* soma dos presentes "-20 s" */
    int       segundosFinais;   /* tempo congelado na vitória */
    int       pontos;           /* pontos da vitória */
    int       venceu;
    char      nome[NOME_MAX];
    Registro *ranking;          /* carregado no fim, para mostrar na tela */
} Jogo;

#endif
