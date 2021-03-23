#include <stdio.h>
#include <stdlib.h>

int novo_caminho(int *a, int *b, char **labirinto){
  int x=0, y=0;
  x=*a;
  y=*b;
  while(labirinto[x][y]!='.'){       
  /*verificar se tem um caminho nao percorrido para subir*/
  if(labirinto[x-1][y] =='.' || labirinto[x][y-1] =='.' || labirinto[x][y+1] =='.' || labirinto[x+1][y] =='.'){
    break;
  }

  /*verificar se eh possivel subir*/
  if(labirinto[x-1][y] =='*'){
    if(labirinto[x-1][y]!='.' && labirinto[x][y-1]!='.' && labirinto[x][y+1]!='.' && labirinto[x+1][y]!='.'){
      x--;
      labirinto[x+1][y]='1';
    }
  }

  /*verificar se eh possivel ir para a direita*/
  if(labirinto[x][y+1]=='*'){
    if(labirinto[x-1][y]!='.' && labirinto[x][y-1]!='.' && labirinto[x+1][y]!='.'){
      y++;
      labirinto[x][y-1]='1';
    }
  }

  /*verificar se eh possivel descer*/
  if(labirinto[x+1][y]=='*'){
    if(labirinto[x-1][y]!='.' && labirinto[x][y-1]!='.' && labirinto[x][y+1]!='.' && labirinto[x+1][y]!='.'){
      x++;
      labirinto[x-1][y]='1';
    }
  }

  /*verificar se eh possivel ir para a esquerda*/
  if(labirinto[x][y-1]=='*'){
    if(labirinto[x-1][y]!='.' && labirinto[x][y+1]!='.' && labirinto[x+1][y]!='.'){
      y--;
      labirinto[x][y+1]='1';
    }
  }
        
  /*verificar se o unico caminho disponivel ja foi percorrido*/
  /*caminho para cima*/
  if(labirinto[x-1][y] == '1' && labirinto[x][y+1]=='#' && labirinto[x][y-1]=='#' && labirinto[x+1][y] == '1'){
    labirinto[x-1][y]='*';
  }

  /*verificar se o unico caminho disponivel ja foi percorrido*/
  /*caminho pela direita*/
  if(labirinto[x][y+1] =='1' && labirinto[x+1][y]=='#' && labirinto[x-1][y]=='#' && labirinto[x][y-1] =='1'){
    labirinto[x][y+1]='*';
  }

  /*verificar se o unico caminho disponivel ja foi percorrido*/
  /*caminho para baixo*/
  if(labirinto[x+1][y] =='1' && labirinto[x][y+1]=='#' && labirinto[x][y-1]=='#' && labirinto[x-1][y] =='1'){
    labirinto[x+1][y]='*';
  }

  /*verificar se o unico caminho disponivel ja foi percorrido*/
  /*caminho pela esquerda*/
  if(labirinto[x][y-1] =='1' && labirinto[x+1][y]=='#' && labirinto[x-1][y]=='#' && labirinto[x][y+1] =='1'){
    labirinto[x][y-1]='*';
    }
  }

  /*salvar os valores de x e y nas variaveis a e b para 
   passar os valores para a proxima funcao*/
  *a=x;
  *b=y;
  return 1;
}

int movimentos(int x,  int y,  int M ,  int N,  char **labirinto)  {
    /*verificar se eh possivel subir*/
    if(labirinto[x-1][y]=='.'){
      labirinto[x-1][y]='*';
      movimentos(x-1, y, M , N , labirinto);
      return 1;
    }

    /*verificar se eh possivel ir para a direita*/
    if(labirinto[x][y+1]=='.'){
      labirinto[x][y+1]='*';
      movimentos(x, y+1, M , N , labirinto);
      return 1;
    }

    /*verificar se eh possivel descer*/
    if(labirinto[x+1][y]=='.'){
      labirinto[x+1][y]='*';
      movimentos(x+1, y, M , N , labirinto);
      return 1;
    }


    /*verificar se eh possivel ir para a esquerda*/
    if(labirinto[x][y-1]=='.'){
      labirinto[x][y-1]='*';
      movimentos(x, y-1, M , N , labirinto);
      return 1;
    }

    /*se estiver subindo e encontrar um caminho sem saida*/
    if(labirinto[x-1][y]=='#' && labirinto[x][y] =='*'  && labirinto[x][y+1]=='#' && labirinto[x][y-1]=='#'){
      novo_caminho(&x, &y, labirinto);
      movimentos(x, y, M , N , labirinto);
      return 1;
    }

    /*se estiver indo para a esquerda e encontrar um caminho sem saida*/
    if(labirinto[x][y-1]=='#' && labirinto[x][y] =='*'  && labirinto[x+1][y]=='#' && labirinto[x-1][y]=='#'){
      novo_caminho(&x, &y, labirinto);
      movimentos(x, y, M , N , labirinto);
      return 1;
    }

    /*se estiver indo para a direita e encontrar um caminho sem saida*/
    if(labirinto[x][y+1]=='#' && labirinto[x][y] =='*'  && labirinto[x+1][y]=='#' && labirinto[x-1][y]=='#'){
      novo_caminho(&x, &y, labirinto);
      movimentos(x, y, M , N , labirinto);
      return 1;
    }

    /*se estiver descendo e encontrar um caminho sem saida*/
    if(labirinto[x+1][y]=='#' && labirinto[x][y] =='*'  && labirinto[x][y+1]=='#' && labirinto[x][y-1]=='#'){
      novo_caminho(&x, &y, labirinto);
      movimentos(x, y, M , N , labirinto);
      return 1;
    }

    return  0 ;
}

