# escaPIF

## Descrição Geral
escaPIF é um jogo de fuga desenvolvido em C com a biblioteca [raylib](https://www.raylib.com/) 5.5. O jogador controla um aluno preso no Brum e para conseguir sair, ele precisa reunir 10 estrelas do conhecimento espalhadas pelas salas do prédio, enquanto desvia das distrações que tentam tirar seu foco, como o sono, o celular, as redes sociais e os bugs no código.

## Mecânica
O jogador começa com 3 vidas e se move pelas salas usando o teclado. As estrelas do conhecimento ficam espalhadas pelas 3 salas e são coletadas quando o jogador passa por elas. Os professores são aliados que aparecem nas salas : ao encontrá-los, o aluno recebem uma vida, um poder ou estrela coringa. As distrações estão paradas pelo mapa; se encostar nelas o jogador perde 1 vida, se ele perder as 3 vidas o jogo recomeça. As salas se conectam por portas, e o jogador passeia entre elas para encontrar todas as estrelas. Ao reunir as 10 estrelas, a saída do prédio é liberada e o jogador vence/ passou em PIF. A pontuação considera o tempo gasto e as vidas restantes e a existência ou não da estrela coringa , e então é registrado uma pontuação no ranking.

## Requisitos técnicos atendidos:
- Animação e movimento: deslocamento do jogador e das distrações em tempo real.-
- Colisão: jogador x paredes, jogador x estrelas, jogador x distrações, jogador x professores/monitores.
- Structs: representação do jogador, das distrações, dos aliados, das estrelas e das salas.
- Ponteiros: manipulação das listas e passagem de dados entre funções.
- Alocação dinâmica: criação e liberação de distrações e estrelas com malloc e free.
- Listas encadeadas: controle das distrações ativas e das estrelas coletadas.
- Matrizes: mapa de cada sala do prédio.
- Arquivos: leitura dos mapas das salas a partir de arquivos de texto e gravação do ranking de melhores pontuações.

## Como compilar e rodar
A raylib já vem no repositório (pasta `raylib/`, versão Linux/WSL 64 bits). Só é preciso instalar o compilador e as bibliotecas de janela uma vez:

```
sudo apt install build-essential git libgl1-mesa-dev libx11-dev
```

Depois, na pasta do projeto:

```
make run      # compila e abre o jogo (ESC fecha)
make clean    # apaga a pasta build/
```

- Windows: use o WSL (`wsl --install` no PowerShell como administrador) e rode os comandos acima no Ubuntu.
- macOS: `brew install raylib` e troque a linha `LIBS` do `Makefile` pelas linhas comentadas de macOS.

## Estrutura
- `include/tipos.h`: constantes, cores e structs (do trio).
- `include/mapa.h`, `include/ranking.h`, `src/mapa.c`, `src/ranking.c`, `mapas/`: Pessoa A.
- `include/entidades.h`, `src/entidades.c`: Pessoa B.
- `include/jogo.h`, `src/jogo.c`, `src/main.c`: Pessoa C.
- `raylib/`: biblioteca raylib 5.5 (licença zlib em `raylib/LICENSE`).
