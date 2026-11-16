# escaPIF

## Descrição Geral
escaPIF é um jogo de fuga em 2D desenvolvido em C com a biblioteca raylib. O jogador controla um aluno preso no Brum e, para conseguir escapar, precisa reunir 10 estrelas do conhecimento espalhadas pelas salas do prédio, enquanto desvia das distrações que tentam tirar seu foco: o celular, as redes sociais, a conversa, o sono e os vírus no código.

## Mecânica
O jogador começa com 3 vidas e se move usando o teclado. As estrelas do conhecimento ficam espalhadas pelas 3 salas e são coletadas quando o jogador passa por elas. Mas atenção: cada sala contém 1 estrela falsa(que são visualmente iguais as verdadeiras), e se o jogador pegá-la, ele volta para o início da sala em que está. Os 3 professores (Péricles , Daniel e Thiaguinho), são aliados que aparecem um em cada sala. Ao encontrá-los, o aluno recebe um presente: uma vida extra, uma estrela extra, tempo extra de 20 segundos ( 20 segundos são subtraídos do tempo de jogo) ou o poder de 3 quebrar paredes (abrindo atalhos pelo mapa). 
As distrações ficam paradas pelo mapa e se o jogador encostar nelas, perde 1 vida, caso as 3 vidas forem perdidas, o jogo recomeça. As salas se conectam por portas, e o jogador circula entre elas para encontrar todas as estrelas. 
Para escapar (passar em PIF!), o jogador precisa reunir no mínimo 7 estrelas. A pontuação que vai para o ranking considera: estrelas coletadas, vidas restantes e se tempo gasto foi menor do que o padrão estabelecido.

## Requisitos técnicos atendidos:
- Animação e movimento: deslocamento do jogador e das distrações em tempo real.-
- Colisão: jogador x paredes, jogador x estrelas, jogador x distrações, jogador x professores/monitores.
- Structs: representação do jogador, das distrações, dos aliados, das estrelas e das salas.
- Ponteiros: manipulação das listas e passagem de dados entre funções.
- Alocação dinâmica: criação e liberação de distrações e estrelas com malloc e free.
- Listas encadeadas: controle das distrações ativas e das estrelas coletadas.
- Matrizes: mapa de cada sala do prédio.
- Arquivos: leitura dos mapas das salas a partir de arquivos de texto e gravação do ranking de melhores pontuações.
