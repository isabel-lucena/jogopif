#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char mensagemHud[128] = "";
static float tempoMensagemHud = 0.0f;

static void jogoAvisar(const char *texto, float duracao) {
    strncpy(mensagemHud, texto, sizeof(mensagemHud) - 1);
    mensagemHud[sizeof(mensagemHud) - 1] = '\0';
    tempoMensagemHud = duracao;
}

static int jogoContarEstrelas(const Jogador *j) {
    int total = j->estrelasExtras;
    for (const Estrela *p = j->coletadas; p != NULL; p = p->prox) {
        total++;
    }
    return total;
}

static int jogoCalcularPontos(const Jogo *jogo, int segundosGastos) {
    int estrelas = jogoContarEstrelas(&jogo->jogador);
    int bonusTempo = (segundosGastos < TEMPO_LIMITE)
                         ? (TEMPO_LIMITE - segundosGastos) * XP_SEGUNDO
                         : 0;

    return (estrelas * XP_ESTRELA) +
           (jogo->jogador.vidas * XP_VIDA) +
           bonusTempo;
}

static void jogoLimparListasSala(Sala *s) {
    while (s->estrelas != NULL) {
        Estrela *aux = s->estrelas;
        s->estrelas = aux->prox;
        free(aux);
    }
    while (s->distracoes != NULL) {
        Distracao *aux = s->distracoes;
        s->distracoes = aux->prox;
        free(aux);
    }
    while (s->aliados != NULL) {
        Aliado *aux = s->aliados;
        s->aliados = aux->prox;
        free(aux);
    }
    while (s->itensVida != NULL) {
        ItemVida *aux = s->itensVida;
        s->itensVida = aux->prox;
        free(aux);
    }
}

static void jogoLimparColetadas(Jogador *j) {
    while (j->coletadas != NULL) {
        Estrela *aux = j->coletadas;
        j->coletadas = aux->prox;
        free(aux);
    }
}

static void jogoPrepararSala(Sala *s) {
    s->inicio.x = 1;
    s->inicio.y = 2;

    for (int y = 0; y < MAPA_ALT; y++) {
        for (int x = 0; x < MAPA_LARG; x++) {
            char c = s->mapa[y][x];

            if (c == 'X' || c == 'x') {
                s->mapa[y][x] = CH_PAREDE;
            } else if (c == '7') {

                s->mapa[y][x] = CH_SAIDA;
            } else if (c == CH_JOGADOR) {
                s->inicio.x = x;
                s->inicio.y = y;
                s->mapa[y][x] = CH_CHAO;
            } else if (c == CH_ESTRELA || c == CH_FAKE || c == CH_DISTRACAO ||
                       c == CH_PROFESSOR || c == CH_VIDA) {
                s->mapa[y][x] = CH_CHAO;
            }
        }
    }
}

static Posicao jogoAcharPorta(const Sala *s, char porta) {
    for (int y = 0; y < MAPA_ALT; y++) {
        for (int x = 0; x < MAPA_LARG; x++) {
            if (s->mapa[y][x] == porta) {
                Posicao p = { x, y };
                return p;
            }
        }
    }
    Posicao naoAchou = { -1, -1 };
    return naoAchou;
}

void jogoInicializar(Jogo *jogo) {
    memset(jogo, 0, sizeof(Jogo));
    strcpy(jogo->nome, "Aluno");
    jogo->tela = TELA_NOME;
    jogo->ranking = rankingCarregar(ARQ_RANKING);
}

