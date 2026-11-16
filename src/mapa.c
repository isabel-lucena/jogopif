
#include <stdio.h>
#include <string.h>
#include "mapa.h"

int mapaCarregar(Sala *sala, const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        return 0;
    }

    char linha[MAPA_LARG + 3];               
    int acabou = 0;

    for (int y = 0; y < MAPA_ALT; y++) {
        if (!acabou && fgets(linha, sizeof linha, f) == NULL) {
            acabou = 1;                     
        }

        if (acabou) {
            linha[0] = '\0';
        } else {
            linha[strcspn(linha, "\r\n")] = '\0';
        }

        int tam = (int)strlen(linha);
        for (int x = 0; x < MAPA_LARG; x++) {
            if (x < tam) {
                sala->mapa[y][x] = linha[x];
            } else {
                sala->mapa[y][x] = CH_CHAO;
            }
        }

        sala->mapa[y][MAPA_LARG] = '\0';
    }

    fclose(f);
    return 1;
}

void mapaDesenhar(const Sala *sala) {
    for (int y = 0; y < MAPA_ALT; y++) {
        for (int x = 0; x < MAPA_LARG; x++) {
            char c  = sala->mapa[y][x];
            int  px = PIXEL_X(x);             
            int  py = PIXEL_Y(y);

            if (c == CH_PAREDE) {
                DrawRectangle(px, py, TAM_CELULA, TAM_CELULA, COR_PAREDE);
            } else if (c >= '1' && c <= '3') {
                char texto[2] = { c, '\0' };
                DrawText(texto, px + 5, py, TAM_CELULA, COR_PORTA);
            } else if (c == CH_SAIDA) {
                DrawRectangleLines(px, py, TAM_CELULA, TAM_CELULA, COR_PORTA);
                DrawText("S", px + 5, py, TAM_CELULA, COR_PORTA);
            }
        }
    }
}


char mapaCelula(const Sala *sala, int x, int y) {
    if (x < 0 || x >= MAPA_LARG || y < 0 || y >= MAPA_ALT) {
        return CH_PAREDE;
    }
    return sala->mapa[y][x];                   
}

int mapaEhParede(const Sala *sala, int x, int y) {
    return mapaCelula(sala, x, y) == CH_PAREDE;
}


int mapaQuebrarParede(Sala *sala, int x, int y) {
    if (x <= 0 || x >= MAPA_LARG - 1 || y <= 0 || y >= MAPA_ALT - 1) {
        return 0;                             
    }
    if (sala->mapa[y][x] != CH_PAREDE) {
        return 0;                              
    }
    sala->mapa[y][x] = CH_CHAO;
    return 1;
}


Posicao mapaAcharPorta(const Sala *sala, char destino) {
    for (int y = 0; y < MAPA_ALT; y++) {
        for (int x = 0; x < MAPA_LARG; x++) {
            if (sala->mapa[y][x] == destino) {
                Posicao p = { x, y };
                return p;
            }
        }
    }
    Posicao nada = { -1, -1 };
    return nada;
}
