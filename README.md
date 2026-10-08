# escaPIF

## Descrição Geral
escaPIF é um jogo de fuga em linha de comando desenvolvido em C com a biblioteca cli-lib. O jogador controla um aluno preso no Brum e para conseguir sair, ele precisa reunir 10 estrelas do conhecimento espalhadas pelas salas do prédio, enquanto desvia das distrações que tentam tirar seu foco, como o sono, o celular, as redes sociais e os bugs no código.

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
