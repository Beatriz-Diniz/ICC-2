#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"


int main() {
  int N, x, y, T, i = 0, j=0;
  int **matriz, *a, *b;
  FILE *imagem_original;
  FILE *imagem_modificada;

  /*Inserir os valores*/
  scanf("%d", &N);
  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &T);

  /*Alocar matriz de acordo com o valor de N*/
  matriz = (int**)malloc(N*sizeof(int*));
  assert(matriz);
  for(i=0; i<N; i++){
    matriz[i] = (int*)malloc(N*sizeof(int));
    assert(matriz[i]);
  }
  a = (int*)malloc(20000*sizeof(int));
  b = (int*)malloc(20000*sizeof(int));

  /*preencher e imprimir a matriz original*/
  preencher_matriz(matriz, T, N); 
  imprimir_matriz(matriz, N);
  printf("\n"); 

  /*criar um arquivo PGM com os valores da matriz original*/
  imagem_original = fopen("imagem_original.pgm", "wb"); 
  imagem(imagem_original, N, N, matriz);
  fclose(imagem_original); 
  

  /*Se T = 0:
      *nao havera modificacao nos valores da matriz
   *Se T>0 e T<255:
      *p = matriz[x][y]
      *Valores intermediários são modificados de acordo com o valor de m definido acima.
      *O valor de m é calculado desta forma: Se |p - v| <= T, v receberá o valor de p
   *Se T>=255:
      *todos os valores da matriz sera igual ao valor do elemento matriz[x][y]
   */
  if(T>0 && T<255){
    int p = matriz[x][y];
    i =0;
    movimentos(x, y, N, T, p, matriz, a, b, i);
  }

  if(T>=255){
    igualar(x, y, N, matriz);
  }
  
  /*imprimir a matriz modificada*/
  imprimir_matriz(matriz, N);

  /*criar um arquivo PGM com os valores da matriz modificada**/
  imagem_modificada = fopen("imagem_modificada.pgm", "wb"); 
  imagem(imagem_modificada, N, N, matriz);
  fclose(imagem_modificada); 
    
  
  free(matriz);
  free(a);
  free(b);
  return 0;
}