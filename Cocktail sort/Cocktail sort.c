#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*deletar os nomes das cidades*/
void nome_extraido(char *nome){
  int tam=strlen(nome);
  int i=0;
  
  for(i=tam;i>=0;i--){
    /*para deletar o .*/
    if(nome[i]=='.'){
      nome[i+1]='\0';
    }
  }
}

/*deixar minusculos todos os caracteres de uma frase*/
void transformar_minusculo(char *nome){
  for(int i = 0; i<strlen(nome); i++){
    nome[i]=tolower(nome[i]);
  }
}

/*funcao para colocar em ordem alfabetica*/
void cocktail_sort(char **lista, int qtd_pessoas){
	int ready, l=0, j=0;
	char aux[200], copia1[200], copia2[200];

	do{
		ready = 0;
    /*ordenar buscando do fim para o inicio da lista*/
    for (j = qtd_pessoas-1; j >=0; j--) { 
      for (l = j-1; l >= 0; l--) {
        /*criar uma copia dos nomes e deixar com todos os caracteres minusculos*/
        strcpy(copia1, lista[l]);
        transformar_minusculo(copia1);
        strcpy(copia2, lista[j]);
        transformar_minusculo(copia2);

        /*comparar as duas copias para ordenar alfabeticamente os nomes*/
        if (strcmp(copia1, copia2)>0) {
          strcpy(aux, lista[l]);
          strcpy(lista[l], lista[j]);
          strcpy(lista[j], aux);
          ready = 1;
        }
      }
    }
    /*ordenar buscando do inicio para o fim da lista*/
		for (j = 0; j < qtd_pessoas; j++) { 
      for (l = j+1; l < qtd_pessoas; l++) {
        /*criar uma copia dos nomes e deixar com todos os caracteres minusculos*/
        strcpy(copia1, lista[l]);
        transformar_minusculo(copia1);
        strcpy(copia2, lista[j]);
        transformar_minusculo(copia2);

        /*comparar as duas copias para ordenar alfabeticamente os nomes*/
        if (strcmp(copia2, copia1)>0) {
          strcpy(aux, lista[j]);
          strcpy(lista[j], lista[l]);
          strcpy(lista[l], aux);
          ready = 1;
        }
      }
    }
	} while(ready);
}

/*funcao para verificar se a pessoa buscada eh de Sao Carlos
Se for de Sao Carlos o resultado vai ser 1
Se nao for de Sao Carlos o resultado vai ser zero*/
void verificar_cidade(char *pessoa, int *cidade_busca){
  char *cidade;	
  cidade = strstr(pessoa, "Sao Carlos");	
  if (cidade != NULL) {
    *cidade_busca = 1;
  }else{
   *cidade_busca = 0;
  }
}

int main() {
  int qtd_pessoas = 0, i = 0, qtd_busca = 0, *cidades;
  char **nomes, **busca_nomes;

  /*determinar a quantidade de nomes inseridos*/
  scanf("%d", &qtd_pessoas);

  /*alocar memoria da lista principal*/
  nomes=(char**)malloc(qtd_pessoas*sizeof(char*));
  for(i=0; i<qtd_pessoas; i++){
    nomes[i]=(char*)malloc(100*sizeof(char));
  }
  if(nomes==NULL){
    return 0;
  }

  /*inserir os nomes*/
  for(i=0; i<qtd_pessoas; i++){
    scanf(" %[^\n]s", nomes[i]);
  }

  /*determinar a quantidades de busca realizada*/
  scanf("%d", &qtd_busca);

  /*alocar memoria para a lista de nomes a ser buscado*/
  busca_nomes=(char**)malloc(qtd_busca*sizeof(char*));
  for(i=0; i<qtd_busca; i++){
    busca_nomes[i]=(char*)malloc(100*sizeof(char));
  }
  if(busca_nomes==NULL){
    return 0;
  }

  /*inserir os nomes que deseja buscar*/
  for(i=0; i<qtd_busca; i++){
    scanf(" %[^\n]s", busca_nomes[i]);
  }

  /*buscar uma pessoa e verificar sua cidade*/
  cidades=(int*)malloc(qtd_busca*sizeof(int));
  for(int i = 0; i<qtd_busca; i++){
    for(int j = 0; j<qtd_pessoas; j++){
      /*se a pessoa buscada estiver na lista*/
      if(strncmp(nomes[j], busca_nomes[i], strlen(busca_nomes[i])-1)==0){
        /*verificar a cidade onde mora a pessoa buscada*/
        verificar_cidade(nomes[j], &cidades[i]);
      }
    }
  }

  /*colocar em ordem alfabetica*/
  cocktail_sort(nomes, qtd_pessoas);

  /*imprimir em ordem alfabetica*/
  for(i=0; i<qtd_pessoas; i++){
    nome_extraido(nomes[i]);
    printf("%s\n", nomes[i]);
  }

  for(i=0; i<qtd_busca; i++){
    printf("%d\n", cidades[i]);
  }


  free(nomes);
  free(busca_nomes);
  return 0;
}
