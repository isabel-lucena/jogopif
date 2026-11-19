#include <stdlib.h>

#include "entidades.h"

static Estrela *novaEstrela(int x, int y, int fake) {
    Estrela *e = malloc(sizeof(*e));
    if (e == NULL) return NULL;

    e->pos = (Posicao){ x, y };
    e->fake = fake;
    e->prox = NULL;
    return e;
}

static Distracao *novaDistracao(int x, int y) {
    Distracao *d = malloc(sizeof(*d));
    if (d == NULL) return NULL;

    d->pos = (Posicao){ x, y };
    d->tipo = rand() % 5;
    d->prox = NULL;
    return d;
}

static Aliado *novoAliado(int x, int y) {
    Aliado *a = malloc(sizeof(*a));
    if (a == NULL) return NULL;

    a->pos = (Posicao){ x, y };
    a->tipo = rand() % 4;
    a->prox = NULL;
    return a;
}

static ItemVida *novoItemVida(int x, int y) {
    ItemVida *v = malloc(sizeof(*v));
    if (v == NULL) return NULL;

    v->pos = (Posicao){ x, y };
    v->prox = NULL;
    return v;
}

void entidadesExtrairDoMapa(Sala *sala) {
    sala->estrelas = NULL;
    sala->distracoes = NULL;
    sala->aliados = NULL;
    sala->itensVida = NULL;

    for (int y = 0; y < MAPA_ALT; y++) {
        for (int x = 0; x < MAPA_LARG; x++) {
            char c = sala->mapa[y][x];

            if (c == CH_ESTRELA || c == CH_FAKE) {
                Estrela *e = novaEstrela(x, y, c == CH_FAKE);
                if (e != NULL) {
                    e->prox = sala->estrelas;
                    sala->estrelas = e;
                }
            } else if (c == CH_DISTRACAO) {
                Distracao *d = novaDistracao(x, y);
                if (d != NULL) {
                    d->prox = sala->distracoes;
                    sala->distracoes = d;
                }
            } else if (c == CH_PROFESSOR) {
                Aliado *a = novoAliado(x, y);
                if (a != NULL) {
                    a->prox = sala->aliados;
                    sala->aliados = a;
                }
            } else if (c == CH_VIDA) {
                ItemVida *v = novoItemVida(x, y);
                if (v != NULL) {
                    v->prox = sala->itensVida;
                    sala->itensVida = v;
                }
            } else if (c == CH_JOGADOR) {
                sala->inicio = (Posicao){ x, y };
            } else {
                continue;
            }

            sala->mapa[y][x] = CH_CHAO;
        }
    }
}

Estrela *estrelaRemoverEm(Estrela **lista, int x, int y) {
    Estrela *ant = NULL;
    Estrela *p = *lista;

    while (p != NULL) {
        if (p->pos.x == x && p->pos.y == y) {
            if (ant == NULL) {
                *lista = p->prox;
            } else {
                ant->prox = p->prox;
            }
            p->prox = NULL;
            return p;
        }
        ant = p;
        p = p->prox;
    }

    return NULL;
}

void estrelaInserir(Estrela **lista, Estrela *e) {
    if (e == NULL) return;

    e->prox = *lista;
    *lista = e;
}

int estrelaContar(const Estrela *lista) {
    int n = 0;

    for (const Estrela *p = lista; p != NULL; p = p->prox) {
        if (!p->fake) n++;
    }

    return n;
}

Distracao *distracaoEm(Distracao *lista, int x, int y) {
    for (Distracao *p = lista; p != NULL; p = p->prox) {
        if (p->pos.x == x && p->pos.y == y) return p;
    }

    return NULL;
}

Aliado *aliadoRemoverEm(Aliado **lista, int x, int y) {
    Aliado *ant = NULL;
    Aliado *p = *lista;

    while (p != NULL) {
        if (p->pos.x == x && p->pos.y == y) {
            if (ant == NULL) {
                *lista = p->prox;
            } else {
                ant->prox = p->prox;
            }
            p->prox = NULL;
            return p;
        }
        ant = p;
        p = p->prox;
    }

    return NULL;
}

ItemVida *itemVidaRemoverEm(ItemVida **lista, int x, int y) {
    ItemVida *ant = NULL;
    ItemVida *p = *lista;

    while (p != NULL) {
        if (p->pos.x == x && p->pos.y == y) {
            if (ant == NULL) {
                *lista = p->prox;
            } else {
                ant->prox = p->prox;
            }
            p->prox = NULL;
            return p;
        }
        ant = p;
        p = p->prox;
    }

    return NULL;
}

static const char *LETRA_DISTRACAO[] = { "C", "R", "Z", "B", "V" };

void entidadesDesenhar(const Sala *sala) {
    int m = TAM_CELULA / 2;

    for (const Estrela *e = sala->estrelas; e != NULL; e = e->prox) {
        Vector2 centro = {
            PIXEL_X(e->pos.x) + m,
            PIXEL_Y(e->pos.y) + m
        };
        DrawPoly(centro, 4, m - 1, 0, COR_ESTRELA);
    }

    for (const Distracao *d = sala->distracoes; d != NULL; d = d->prox) {
        int px = PIXEL_X(d->pos.x);
        int py = PIXEL_Y(d->pos.y);
        DrawRectangle(px + 1, py + 1, TAM_CELULA - 2, TAM_CELULA - 2,
                      COR_DISTRACAO);
        const char *letra = LETRA_DISTRACAO[d->tipo];
        DrawText(letra, px + (TAM_CELULA - MeasureText(letra, 16)) / 2,
                 py + 2, 16, COR_FUNDO);
    }

    for (const Aliado *a = sala->aliados; a != NULL; a = a->prox) {
        int cx = PIXEL_X(a->pos.x) + m;
        int cy = PIXEL_Y(a->pos.y) + m;
        DrawCircle(cx, cy, m, COR_TEXTO);
        DrawCircle(cx, cy, m - 2, COR_PROFESSOR);
        DrawText("P", cx - MeasureText("P", 14) / 2, cy - 7, 14, COR_TEXTO);
    }

    for (const ItemVida *v = sala->itensVida; v != NULL; v = v->prox) {
        int px = PIXEL_X(v->pos.x);
        int py = PIXEL_Y(v->pos.y);
        DrawRectangle(px + 8, py + 3, 4, 14, COR_VIDA);
        DrawRectangle(px + 3, py + 8, 14, 4, COR_VIDA);
    }
}

void salaLiberar(Sala *sala) {
    estrelasLiberar(&sala->estrelas);
    distracoesLiberar(&sala->distracoes);
    aliadosLiberar(&sala->aliados);
    itensVidaLiberar(&sala->itensVida);
}

void estrelasLiberar(Estrela **lista) {
    while (*lista != NULL) {
        Estrela *aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}

void distracoesLiberar(Distracao **lista) {
    while (*lista != NULL) {
        Distracao *aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}

void aliadosLiberar(Aliado **lista) {
    while (*lista != NULL) {
        Aliado *aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}

void itensVidaLiberar(ItemVida **lista) {
    while (*lista != NULL) {
        ItemVida *aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}