void jogoNovaPartida(Jogo *jogo) {
    const char *arquivos[NUM_SALAS] = {
        "mapas/sala1.txt",
        "mapas/sala2.txt",
        "mapas/sala3.txt"
    };

    jogoLimparColetadas(&jogo->jogador);

    for (int i = 0; i < NUM_SALAS; i++) {
        jogoLimparListasSala(&jogo->salas[i]);
        if (!mapaCarregar(&jogo->salas[i], arquivos[i])) {
            TraceLog(LOG_ERROR, "Nao foi possivel carregar %s", arquivos[i]);
        }
        jogoPrepararSala(&jogo->salas[i]);
    }

    jogo->jogador.salaAtual = 0;
    jogo->jogador.pos = jogo->salas[0].inicio;
    jogo->jogador.entrada = jogo->salas[0].inicio;
    jogo->jogador.vidas = VIDAS_INICIAIS;
    jogo->jogador.estrelasExtras = 0;
    jogo->jogador.quebrasRestantes = 0;
    jogo->jogador.invencivel = 0.0f;

    jogo->inicio = GetTime();
    jogo->descontoTempo = 0;
    jogo->segundosFinais = 0;
    jogo->pontos = 0;
    jogo->venceu = 0;
    jogo->tela = TELA_JOGO;

    jogoAvisar("Use WASD ou Setas para explorar. Reuna 7 estrelas e ache a saida (S)!", 4.5f);
}

static void jogoTrocarSala(Jogo *jogo, int destinoSala, char porta) {
    jogo->jogador.salaAtual = destinoSala;
    Sala *s = &jogo->salas[destinoSala];

    Posicao p = jogoAcharPorta(s, porta);
    if (p.x == -1 || p.y == -1) {
        p = s->inicio;
    } else {
        if (p.x == MAPA_LARG - 1 && !mapaEhParede(s, p.x - 1, p.y)) {
            p.x -= 1;
        } else if (p.x == 0 && !mapaEhParede(s, p.x + 1, p.y)) {
            p.x += 1;
        }
    }

    jogo->jogador.pos = p;
    jogo->jogador.entrada = p;
}

static void jogoEncerrarPartida(Jogo *jogo, int venceu) {
    int tempoDecorrido = (int)(GetTime() - jogo->inicio) - jogo->descontoTempo;
    if (tempoDecorrido < 0) tempoDecorrido = 0;

    jogo->segundosFinais = tempoDecorrido;
    jogo->venceu = venceu;

    if (venceu) {
        jogo->pontos = jogoCalcularPontos(jogo, tempoDecorrido);
        const char *nomeFinal = (strlen(jogo->nome) > 0) ? jogo->nome : "Aluno";
        rankingInserir(&jogo->ranking, nomeFinal, jogo->pontos);
        rankingSalvar(jogo->ranking, ARQ_RANKING);
        jogo->tela = TELA_FIM;
    } else {
        jogo->pontos = 0;
        jogo->tela = TELA_GAMEOVER;
    }
}

