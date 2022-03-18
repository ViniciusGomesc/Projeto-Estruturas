#include "Fila_Dinamica.h"
#include "jogador.h"
#include "Tentantiva.h"

#define TAM 8;

/* 
  0 = Espaço vazio 
  1 = Player
  2 = X
  3 = Chegada
*/

const int espaco_vazio = 0;
const int obstaculo = 2;
const int chegada = 3;

// Cria o tabuleiro dinamicamente colocando 0 em todas as posições
int** criar_tabuleiro(){

    int linhas = TAM;
    int colunas = TAM;
    int **matriz;

    matriz = calloc(linhas, sizeof(int*));

    for(linhas = 0; linhas < TAM linhas++){
      matriz[linhas] = calloc(colunas, sizeof(int));
    }

    return matriz;

}

// Preenche o tabuleiro de acordo com a fase.
void preenche_tabuleiro(int **tabuleiro, int fase){

    if(!tabuleiro){
      printf("\nERRO no Tabuleiro");
      return;
    }else{
      tabuleiro[0][0] = 1;
      tabuleiro[7][7] = chegada;
      switch(fase){
        case 1:
          tabuleiro[2][1] = obstaculo;
          tabuleiro[2][2] = obstaculo;
          tabuleiro[0][5] = obstaculo;
          tabuleiro[1][5] = obstaculo;
          tabuleiro[5][0] = obstaculo;
          tabuleiro[6][0] = obstaculo;
          tabuleiro[5][6] = obstaculo;
          tabuleiro[5][7] = obstaculo;
        break;

        case 2:
          tabuleiro[2][0] = obstaculo;
          tabuleiro[2][1] = obstaculo;
          tabuleiro[2][2] = obstaculo;
          tabuleiro[1][4] = obstaculo;
          tabuleiro[2][4] = obstaculo;
          tabuleiro[1][6] = obstaculo;
          tabuleiro[1][7] = obstaculo;
          tabuleiro[4][4] = obstaculo;
          tabuleiro[5][3] = obstaculo;
          tabuleiro[5][4] = obstaculo;
          tabuleiro[6][0] = obstaculo;
          tabuleiro[6][1] = obstaculo;
          tabuleiro[5][7] = obstaculo;
          tabuleiro[6][7] = obstaculo;
          tabuleiro[7][4] = obstaculo;
          tabuleiro[7][5] = obstaculo;
        break;

        case 3:
          tabuleiro[0][1] = obstaculo;
          tabuleiro[1][1] = obstaculo;
          tabuleiro[2][1] = obstaculo;
          tabuleiro[0][3] = obstaculo;
          tabuleiro[0][4] = obstaculo;
          tabuleiro[0][5] = obstaculo;
          tabuleiro[0][7] = obstaculo;
          tabuleiro[1][7] = obstaculo;
          tabuleiro[2][7] = obstaculo;
          tabuleiro[2][3] = obstaculo;
          tabuleiro[2][4] = obstaculo;
          tabuleiro[3][3] = obstaculo;
          tabuleiro[4][0] = obstaculo;
          tabuleiro[4][1] = obstaculo;
          tabuleiro[4][2] = obstaculo;
          tabuleiro[6][0] = obstaculo;
          tabuleiro[6][1] = obstaculo;
          tabuleiro[6][2] = obstaculo;
          tabuleiro[4][6] = obstaculo;
          tabuleiro[4][5] = obstaculo;
          tabuleiro[5][7] = obstaculo;
          tabuleiro[7][4] = obstaculo;
          tabuleiro[7][5] = obstaculo;
          tabuleiro[6][5] = obstaculo;
        break;
    }
  }
}

void next_fase(int **tabuleiro, Player *jg, Tentativa *t){

  if(jg->pos1 == 7 && jg->pos2 == 7){

    t->fases = t->fases + 1;

    system("cls||clear");
    printf("Parabens voce avancou para proxima fase!!!");
    getchar();

  }else{
    t->tentativa = t->tentativa - 1;

    if(t->tentativa == 0){
      printf("Game Over");
      exit(1);
    }
  }
}

