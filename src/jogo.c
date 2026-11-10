/* jogo.c  -  PESSOA C  (versão stub: troquem cada função pelo código real)
 * O stub já abre na tela do nome; ENTER vai para o jogo; ESC fecha. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "mapa.h"
#include "entidades.h"
#include "ranking.h"

int jogoIniciar(Jogo *jogo) { memset(jogo, 0, sizeof *jogo); jogo->tela = TELA_NOME; return 1; }
void jogoAtualizar(Jogo *jogo) { if (jogo->tela == TELA_NOME && IsKeyPressed(KEY_ENTER)) jogo->tela = TELA_JOGO; }
void jogoDesenhar(const Jogo *jogo) {
    if (jogo->tela == TELA_NOME) telaNomeDesenhar(jogo);
    else DrawText("escaPIF - esqueleto (ESC sai)", 20, 20, 20, COR_TEXTO);
}
void jogoLiberar(Jogo *jogo) { (void)jogo; }
void jogadorMover(Jogo *jogo, int dx, int dy) { (void)jogo; (void)dx; (void)dy; }
void jogadorVoltarInicio(Jogo *jogo) { (void)jogo; }
void aliadoAplicar(Jogo *jogo, const Aliado *aliado) { (void)jogo; (void)aliado; }
void salaTrocar(Jogo *jogo, int destino) { (void)jogo; (void)destino; }
int jogoRecomecar(Jogo *jogo) { (void)jogo; return 1; }
int jogoSegundos(const Jogo *jogo) { (void)jogo; return 0; }
int pontuacaoCalcular(int estrelas, int vidas, int segundos) { (void)estrelas; (void)vidas; (void)segundos; return 0; }
void jogoFinalizar(Jogo *jogo) { (void)jogo; }
void hudDesenhar(const Jogo *jogo) { (void)jogo; }
void telaNomeDesenhar(const Jogo *jogo) { (void)jogo; DrawText("Adicione seu nome e aperte ENTER", 20, 20, 20, COR_TEXTO); }
void telaFimDesenhar(const Jogo *jogo) { (void)jogo; }