/*funcao para adicionar cada palavra do arquivo em uma posicao da string palavra*/
void arquivo_para_string(char **palavra, long int  *quantidade_de_linhas, FILE *fp){
  long int i=0;
  while(fgets(palavra[i], 1000, fp) != NULL){ 
  i++;
  /*para calcluar a quantia de linhas dentro do arquivo*/
  *quantidade_de_linhas=i;
  }
}

/*funcao para ler o arquivo*/
void ler_arquivo(FILE **fp){
  char arquivo[30];
  /*escolher o arquivo para abrir*/
  scanf("%s", arquivo);
  
  /*abrir arquivo*/
  *fp=fopen(arquivo, "r");
  if(fp==NULL){
    printf("Nao foi possivel abrir o arquivo\n");
  }
}

/*funcao imprimir labirinto*/
void imprimir_labirinto(int *visitados, char **labirinto, int M, int N){
  int i =0, j=0, visitado = 0;
  /*loop para substituir todos os 1 por '*' */
  for(i=0; i<=M; i++){
    for(j=0; j<=N; j++){
      if(labirinto[i][j]=='1'){
        labirinto[i][j]='*';
      }
      if(labirinto[i][j]=='\n'){
        labirinto[i][j]='\0';
      }
    }
  }

  /*loop para imprmir o labirinto e
   *contar a quantidade de '*'*/
  for(i=0; i<M; i++){
    for(j=0; j<N; j++){
      printf("%c",labirinto[i][j]);
      if(labirinto[i][j]=='*'){
        visitado++;
      }
    }
    printf("\n");
  }
  *visitados = visitado;
}

/*funcao imprimir valores*/
void imprimir_valores(int pessoas, int caminhos, int visitados, double exploracao){
  printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
  printf("Veja abaixo os detalhes da sua fuga:\n");
  printf("----Pessoas te procurando: %d\n", pessoas);
  printf("----Numero total de caminhos validos:   %d\n", caminhos);
  printf("----Numero total de caminhos visitados: %d\n", visitados);
  printf("----Exploracao total do labirinto: %.1lf%%\n", exploracao);
}

int main() {
  
  char **linha, **matriz;
  long int quantidade_de_linhas=0;
  int i = 0, j = 0, M = 0, N = 0, x = 0, y = 0, visitados =0;
  double exploracao = 0;
  int qtd_pessoas = 0, qtd_caminhos = 0;
  FILE *fp;

  ler_arquivo(&fp);
  
  linha=(char**)malloc(800*sizeof(char*));
  for(i=0; i<800; i++){
    linha[i]=(char*)malloc(300*sizeof(char));
  }

  /*armazenar cada frase do arquivo em um vetor da string*/
  arquivo_para_string(linha, &quantidade_de_linhas, fp);

  /*fechar arquivo*/
  fclose(fp);

  /*salvar a quantidade de linhas e colunas*/
  M = atoi(&linha[0][0]);
  N = atoi(&linha[0][2]);

  /*salvar as coordenadas iniciais*/
  x = atoi(&linha[1][0]);
  y = atoi(&linha[1][2]);

  /*determinar o tamanho da matriz e alocar memoria*/
  matriz=(char**)malloc((M+1)*sizeof(char*));
  for(i=0; i<M+1; i++){
    matriz[i]=(char*)malloc((N+1)*sizeof(char));
  }

  /*passar o labirinto para uma matriz*/
  for(i=0; i<=M; i++){
    for(j=0; j<=N; j++){
      matriz[i][j] = linha[i+2][j];
      /*contar a quantidade de pessoas*/
      if(matriz[i][j] == '#'){
        qtd_pessoas++;
      }
      /*contar a quantidade de caminhos*/
      if(matriz[i][j] == '.'){
        qtd_caminhos++;
      }
      /*encontrar a posicao inicial*/
      if(i == x && j == y){
        matriz[i][j] = '*';
      }
    }
  }
  
  /*chamar funcao*/
  movimentos(x, y, M, N, matriz);

  /*chamar a funcao imprimir_labirinto*/
  imprimir_labirinto(&visitados, matriz, M, N);

  /*calcular a porcentagem explorada do labirinto*/
  exploracao = ((visitados*100)/qtd_caminhos);

  /*chamar a funcao imprimir os valores*/
  imprimir_valores(qtd_pessoas, qtd_caminhos, visitados, exploracao);
  
  /*liberar memoria*/
  free(linha);
  free(matriz);
  return 0;
}