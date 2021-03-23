#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "spotify.h"

struct dados{
  char *artist_name, *track_name, *track_id;
  double acousticness, danceability, energy, instrumentalness,liveness, loudness, speechiness, tempo, time_signature, dissimilaridade;
};


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
int comparar_string (const void *a, const void *b){
  return strcmp (((struct dados *)a)->track_id,((struct dados *)b)->track_id);
}

/*funcao para imprimir os dados desejados*/
void print_most_similar_tracks(dados *d, char *tracks, int K){
  printf("----As %d musicas mais parecidas com %s sao:\n", K, tracks);
  for (int i=0; i<K; i++){
    printf("\t(%d)Artista: %s\n", i, d[i].artist_name);
    printf("\t\tMusica: %s\n", d[i].track_name);
    printf("\t\tDissimilaridade: %lf\n", d[i].dissimilaridade);
    printf("\t\tLink: https://open.spotify.com/track/%s\n", d[i].track_id);
  }
  printf("\n");
}

void ler_csv(dados *d, int *total_musicas){
   char line[16352], *aux;
   FILE *fp;
   int i = 0, j = 0;
  
  ler_arquivo(&fp);
    
  /*Extrair as informacaoes do arquivo*/
  while(fgets(line, 16352, fp)){
    char *token;
    /*para quebrar uma linha quando encontar o ';'*/
    token = strtok(line, ";");
    i = 0;
    
    /*Para deixar vazio */
    if(line[0] == ';')
      i=1;
    

    while(token!=NULL){
      aux = (char*)calloc(200, sizeof(char));
      
      /*guardar as musicas*/
      if(i==0){
        strcpy(aux, token);
        d[j].track_name = aux;
      }

      /*guardar as ids*/
      if(i==1){
        strcpy(aux, token);
        /*para retirar o ' ' no inicio da id*/
        for(int k = 0; k<200; k++)
          aux[k] = aux[k+1];
        
        d[j].track_id = aux;
      }

      /*guardar os artistas*/
      if(i==4){
        strcpy(aux, token);
        /*para retirar o ' ' no inicio dos nomes dos artistas*/
        for(int k = 0; k<200; k++)
          aux[k] = aux[k+1];
        
        d[j].artist_name = aux;
      }

      /*salvar o valor de acousticness*/
      if(i==9)
        d[j].acousticness = atof(token);
      
      /*salvar o valor de danceability*/
      if(i==10)
        d[j].danceability = atof(token);

      /*salvar o valor de energy*/
      if(i==11)
        d[j].energy = atof(token);

      /*salvar o valor de instrumentalness*/
      if(i==12)
        d[j].instrumentalness = atof(token);
      
      /*salvar o valor de liveness*/
      if(i==13)
        d[j].liveness = atof(token);

      /*salvar o valor de loudness*/
      if(i==14)
        d[j].loudness = atof(token);
      
      /*salvar o valor de speechiness*/
      if(i==15)
        d[j].speechiness = atof(token);
      
      /*salvar o valor de tempo*/
      if(i==16)
        d[j].tempo = atof(token);
      
      /*salvar o valor de time_signature*/
      if(i==17)
        d[j].time_signature = atof(token);

      /*Zerar o token*/
      token = strtok(NULL, ";");
      i++;
    }
    j++;
  }

  /*Encontrar a quantidade total de musicas*/
  *total_musicas = j;
  free(aux);
  fclose(fp);
}

/* Algoritmo countingsort com registros*/
void countingsort_rec(dados *d, int total_musicas){
  int c[256] = {0};
  int pos[256];

  /*alocar memoria para uma struct copia*/
  struct dados *copy = calloc(total_musicas, sizeof(dados));

  /*para copiar os dados da struct original para a struct copia e realizar a contagem*/
  for(int shift = 0; shift <=8 *(sizeof(double)-1); shift +=8){
    for(int i = 0; i < total_musicas; i++){
      /*deslocar e extrair um bloco de 8 bits*/
      short k =((int)round(d[i].dissimilaridade * 1000000) >> shift) & 255;
      c[k]++;
      copy[i] = d[i];
    }

    /*contagem acumulada*/
    pos[0] = 0;
    for(int i = 1; i<256; i++){
      pos[i] = pos[i-1] + c[i-1];
      /*zerar a contagem*/
      c[i-1] = 0;
    }

    /*copia os elementos para a posicao correta*/
    for(int i =0; i<total_musicas; i++){
      short k =((int)round(copy[i].dissimilaridade * 1000000) >> shift) & 255;
      /*ordena na posicao de k*/
      d[pos[k]] = copy[i];
      pos[k]++;
    }
  }
  free(copy);
}

