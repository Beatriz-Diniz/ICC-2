#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "spotify.h"

int main() {
  int total_musicas = 0, q = 0, k = 0;
  dados *d;
  
  d = (dados*)malloc(16352*sizeof(dados*));
  /*ler o arquivo csv*/
  ler_csv(d, &total_musicas);
  
  /*q = quantidade de ids que serao buscadas
   *k = quantidade de musicas similares que deverao ser imprimidas
  */
  scanf("%d",&q);
  scanf("%d",&k);

  /*calcular a dissimilaridade*/
  dissimilaridade(d, q, k, total_musicas);

  
  /*liberar memoria*/
  free(d);
  return 0;
}