#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"

int movimentos(int x,  int y,  int N, int T ,  int p,  int **matriz, int *a, int *b, long int i){

  int m1 = 0, m2 =0, m3 = 0, m4 = 0;

  /*variavel para guardar o valor da posicao x-1*/
  if(x-1>=0){
    if(p>matriz[x-1][y]){
      m1 = p-matriz[x-1][y];
    }else{
      m1 = (p -matriz[x-1][y])*(-1);
    }
  }

  /*variavel para guardar o valor da posicao y+1*/
  if(y+1<N){
    if(p>matriz[x][y+1]){
      m2 = p-matriz[x][y+1];
    }else{
      m2 = (p -matriz[x][y+1])*(-1);
    }
  }

  /*variavel para guardar o valor da posicao x+1*/
  if(x+1<N){
    if(p>matriz[x+1][y]){
      m3 = p-matriz[x+1][y];
    }else{
      m3 = (p -matriz[x+1][y])*(-1);
    }
  }

  /*variavel para guardar o valor da posicao y-1*/
  if(y-1>=0){
    if(p>matriz[x][y-1]){
      m4 = p-matriz[x][y-1];
    }else{
      m4 = (p -matriz[x][y-1])*(-1);
    }
  }

  /*verificar se eh possivel subir*/
  if(x-1>=0){
    if(m1<=T && matriz[x-1][y]!=p){
      matriz[x-1][y]=p;
      x = x-1;
      /*verificar se ha mais de um caminho valido*/
      if((m2<=T && m2>0) || (m3<=T && m3>0) || (m4<=T && m4>0)){
        a[i] = x+1;
        b[i] = y;
        i++;
      }
      movimentos(x, y, N, T, p,matriz, a, b, i);
      return 1;
    }
  }
  
  /*verificar se eh possivel ir para a direita*/
  if(y+1<N){
    if(m2<=T && matriz[x][y+1]!=p){
      matriz[x][y+1]=p;
      y = y+1;
      /*verificar se ha mais de um caminho valido*/
      if((m1<=T && m1>0) || (m3<=T && m3>0) || (m4<=T && m4>0)){
        a[i] = x;
        b[i] = y-1;
        i++;
      }
      movimentos(x, y, N, T, p, matriz,a ,b, i);
      return 1;
    }
  }
    

  /*verificar se eh possivel descer*/
  if(x+1<N){
    if(m3<=T && matriz[x+1][y]!=p){
      matriz[x+1][y]=p;
      x = x+1;
      /*verificar se ha mais de um caminho valido*/
      if((m2<=T && m2>0) || (m1<=T && m1>0) || (m4<=T && m4>0)){
        a[i] = x-1;
        b[i] = y;
        i++;
      }
      movimentos(x, y, N, T, p, matriz, a, b, i);
      return 1;
    }
  }
    
  /*verificar se eh possivel ir para a esquerda*/
  if(y-1>=0){
    if(m4<=T && matriz[x][y-1]!=p){
      matriz[x][y-1]=p;
      y = y-1;
      /*verificar se ha mais de um caminho valido*/
      if((m2<=T && m2>0) || (m3<=T && m3>0) || (m1<=T && m1>0)){
        a[i] = x;
        b[i] = y+1;
        i++;
      }
      movimentos(x, y, N, T, p, matriz, a, b, i);
      return 1;
    }
  }
  
  /*para encerrar a funcao*/
  if(i==0)
    return 0;

  /*para retornar para a ultima posicao que tinha mais de um caminho*/
  if(x!=a[i] || y!=b[i]){
    x = a[i];
    y = b[i];
    movimentos(x, y, N, T, p, matriz, a, b, i);  
  }else{
    /*para excluir a ultima posicao que tinha mais de um caminho*/
    a[i]='\0';
    b[i]='\0';
    i--;
    x = a[i];
    y = b[i];
    movimentos(x, y, N, T, p, matriz, a, b, i);
  }

  return  0 ;
}

/*funcao para deixar todos os elemenros no mesmo valor*/
int igualar(int x,  int y,  int N, int **matriz){
  for (int i=0; i <N; i++){
    for(int j=0; j<N; j++){
      matriz[i][j]=matriz[x][y];
    }
  }
  return 0;
}

int preencher_matriz(int **matriz, int T, int N){
  /*Determinar a semente do valor aleatorio*/
  srand(T);
  
  /*Inserir valores aleatorios*/
  for (int i=0; i < N; i++){
    for(int j=0; j<N; j++){
      matriz[i][j]=rand()%256;
    }
  }
  return 0;
}

int imprimir_matriz(int **matriz, int N){
  for (int i=0; i < N; i++){
    for(int j=0; j<N; j++){
      printf("%d\t", matriz[i][j]);
      if(j==N-1){
        printf("\n");
      }
    }
  }
  return 0;
}

/*funcao para criar a imagem PGM*/
void imagem(FILE *fp, int largura, int altura, int **imagem){
  int i, j, aux = 0; 
  fprintf(fp, "P2\n");  
  
  /*determinar a largura e a altura da imagem*/
  fprintf(fp, "%d %d\n", largura, altura);  
  
  /*determinar o maior valor do pixel*/
  fprintf(fp, "255\n");  
  int count = 0; 
  for (i = 0; i < altura; i++) { 
    for (j = 0; j < largura; j++) { 
      aux = imagem[i][j]; 
  
      /*escrever os valores do pixel no arquivo*/
      fprintf(fp, "%d ", aux); 
    } 
    fprintf(fp, "\n"); 
  } 
}