// Imprime o tabuleiro com a fase completa.
void imprime_tabuleiro(int **tabuleiro){

    int linhas;
    int colunas;
    int i;
    
    for(linhas = 0; linhas < TAM linhas++){
      for(i = 0; i < TAM i++){
        printf("|---");
      }
      printf("|\n");
      for(colunas = 0; colunas < TAM colunas++){
        printf("|");
        if(tabuleiro[linhas][colunas] == espaco_vazio){
          printf("   ");
        }else if(tabuleiro[linhas][colunas] == 1){
          printf(" P ");
        }else if(tabuleiro[linhas][colunas] == obstaculo){
          printf(" X ");
        }else if(tabuleiro[linhas][colunas] == chegada){
          printf(" O ");
        }
      }
      printf("|\n");
    }
    for(i = 0; i < TAM i++){
      printf("|---");
    }
    printf("|\n");
    getchar();
}

void show_fase(int **tabuleiro, int fase){

    printf("\t\t\t\t\t\tSentido do player no tabuleiro: [ P > ]\n\n");
    printf("\t\t\t\t\t\tComandos:\n");
    printf("\t\t\t\t\t\t1) X X X\n");
    
    switch(fase){
        case 1:
          printf("Tabuleiro da primeira fase:");
        break;
        
        case 2:
          printf("Tabuleiro da segunda fase:");
        break;
        
        case 3:
          printf("Tabuleiro da terceira fase:");
        break;
    }
    printf("\t\t\t2) X X X \n");
    printf("\t\t\t\t\t\t3) X X X \n");
    printf("\t\t\t\t\t\t4) X X X \n");

    imprime_tabuleiro(tabuleiro);
}

// Desaloca o tabuleiro criado na memoria.
void desalocar_tabuleiro(int **tabuleiro){
  
    int linhas;

    for(linhas = 0; linhas < TAM linhas++){
      free(tabuleiro[linhas]);
    }

    free(tabuleiro);
}

// Pega os comandos do player
void comandos(Fila *f, int **tabuleiro, int fase){

    Comando c;
    int op;

    do{

    system("cls||clear");

    show_fase(tabuleiro, fase);

    printf("\nEntre com o comando que deseja inserir na fila: ");
    scanf("%d", &c.comando);
    getchar();

    printf("\nEntre com a quantidade de vezes que voce deseja realizar esse comando: ");
    scanf("%d", &c.repeticoes);
    getchar();

    enfileirar(f, &c);

    printf("\nDeseja inserir mais algum comando na fila? Caso sim, digite '1', caso nao, digite '0': ");
    scanf("%d", &op);
    getchar();

    }while(op != 0);
}

// Atualiza o tabuleiro com as novas posições
void atualizar_tabuleiro(int **tabuleiro, Player *jg){
  tabuleiro[jg->pos1][jg->pos2] = 1;
  imprime_tabuleiro(tabuleiro);

}
// Exibe a direção atual do player.
void exibir_direcao(Player *jg, Tentativa *t){

  printf("\n\n\t\t\t\t\t\tTentativas: %d\n\n", t->tentativa);
  if(jg->direcao == 1){
    printf("\n\n\t\t\t\t\t\t[ P > ]\n\n");
  }else if(jg->direcao == 2){
    printf("\n\n\t\t\t\t\t\t[ P V ]\n\n");
  }else if(jg->direcao == 3){
    printf("\n\n\t\t\t\t\t\t[ P < ]\n\n");
  }else{
    printf("\n\n\t\t\t\t\t\t[ P ꓥ ]\n\n");
  }
}

