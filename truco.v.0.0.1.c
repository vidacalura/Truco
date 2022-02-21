#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Declaração do tipo "Jogador", que representará os 2 jogadores
typedef struct {

  int rounds;
  char carta[3];
  int carta_naipe[3];

} Jogador;

typedef struct {

  int naipe;
  char valor;

} Carta_mesa;

void dar_mao(char carta[], int carta_naipe[], char baralho[]);
char tirar_vira(char baralho[]);
void mostrar_mao(char carta[], int carta_naipe[], char vira);
void mostrar_mesa(char carta, int naipe);
int definir_valor_cartas(char carta, int naipe, char vira);

int main() {
  // Define o idioma para português
  setlocale(LC_ALL, "Portuguese");

  // Permite geração de número aleatórios
  srand(time(0));

  // Declaração dos 2 jogadores
  Jogador player1, player2;
  Carta_mesa carta_mesa_player1, carta_mesa_player2;

  char vira, jogada;
  int vez = 0, rodada = 0, pontos_rodada, rand_carta, carta_mesa1_valor = 0, carta_mesa2_valor = 0;

  int player1_pontos = 0;
  int player2_pontos = 0;

  // Início do jogo
  while (player1_pontos < 12 || player2_pontos < 12) {
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

    vez = rodada;

    // Início da rodada
    while (player1.rounds < 2 && player2.rounds < 2){

      jogada = ' ';

      do {
        // Define a carta do jogador 2
        rand_carta = rand() % 3;
        carta_mesa_player2.valor = player2.carta[rand_carta];
        carta_mesa_player2.naipe = player2.carta_naipe[rand_carta];
      } while (player2.carta[rand_carta] == ' ');
        
      player2.carta[rand_carta] = ' ';

      // Mostra as cartas ao jogador 1
      mostrar_mao(player1.carta, player1.carta_naipe, vira);
      sleep(2);

      if (vez % 2 == 1){
        printf("        Seu oponente jogou: \n");
        mostrar_mesa(carta_mesa_player2.valor, carta_mesa_player2.naipe);
        printf("\n");
        fflush(stdout);
        sleep(1);
      }


      // Recebe evento do jogador
      while (jogada != '1' && jogada != '2' && jogada != '3') {
        printf(" \
        1: joga sua primeira carta na mão (%c)\n \
        2: joga sua segunda carta na mão (%c)\n \
        3: joga sua terceira carta na mão (%c)\n \
        T: para trucar\n", player1.carta[0], player1.carta[1], player1.carta[2]);

        // Registra o evento na variável "jogada"
        printf("         ");
        jogada = getchar();
        fflush(stdin);

        if (jogada != '1' && jogada != '2' && jogada != '3' && jogada != 'T' && jogada != 't') {
          printf("Favor inserir uma ação válida");
        }

        // Realizar e mostrar evento
        switch(jogada){
          // Em caso de jogar a primeira carta
          case '1':
            carta_mesa_player1.valor = player1.carta[0];
            carta_mesa_player1.naipe = player1.carta_naipe[0];
            player1.carta[0] = ' '; 
            break;
          // Em caso de jogar a segunda carta
          case '2':
            carta_mesa_player1.valor = player1.carta[1];
            carta_mesa_player1.naipe = player1.carta_naipe[1];
            player1.carta[1] = ' ';
            break;
          // Em caso de jogar a terceira carta
          case '3':
            carta_mesa_player1.valor = player1.carta[2];
            carta_mesa_player1.naipe = player1.carta_naipe[2];
            player1.carta[2] = ' ';
            break;
          case 't':
          case 'T':
            // Se o bot aceitar
            pontos_rodada = 3;
        }

        if (carta_mesa_player1.valor == ' '){
          jogada = ' ';
          printf("         Você não pode jogar uma mesma carta mais de uma vez\n");
        }
 
      }

      sleep(1);
      // Mostrar cartas na mesa
      printf("        Sua carta foi jogada: \n");
      mostrar_mesa(carta_mesa_player1.valor, carta_mesa_player1.naipe);
      sleep(2);

      if (vez % 2 == 0){
        printf("        Seu oponente jogou: \n");
        mostrar_mesa(carta_mesa_player2.valor, carta_mesa_player2.naipe);
        printf("\n");
        fflush(stdout);
        sleep(3);
      }

      // Ver qual carta é maior
      carta_mesa1_valor = definir_valor_cartas(carta_mesa_player1.valor, carta_mesa_player1.naipe, vira);
      carta_mesa2_valor = definir_valor_cartas(carta_mesa_player2.valor, carta_mesa_player2.naipe, vira);

      if (carta_mesa1_valor > carta_mesa2_valor){
        player1.rounds++;
        if (vez % 2 == 1)
          vez++;
      }
      else if (carta_mesa1_valor < carta_mesa2_valor){
        player2.rounds++;
        if (vez % 2 == 0)
          vez++;
      } 
      else {
        player1.rounds++;
        player2.rounds++;
      }
    }
    if (player1.rounds == 2) {
      player1_pontos + pontos_rodada;
      printf("         Você venceu a rodada! :)");
    }
    else {
      player2_pontos + pontos_rodada;
      printf("         Você perdeu a rodada :(");
    }
    
    printf("\n\n \
      |||//////////////////////////\n \
      |||\n \
      ||| Placar:\n \
      |||     Você: %d\n \
      |||     Bot:  %d\n \
      |||\n \
      |||//////////////////////////\n\n", player1_pontos, player2_pontos);
    fflush(stdout);

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
void mostrar_mao(char carta[], int carta_naipe[], char vira) {

  printf("        Vira = %c\n", vira);
  printf("        Sua mão:\n");

  for (int i = 0; i < 3; i++) {
    if (carta[i] != ' ') {
        for (int j = 0, n = 11; j < n; j++){
          printf("\n");
          if (j == 0 || j == n - 1){
            printf("          +-----------+");
          }
          else if (j == 5){
            switch (carta_naipe[i]){
              case 0:
                printf("          |     ♦     |");
                break;
              case 1:
                printf("          |     ♠     |");
                break;
              case 2:
                printf("          |     ♥     |");
                break;
              case 3:
                printf("          |     ♣     |");
                break;
            }  
          }
          else if (j == 1) {
            printf("          | %c         |", carta[i]);
          }
          else if (j == n - 2){
            printf("          |         %c |", carta[i]);
          }
          else {
            printf("          |           |");
          }
        }
      }
//      printf("\n");
    }
  printf("\n");
  fflush(stdout);
}

void mostrar_mesa(char carta, int carta_naipe){

  for (int j = 0, n = 11; j < n; j++){
    printf("\n");
    if (j == 0 || j == n - 1){
      printf("          +-----------+");
    }
    else if (j == 5){
      switch (carta_naipe){
        case 0:
          printf("          |     ♦     |");
          break;
        case 1:
          printf("          |     ♠     |");
          break;
        case 2:
          printf("          |     ♥     |");
          break;
        case 3:
          printf("          |     ♣     |");
          break;
        }  
      }
      else if (j == 1) {
        printf("          | %c         |", carta);
      }
      else if (j == n - 2){
        printf("          |         %c |", carta);
      }
      else {
        printf("          |           |");
      }
    }

  printf("\n");
  fflush(stdout);

}

int definir_valor_cartas(char carta, int naipe, char vira){

  int valor_carta, valor_vira;

  switch (vira){
    case '4':
      valor_vira = 0;
      break;
    case '5':
      valor_vira = 1;
      break;
    case '6':
      valor_vira = 2;
      break;
    case '7':
      valor_vira = 3;
      break;
    case 'Q':
      valor_vira = 4;
      break;
    case 'J':
      valor_vira = 5;
      break;
    case 'K':
      valor_vira = 6;
      break;
    case 'A':
      valor_vira = 7;
      break;
    case '2':
      valor_vira = 8;
      break;
    case '3':
      valor_vira = 9;
      break;
  }

  switch (carta){
    case '4':
      valor_carta = 0;
      break;
    case '5':
      valor_carta = 1;
      break;
    case '6':
      valor_carta = 2;
      break;
    case '7':
      valor_carta = 3;
      break;
    case 'Q':
      valor_carta = 4;
      break;
    case 'J':
      valor_carta = 5;
      break;
    case 'K':
      valor_carta = 6;
      break;
    case 'A':
      valor_carta = 7;
      break;
    case '2':
      valor_carta = 8;
      break;
    case '3':
      valor_carta = 9;
      break;
  }

  if (valor_carta == valor_vira + 1){
    valor_carta = 10 + naipe;
  }

  return valor_carta;

}



///////////////////////////
//
// Bugs
//
//////////////////////////

/*

Podem haver 2 cartas de mesmo número e mesmo naipe em jogo
Empatar na última rodada dá vitória a ambos os jogadores
Pontos não são marcados

*/

// Permitir omitir (virar) a carta
// Fazer caso de truco

// Criar mais funções 
// Formatar melhor o código
