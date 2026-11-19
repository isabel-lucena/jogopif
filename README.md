# **escaPIF - Fuga do Brum**

## Descrição Geral

escaPIF é um jogo de fuga em 2D desenvolvido em C com a biblioteca raylib. O jogador controla um aluno preso no Brum e, para conseguir escapar, precisa reunir pelo menos 7 das 10 estrelas do conhecimento espalhadas pelas 3 salas do prédio, antes que o tempo acabe, enquanto desvia das distrações que tentam tirar seu foco: o celular, as redes sociais, a conversa, o sono e os vírus no código.

## Demonstração em vídeo

https://youtu.be/wn9y0k5BS7I

---

<details>
  <summary><b>**Compilação do projeto**</b></summary>
  <br>

O escaPIF é feito em C com a biblioteca raylib, que já vem no repositório, na pasta `raylib/`. O jogo roda no Linux. No Windows, use o WSL (Ubuntu).

### Pré-requisitos (só na primeira vez)
```
sudo apt update
sudo apt install build-essential libgl1-mesa-dev libx11-dev
```
- `build-essential`: instala o compilador `gcc` e o comando `make`.
- `libgl1-mesa-dev` e `libx11-dev`: permitem que a raylib abra a janela do jogo.

### Baixar o projeto
```
git clone https://github.com/isabel-lucena/jogopif.git
cd jogopif
```

### Makefile
O Makefile guarda a "receita" de compilação. Assim, você só precisa digitar uma palavra:

| Comando      | O que faz                                      |
|--------------|------------------------------------------------|
| `make`       | Compila tudo e cria o jogo em `./escapif`  |
| `make run`   | Compila e já abre o jogo                       |
| `make clean` | Apaga a pasta `build/` para compilar do zero   |

</details>

---

<details>
  <summary><b>Mecânica</b></summary>
  <br>

O jogador começa na Sala 1 com 3 vidas e se move pelo teclado. As 10 estrelas do conhecimento estão divididas entre as salas: 2 na Sala 1, 3 na Sala 2 e 5 na Sala 3. Elas são coletadas quando o jogador passa por cima delas. Mas atenção: cada sala contém 1 estrela falsa, visualmente igual às verdadeiras. Se o jogador pegá-la, a estrela falsa some e ele volta para a entrada da sala em que está.

Os 3 professores (Péricles, Daniel e Thiaguinho) são aliados, um em cada sala, desenhados como um círculo azul com a letra P. Ao encontrar com um professor, o aluno recebe um presente sorteado entre quatro:

- 1 estrela.
- 1 vida.
- 20 segundos a mais no relógio.
- o poder de quebrar 3 paredes: andando contra uma parede, ela é quebrada e vira chão, abrindo atalhos pelo mapa (as paredes da borda da sala não quebram).

CUIDADO! Existem distrações nas salas, algumas ficam paradas e algumas se movimentam, são quadrados vermelhos com uma letra que mostra o tipo (o tipo de cada uma é sorteado no começo da partida). Elas funcionam como obstáculos: o jogador não consegue passar por cima, e quando encosta em uma, sofre o efeito dela:

| Letra | Distração | Efeito |
| --- | --- | --- |
| C | Celular | perde 1 vida |
| R | Redes sociais | perde 20 segundos do relógio |
| Z | Sono | volta para a entrada da sala |
| B | Conversa | perde 1 vida e 10 segundos do relógio |
| V | Vírus | perde 1 estrela: a última coletada ou, se não tiver, uma extra de professor (sem nenhuma estrela, perde 1 vida) |

As salas se conectam por portas (`>`) em sequência. Por isso, é preciso pegar as estrelas de cada sala antes de atravessar a porta. A porta da Sala 3 é a saída do Brum e só abre se o jogador tiver no mínimo 7 estrelas. Ao atravessá-la, ele escapa (passa em PIF!).

O jogo acaba em derrota (tela "FIM DE JOGO! VOCÊ REPROVOU EM PIF!") se as vidas chegarem a 0 ou se o relógio de 180 segundos zerar. Nesse caso, não há pontuação nem registro no ranking, e ENTER (ou ESPAÇO) começa uma partida nova, desde a Sala 1, com o mesmo nome.

Na vitória, a pontuação final vai para o ranking e é calculada assim:

```
pontos = 120 x estrelas + 300 x vidas restantes + 15 x (180 - segundos gastos)
```

 O ranking guarda as 10 maiores pontuações no arquivo `ranking.txt`.

### O que aparece na tela

- No topo (HUD): vidas, estrelas (x/7), sala atual (x/3), tempo restante (fica vermelho nos últimos 30 segundos), quebras de parede restantes e avisos rápidos do que acabou de acontecer.
- `@` ciano: o aluno.
- Losango amarelo: estrela (verdadeira ou falsa).
- Quadrado vermelho com letra: distração.
- Círculo azul com P: professor.
- Bloco azul: parede.
- `>` branco: porta para a próxima sala / saída.

</details>

---

<details>
  <summary><b>Requisitos técnicos atendidos:</b></summary>
  <br>

- Animação e movimento: deslocamento do jogador em tempo real, célula por célula, com movimento contínuo ao segurar a tecla; o jogador pisca durante a invencibilidade depois de uma distração; o relógio e os avisos do HUD são atualizados a cada quadro (60 FPS).
- Colisão: jogador x paredes (bloqueia ou quebra, se ele tiver o poder), jogador x estrelas (verdadeiras e falsas), jogador x distrações, jogador x professores, jogador x portas/saída.
- Structs: `Jogador`, `Estrela`, `Distracao`, `Aliado` (professores), `ItemVida`, `Sala`, `Registro` (ranking), `Posicao` e `Jogo` (estado geral), definidas em `include/tipos.h`.
- Ponteiros: listas manipuladas por ponteiro para ponteiro (`Estrela **lista`, `Registro **lista`), funções que recebem `Jogo *` e `const Sala *`, e nós que são tirados de uma lista e passados para outra.
- Alocação dinâmica: ao carregar cada sala, cada estrela, distração e professor do mapa vira um nó criado com `malloc` (`entidadesExtrairDoMapa`); cada registro do ranking também usa `malloc`. Os nós são liberados com `free` quando o jogador pega um professor ou uma estrela falsa, quando o vírus tira uma estrela, ao começar uma partida nova e ao fechar o jogo (`salaLiberar`, `estrelasLiberar`, `rankingLiberar`).
- Listas encadeadas: cada sala tem listas de estrelas, distrações e professores; as estrelas coletadas formam uma lista do jogador (a estrela sai da lista da sala e entra na do jogador); o ranking é uma lista mantida em ordem decrescente de pontos.
- Matrizes: o mapa de cada sala é uma matriz de caracteres `char mapa[18][61]` (18 linhas x 60 colunas), e as 3 salas ficam no vetor `salas[3]`.
- Arquivos: leitura dos mapas a partir de `mapas/sala1.txt`, `mapas/sala2.txt` e `mapas/sala3.txt` (`fopen`/`fgets`), e leitura e gravação do ranking em `ranking.txt` (`fscanf`/`fprintf`, uma linha `nome pontos` por jogador).

</details>

---