void jogoAtualizar(Jogo *jogo) {
    float dt = GetFrameTime();

    if (tempoMensagemHud > 0.0f) {
        tempoMensagemHud -= dt;
        if (tempoMensagemHud <= 0.0f) {
            mensagemHud[0] = '\0';
        }
    }

    if (jogo->tela == TELA_NOME) {
        int len = (int)strlen(jogo->nome);
        int tecla = GetCharPressed();

        while (tecla > 0) {
            if (tecla >= 33 && tecla <= 125 && len < NOME_MAX - 1) {
                jogo->nome[len++] = (char)tecla;
                jogo->nome[len] = '\0';
            }
            tecla = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && len > 0) {
            jogo->nome[--len] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (strlen(jogo->nome) == 0) {
                strcpy(jogo->nome, "Aluno");
            }
            jogoNovaPartida(jogo);
        }
        return;
    }

    if (jogo->tela == TELA_FIM || jogo->tela == TELA_GAMEOVER) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            jogoNovaPartida(jogo);
        }
        return;
    }

    if (jogo->jogador.invencivel > 0.0f) {
        jogo->jogador.invencivel -= dt;
        if (jogo->jogador.invencivel < 0.0f) {
            jogo->jogador.invencivel = 0.0f;
        }
    }

    int tempoAtual = (int)(GetTime() - jogo->inicio) - jogo->descontoTempo;
    if (tempoAtual >= TEMPO_LIMITE) {
        jogoEncerrarPartida(jogo, 0);
        return;
    }

    Sala *sala = &jogo->salas[jogo->jogador.salaAtual];

    int dx = 0, dy = 0;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) dy = -1;
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) dy = 1;
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) dx = -1;
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) dx = 1;

    if (dx != 0 || dy != 0) {
        int nx = jogo->jogador.pos.x + dx;
        int ny = jogo->jogador.pos.y + dy;

        if (mapaEhParede(sala, nx, ny)) {
            if (jogo->jogador.quebrasRestantes > 0 && mapaQuebrarParede(sala, nx, ny)) {
                jogo->jogador.quebrasRestantes--;
                jogo->jogador.pos.x = nx;
                jogo->jogador.pos.y = ny;

                char msg[96];
                snprintf(msg, sizeof(msg), "Parede quebrada! Restam %d quebras.", jogo->jogador.quebrasRestantes);
                jogoAvisar(msg, 3.0f);
            }
        } else {
            jogo->jogador.pos.x = nx;
            jogo->jogador.pos.y = ny;

            char celula = mapaCelula(sala, nx, ny);

            if (celula == '2') {
                if (jogo->jogador.salaAtual == 0) {
                    jogoTrocarSala(jogo, 1, '2');
                    jogoAvisar("Voce entrou na Sala 2!", 2.5f);
                } else if (jogo->jogador.salaAtual == 1) {
                    jogoTrocarSala(jogo, 0, '2');
                    jogoAvisar("Voce voltou para a Sala 1!", 2.5f);
                }
            } else if (celula == '3') {
                if (jogo->jogador.salaAtual == 0) {
                    jogoTrocarSala(jogo, 2, '3');
                    jogoAvisar("Voce entrou na Sala 3!", 2.5f);
                } else if (jogo->jogador.salaAtual == 2) {
                    jogoTrocarSala(jogo, 0, '3');
                    jogoAvisar("Voce voltou para a Sala 1!", 2.5f);
                }
            } else if (celula == '1') {
                jogoTrocarSala(jogo, 0, '1');
                jogoAvisar("Voce voltou para a Sala 1!", 2.5f);
            } else if (celula == CH_SAIDA) {
                int estrelas = jogoContarEstrelas(&jogo->jogador);
                if (estrelas >= META_ESTRELAS) {
                    jogoEncerrarPartida(jogo, 1);
                    return;
                } else {
                    char msg[96];
                    snprintf(msg, sizeof(msg), "Saida trancada! Precisa de %d estrelas (atual: %d).",
                             META_ESTRELAS, estrelas);
                    jogoAvisar(msg, 3.5f);
                }
            }
        }
    }
}