/*função que vai realizar a busca binaria*/
void busca_binaria(dados *d, int total_musicas, char *busca, int *r){  
  int inicio = 0;
  int fim = total_musicas;
  int meio;
  int controle_pesquisa = 1;
  qsort(d, total_musicas, sizeof(dados), comparar_string);

  // Loop que ira realizar a pesquisa binaria 
  while (inicio <= fim){                    
  // Obtem o valor do meio do vetor 
    meio = (inicio + fim) / 2;              
    
    // Verifica se o valor foi encontrado
      if (strcmp(busca, d[meio].track_id) == 0){   
        controle_pesquisa = 0;
        break;
      }       
      
      //Se a pesquisa for menor que o meio do vetor, entao o fim do vetor sera o meio atual -1       
      else if (strcmp(busca, d[meio].track_id)<0){ 
        fim = meio - 1;
        continue;
      }
      
      //Se a pesquisa for maior que o meio do vetor, entao a pesquisa comecara        
      else if(strcmp(busca, d[meio].track_id)>0){  
        //a partir do meio atual atual do vetor
        inicio = meio + 1;                    
        continue;
      }
      
      //Se o valor não for encontrado define o controle_pesquisa = 1
      else{ 
        controle_pesquisa = 1;
        break;
      }  
    }
    
    //Se a variavel controle_pesquisa for igual a 0, entao o elemento foi encontrado    
    if (controle_pesquisa == 0){   
      /*para salvar a posicao onde foi encontrdo*/
      *r = meio;
    } else {
      printf("Chave inexistente\n");
    }
}

void dissimilaridade(dados *d, int q, int k, int total_musicas){
  int i = 0, j = 0;
  char *busca;
  for(i=0; i<q; i++){
    int r =0;
    busca = (char*)calloc(100, sizeof(char));
    scanf("%s",busca);
    
    
    /*buscar o id desejado e salvar a sua posicao*/
    busca_binaria(d, total_musicas, busca, &r);
    
    /*salvar os atributos da musica buscada pelo id*/
    double d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0, d8 = 0, d9 = 0;
    d1 = d[r].acousticness;
    d2 = d[r].danceability;
    d3 = d[r].energy;
    d4 = d[r].instrumentalness;
    d5 = d[r].liveness;
    d6 = d[r].loudness;
    d7 = d[r].speechiness;
    d8 = d[r].tempo;
    d9 = d[r].time_signature;
      
    /*realizar uma copia da musica buscada*/
    char *copia;
    copia = (char*)calloc(100, sizeof(char));
    strcpy(copia, d[r].track_name);

    /*calcular a distancia euclidiana entre a musica buscada e todas as musicas do arquivo*/
    for(j = 0; j<total_musicas; j++){
      double soma = 0;
        
      /*elevar ao quadrado a subtracao entre os atributos de duas musicas e somar os resultados*/
      soma = pow((d[j].acousticness-d1), 2) + pow((d[j].danceability-d2),2) + pow((d[j].energy-d3),2) + pow((d[j].instrumentalness-d4),2) + pow((d[j].liveness-d5),2) + pow((d[j].loudness-d6),2) + pow((d[j].speechiness-d7),2) + pow((d[j].tempo-d8),2) + pow((d[j].time_signature-d9),2);

      /*calcular a raiz quadrada da soma*/
      d[j].dissimilaridade = sqrt(soma);  
    }
    
    /*adicionar um valor alto para a dissimilaridade do cabecalho do arquivo para ser ignorado*/
    d[total_musicas-1].dissimilaridade = 10000;

    /*ordenar as musicacom base na dissimilaridade*/
    countingsort_rec(d, total_musicas);
    
    /*imprimir os dados desejados*/
    print_most_similar_tracks(d, copia,k);
  }
}