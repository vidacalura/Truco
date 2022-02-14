#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declaração do tipo "Jogador", que representará os 2 jogadores
typedef struct {
  int pontos;
  int rounds;
  char carta[3];
  int carta_naipe[3];
} Jogador;

void dar_mao(char carta[], int carta_naipe[], char baralho[]);
char tirar_vira(char baralho[]);
void mostrar_cartas(char carta[], int carta_naipe[], char vira);
void embate();

int main() {
  // Define o idioma para português
  setlocale(LC_ALL, "Portuguese");

  // Permite geração de número aleatórios
  srand(time(0));

  // Declaração dos 2 jogadores
  Jogador player1, player2;

  player1.pontos = 0;
  player2.rounds = 0;

  char vira, jogada;
  int rodada = 0, pontos_rodada;

  // Início do jogo
  while (player1.pontos < 12 || player2.pontos < 12) {
    // Declaração do baralho
    char baralho[] = {'4', '4', '4', '4', '5', '5', '5', '5', '6', '6',
                      '6', '6', '7', '7', '7', '7', 'Q', 'Q', 'Q', 'Q',
                      'J', 'J', 'J', 'J', 'K', 'K', 'K', 'K', 'A', 'A',
                      'A', 'A', '2', '2', '2', '2', '3', '3', '3', '3'};

    pontos_rodada = 1;

    // Jogadores recebem suas cartas
    dar_mao(player1.carta, player1.carta_naipe, baralho);
    dar_mao(player2.carta, player2.carta_naipe, baralho);

    // Tira-se o vira
    vira = tirar_vira(baralho);

    player1.rounds = 0;
    player2.rounds = 0;

    // Mostra as cartas ao jogador 1
    mostrar_cartas(player1.carta, player1.carta_naipe, vira);

    // Player 1 começa
    if (rodada % 2 == 0) {
      do {
        // Recebe evento do jogador
        do {
          printf(" \
        1: joga sua primeira carta na mão\n \
        2: joga sua segunda carta na mão\n \
        3: joga sua terceiraa carta na mão\n \
        T: para trucar\n");
          fflush(stdout);
          // Registra o evento na variável "jogada"
          jogada = getchar();
          fflush(stdin);

          if (jogada != '1' && jogada != '2' && jogada != '3' &&
              jogada != 'T' && jogada != 't') {
            printf("Favor inserir uma ação válida");
          }

        } while (jogada != '1' && jogada != '2' && jogada != '3' &&
                 jogada != 'T' && jogada != 't');

        // Realizar e mostrar evento
        switch(jogada){
          // Em caso de jogar a primeira carta
          case '1':
            break;
          // Em caso de jogar a segunda carta
          case '2':
            break;
          // Em caso de jogar a terceira carta
          case '3':
            break;
          // Em caso de truco
          case 'T':
          case 't':
            break;
        }
        // Captar evento do adversário
        // Repetir até que player1.rounds == 2 || player2.rounds == 2 
        //(empate é round + 1 para ambos players)
      } while (player1.rounds < 2 || player2.rounds < 2);
    }
    // Player 2 começa
    else {
    }

    rodada++;
  }

  return 0;
}

// Função que determina as cartas dos jogadores
void dar_mao(char carta[], int carta_naipe[], char baralho[]) {
  int i = 0;

  while (i < 3) {
    int rand_num = rand() % 40;
    if (baralho[rand_num] != ' ') {
      carta[i] = baralho[rand_num];
      carta_naipe[i] = rand() % 4;
      baralho[rand_num] = ' ';
      i++;
    }
  }
}

// Função que tira o vira
char tirar_vira(char baralho[]) {

  while (1) {
    int rand_num = rand() % 40;
    if (baralho[rand_num] != ' ') {
      return baralho[rand_num];
    }
  }
}

// Função que mostra as suas cartas
void mostrar_cartas(char carta[], int carta_naipe[], char vira) {

  printf("        Vira = %c\n\n", vira);

  for (int i = 0; i < 3; i++) {
    if (carta[i] != ' ') {
      switch (carta_naipe[i]) {
      case 0:
        printf(" \
        +-----------+\n \
        |Ouros      |\n \
        |           |\n \
        |           |\n \
        |     %c     |\n \
        |           |\n \
        |           |\n \
        |           |\n \
        +-----------+",
               carta[i]);
        break;
      case 1:
        printf(" \
        +-----------+\n \
        |Espadas    |\n \
        |           |\n \
        |           |\n \
        |     %c     |\n \
        |           |\n \
        |           |\n \
        |           |\n \
        +-----------+",
               carta[i]);
        break;
      case 2:
        printf(" \
        +-----------+\n \
        |Copas      |\n \
        |           |\n \
        |           |\n \
        |     %c     |\n \
        |           |\n \
        |           |\n \
        |           |\n \
        +-----------+",
               carta[i]);
        break;
      case 3:
        printf(" \
        +-----------+\n \
        |Paus       |\n \
        |           |\n \
        |           |\n \
        |     %c     |\n \
        |           |\n \
        |           |\n \
        |           |\n \
        +-----------+",
               carta[i]);
        break;
      }
    }
    printf("\n");
  }
  fflush(stdout);
}

///////////////////////////
//
// Bugs
//
//////////////////////////

/*

Podem haver 2 cartas de mesmo número e mesmo naipe em jogo
Jogador pode jogar uma carta que não tem mais na mão

*/