// Move a direção do player.
void Fase1(int **tabuleiro, Player *jg, Fila *ptr, Tentativa *t){
  
  NO *aux;
  int i, j;

  do{
    aux = ptr->inicio;
    ptr->inicio = (ptr->inicio)->prox;
    if(aux->info.comando == 1){
      for(i = 0; i < aux->info.repeticoes; i++){ // 
        system("cls||clear");
        exibir_direcao(jg, t);
        atualizar_tabuleiro(tabuleiro, jg);
        if(jg->direcao == 1){
          for(j = 0; j < 4; j++){
            if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 + 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 2){
          for(j = 0; j < 4; j++){
            if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos1 = jg->pos1 + 1;       
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 3){
          for(j = 0; j < 4; j++){
            if(tabuleiro[jg->pos1][jg->pos2-1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 - 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 4){
          for(j = 0; j < 4; j++){
            if(tabuleiro[jg->pos1-1][jg->pos2] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos1 = jg->pos1 - 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }
      }

    }else if(aux->info.comando == 2){
      for(i = 0; i < aux->info.repeticoes; i++ ){
        system("cls||clear");
        exibir_direcao(jg, t);
        atualizar_tabuleiro(tabuleiro, jg);
        if(jg->direcao == 1){
          if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos2 = jg->pos2 + 1;
          }
          jg->direcao = jg->direcao + 1;
          if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos1 = jg->pos1 + 1;
          }
          jg->direcao = jg->direcao +1;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 2){
          if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos1 = jg->pos1 + 1;
          }
          jg->direcao = jg->direcao - 1;
          if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos2 = jg->pos2 + 1;
          }
          jg->direcao = jg->direcao +3;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 3){
          if(tabuleiro[jg->pos1][jg->pos2-1] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos2 = jg->pos2 - 1;
          }
          jg->direcao = jg->direcao - 1;
          if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos1 = jg->pos1 + 1;
          }
          jg->direcao = jg->direcao + 1;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 4){
          if(tabuleiro[jg->pos1-1][jg->pos2] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos1 = jg->pos1 - 1;
          }
          jg->direcao = jg->direcao - 3;
          if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
            tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
            jg->pos2 = jg->pos2 + 1;
          }
          jg->direcao = jg->direcao +3;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }
      }
    }else if(aux->info.comando == 3){
      for(i = 0; i < aux->info.repeticoes; i++ ){
        system("cls||clear");
        exibir_direcao(jg, t);
        atualizar_tabuleiro(tabuleiro, jg);
        if(jg->direcao == 1){
          jg->direcao = jg->direcao + 3;
          for(j = 0; j < 2; j++){
            if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 + 1;
            }
          }
          jg->direcao = jg->direcao - 3;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 2){
          jg->direcao = jg->direcao - 1;
          for(j = 0; j < 2; j++){
            if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 + 1;
            }
          }
          jg->direcao = jg->direcao + 1;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 3){
          jg->direcao = jg->direcao - 1;
          for(j = 0; j < 2; j++){
            if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos1 = jg->pos1 + 1;
            }
          }
          jg->direcao = jg->direcao + 1;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 4){
          jg->direcao = jg->direcao - 1;
          for(j = 0; j < 2; j++){
            if(tabuleiro[jg->pos1][jg->pos2-1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 - 1;
            }
          }
          jg->direcao = jg->direcao + 1;
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }
      }
    }else{
      for(i = 0; i < aux->info.repeticoes; i++ ){
        system("cls||clear");
        exibir_direcao(jg, t);
        atualizar_tabuleiro(tabuleiro, jg);
        if(jg->direcao == 1){
          jg->direcao = jg->direcao + 1;
          for(j = 0; j < 3; j++){
            if(tabuleiro[jg->pos1+1][jg->pos2] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos1 = jg->pos1 + 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 2){
          jg->direcao = jg->direcao - 1;
          for(j = 0; j < 3; j++){
            if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 + 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 3){
          jg->direcao = jg->direcao + 1;
          for(j = 0; j < 3; j++){
            if(tabuleiro[jg->pos1-1][jg->pos2] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos1 = jg->pos1 - 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }else if(jg->direcao == 4){
          jg->direcao = jg->direcao - 3;
          for(j = 0; j < 3; j++){
            if(tabuleiro[jg->pos1][jg->pos2+1] != obstaculo){
              tabuleiro[jg->pos1][jg->pos2] = espaco_vazio;
              jg->pos2 = jg->pos2 + 1;
            }
          }
          system("cls||clear");
          exibir_direcao(jg, t);
          atualizar_tabuleiro(tabuleiro, jg);
        }
      }
    }
    free(aux);
  }while(ptr->inicio != NULL);

  next_fase(tabuleiro, jg, t);
}