void jogoDesenhar(const Jogo *jogo) {
    BeginDrawing();
    ClearBackground(COR_FUNDO);

    if (jogo->tela == TELA_NOME) {
        DrawText("escaPIF - Fuga do Brum", LARGURA_JANELA / 2 - 210, 50, 36, COR_ESTRELA);
        DrawText("Reuna pelo menos 7 estrelas do conhecimento e escape pela saida (S)!",
                 LARGURA_JANELA / 2 - 330, 100, 19, COR_SUAVE);

        DrawText("Digite seu nome (sem espacos) e pressione ENTER:",
                 LARGURA_JANELA / 2 - 255, 155, 20, COR_TEXTO);
        DrawRectangleLines(LARGURA_JANELA / 2 - 170, 185, 340, 38, COR_DESTAQUE);
        DrawText(jogo->nome, LARGURA_JANELA / 2 - 155, 193, 22, COR_JOGADOR);

        DrawText("RANKING - TOP 10:", LARGURA_JANELA / 2 - 105, 245, 20, COR_ESTRELA);
        rankingDesenhar(jogo->ranking, LARGURA_JANELA / 2 - 120, 275);

        EndDrawing();
        return;
    }

    int tempoGasto = (int)(GetTime() - jogo->inicio) - jogo->descontoTempo;
    if (tempoGasto < 0) tempoGasto = 0;
    int tempoRestante = TEMPO_LIMITE - tempoGasto;
    if (tempoRestante < 0) tempoRestante = 0;

    int estrelas = jogoContarEstrelas(&jogo->jogador);

    DrawRectangle(0, 0, LARGURA_JANELA, HUD_ALT, COR_HUD_FUNDO);
    DrawLine(0, HUD_ALT, LARGURA_JANELA, HUD_ALT, COR_HUD_LINHA);

    DrawText(TextFormat("VIDAS: %d", jogo->jogador.vidas), 15, 10, 19, COR_VIDA);
    DrawText(TextFormat("ESTRELAS: %d/%d", estrelas, META_ESTRELAS), 140, 10, 19, COR_ESTRELA);
    DrawText(TextFormat("SALA: %d/%d", jogo->jogador.salaAtual + 1, NUM_SALAS), 320, 10, 19, COR_DESTAQUE);
    DrawText(TextFormat("TEMPO: %ds", tempoRestante), 450, 10, 19,
             (tempoRestante <= 30) ? COR_PERIGO : COR_TEXTO);
    DrawText(TextFormat("QUEBRAS: %d", jogo->jogador.quebrasRestantes), 590, 10, 19, COR_SUAVE);

    if (tempoMensagemHud > 0.0f && mensagemHud[0] != '\0') {
        DrawText(mensagemHud, 740, 11, 16, COR_VITORIA);
    }

    const Sala *sala = &jogo->salas[jogo->jogador.salaAtual];
    mapaDesenhar(sala);

    int desenharJogador = 1;
    if (jogo->jogador.invencivel > 0.0f && ((int)(jogo->jogador.invencivel * 10) % 2 == 0)) {
        desenharJogador = 0;
    }

    if (desenharJogador) {
        DrawText("@", PIXEL_X(jogo->jogador.pos.x) + 2, PIXEL_Y(jogo->jogador.pos.y),
                 TAM_CELULA, COR_JOGADOR);
    }

    if (jogo->tela == TELA_FIM) {
        DrawRectangle(0, 0, LARGURA_JANELA, ALTURA_JANELA, Fade(COR_FUNDO, 0.88f));
        DrawText("VOCE PASSOU EM PIF E ESCAPOU DO BRUM!",
                 LARGURA_JANELA / 2 - 280, 35, 26, COR_VITORIA);

        DrawText(TextFormat("Jogador: %s | Estrelas: %d | Vidas: %d | Tempo: %ds",
                            jogo->nome, estrelas, jogo->jogador.vidas, jogo->segundosFinais),
                 LARGURA_JANELA / 2 - 290, 75, 19, COR_TEXTO);

        DrawText(TextFormat("PONTUACAO FINAL: %d XP", jogo->pontos),
                 LARGURA_JANELA / 2 - 150, 105, 24, COR_ESTRELA);

        DrawText("TOP 10 RANKING:", LARGURA_JANELA / 2 - 95, 145, 20, COR_DESTAQUE);
        rankingDesenhar(jogo->ranking, LARGURA_JANELA / 2 - 110, 175);

        DrawText("Pressione ENTER para jogar novamente ou ESC para sair",
                 LARGURA_JANELA / 2 - 250, ALTURA_JANELA - 35, 18, COR_SUAVE);
    }

    if (jogo->tela == TELA_GAMEOVER) {
        DrawRectangle(0, 0, LARGURA_JANELA, ALTURA_JANELA, Fade(COR_FUNDO, 0.88f));
        DrawText("FIM DE JOGO! VOCE REPROVOU EM PIF!",
                 LARGURA_JANELA / 2 - 250, ALTURA_JANELA / 2 - 50, 26, COR_PERIGO);
        DrawText("O tempo acabou ou voce perdeu o foco no Brum.",
                 LARGURA_JANELA / 2 - 220, ALTURA_JANELA / 2 - 10, 20, COR_TEXTO);
        DrawText("Pressione ENTER para tentar novamente ou ESC para sair",
                 LARGURA_JANELA / 2 - 250, ALTURA_JANELA / 2 + 40, 18, COR_SUAVE);
    }

    EndDrawing();
}

void jogoFinalizar(Jogo *jogo) {
    jogoLimparColetadas(&jogo->jogador);
    for (int i = 0; i < NUM_SALAS; i++) {
        jogoLimparListasSala(&jogo->salas[i]);
    }
    rankingLiberar(&jogo->ranking);
}
