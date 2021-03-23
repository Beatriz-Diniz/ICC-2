#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct dados{
  char *artist_name, *artist_id;
  int popularity, music;
  float popularity_2;
  char *artist, *id;

}dados[16352];

/*funcao para ler o arquivo*/
void ler_arquivo(FILE **fp){
  char arquivo[30];
  /*escolher o arquivo para abrir*/
  scanf("%s", arquivo);
  
  /*abrir arquivo*/
  *fp=fopen(arquivo, "r");
  if(*fp==NULL){
    printf("Nao foi possivel abrir o arquivo\n");
  }
}

/*funcao qsort*/
int comparar_string (const void *a, const void *b) {
    return strcmp (((struct dados *)a)->artist_name,((struct dados *)b)->artist_name);
}

/*funcao qsort*/
int comparar_float (const void *a, const void *b) {
    /*retornar 0 quando as palavras forem iguais*/ 
    if((*(struct dados *)a).popularity_2 == (*(struct dados *)b).popularity_2){
      return 0;
    }
    /*retornar -1 quando a a primeira palvra for menor que a segunda palavra*/
    else if((*(struct dados *)a).popularity_2 < (*(struct dados *)b).popularity_2){
      return -1;
      /*retornar 1 quando a segunda palavra for maior que a primeira*/
    }else{
      return 1;
    }
}

int main(void) {
  int i = 0, j = 0, total_musicas = 0, total_artistas = 0;
  FILE *fp;

  struct dados *d;
  d = ( struct dados *)malloc(16352*sizeof( struct dados));
  assert(d!=NULL);

  ler_arquivo(&fp);

  char line[16352], aux[16352][200], aux2[16352][200], **artists;

  /*Extrair as informacaoes do arquivo*/
  while(fgets(line, 16352, fp)){
    char *token;

    /*para quebrar uma linha quando encontar o ';'*/
    token = strtok(line, ";");
    i = 0;
    
    /*Para deixar vazio */
    if(line[0] == ';'){
      i=1;
    }

    while(token!=NULL){

      /*guardar os artistas*/
      if(i==4){
        strcpy(aux[j], token);
        /*para retirar o ' ' no inicio dos nomes dos artistas*/
        for(int k = 0; k<200; k++){
          aux[j][k] = aux[j][k+1];
        }
        d[j].artist_name = aux[j];
      }

      /*guardar as ids*/
      if(i==5){
        strcpy(aux2[j], token);
        /*para retirar o ' ' no inicio da id*/
        for(int k = 0; k<200; k++){
          aux2[j][k] = aux2[j][k+1];
        }
        d[j].artist_id = aux2[j];
      }

      /*guardar a popularidade de cada musica*/
      if(i==8){
        d[j].popularity = atoi(token);
      }

      /*Zerar o token*/
      token = strtok(NULL, ";");
      i++;
    }
    j++;
  }

  /*Encontrar a quantidade total de musicas*/
  total_musicas = j-1;
  fclose(fp);

  /*Ordenar em ordem alfabetica de artistas*/
  qsort(d, total_musicas, sizeof(struct dados), comparar_string);
  
  /*Alocar memoria*/
  artists = (char**)malloc(100*sizeof(char*));
  for(i = 0; i<= 100; i++){
    artists[i] = (char*)malloc(200*sizeof(char));
  }
  
  /*Encontar a quantidade de artistas e salvar numa variavel*/
  for(i=0; i<total_musicas-1; i++){
    if(strcmp(d[i].artist_name, d[i+1].artist_name)!=0 && j>0){
      artists[total_artistas] = d[i].artist_name;
      d[total_artistas].artist = artists[total_artistas];
      d[total_artistas].id = d[i].artist_id;
      total_artistas++;
    }    
  }

  /*encontar a quantidade de musica e popularidade de cada artista*/
  for(i = 0; i<=total_artistas; i++){
    for(j = 0; j<=total_musicas; j++){
      if(strcmp(artists[i], d[j].artist_name)==0){
        d[i].music++;
        d[i].popularity_2 += d[j].popularity;
      }
    }
    d[i].popularity_2 = (d[i].popularity_2/d[i].music);
  }

  /*ordenar em ordem de popularidade*/
  qsort(d, total_artistas, sizeof(struct dados), comparar_float);

  j = 1;
  printf("O Dataset contem %d Artistas e %d Musicas\n", total_artistas, total_musicas);
  printf("Os artistas mais populares sao:\n");
  for(i = total_artistas-1; i>=0; i--){
    printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n", j, d[i].artist, d[i].music, d[i].popularity_2, d[i].id);
    j++;
  }
  
  /*liberar memoria*/
  free(d);
  free(artists);
  return 0;
}
