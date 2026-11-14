Registro *rankingCarregar(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        return NULL;
    }

    Registro *lista = NULL;
    char nome[NOME_MAX];
    int pontos;

    /* %19s lê no máximo 19 letras (NOME_MAX - 1) */
    while (fscanf(f, "%19s %d", nome, &pontos) == 2) {
        rankingInserir(&lista, nome, pontos);
    }

    fclose(f);
    return lista;
}

/* 8. Cria um nó e encaixa no lugar certo (maior primeiro). */
void rankingInserir(Registro **lista, const char *nome, int pontos) {
    Registro *novo = malloc(sizeof(Registro));
    if (novo == NULL) {
        return;
    }
    strncpy(novo->nome, nome, NOME_MAX - 1);
    novo->nome[NOME_MAX - 1] = '\0';
    novo->pontos = pontos;

    if (*lista == NULL || pontos > (*lista)->pontos) {
        novo->prox = *lista;
        *lista = novo;
        return;
    }

    /* empate: quem já estava fica na frente */
    Registro *p = *lista;
    while (p->prox != NULL && p->prox->pontos >= pontos) {
        p = p->prox;
    }
    novo->prox = p->prox;
    p->prox = novo;
}

/* 9. Grava só os 10 melhores, "nome pontos" por linha. */
void rankingSalvar(const Registro *lista, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (f == NULL) {
        return;
    }

    int i = 0;
    for (const Registro *p = lista; p != NULL && i < RANKING_TOP; p = p->prox, i++) {
        fprintf(f, "%s %d\n", p->nome, p->pontos);
    }

    fclose(f);
}

/* 10. Desenha os 10 melhores a partir do pixel (x, y). */
void rankingDesenhar(const Registro *lista, int x, int y) {
    if (lista == NULL) {
        DrawText("Ranking vazio", x, y, 20, COR_TEXTO);
        return;
    }

    char linha[64];
    int i = 0;
    for (const Registro *p = lista; p != NULL && i < RANKING_TOP; p = p->prox, i++) {
        snprintf(linha, sizeof linha, "%d. %s - %d", i + 1, p->nome, p->pontos);
        DrawText(linha, x, y + i * 22, 20, COR_TEXTO);
    }
}

/* 11. Libera todos os nós e deixa *lista = NULL. */
void rankingLiberar(Registro **lista) {
    while (*lista != NULL) {
        Registro *aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}