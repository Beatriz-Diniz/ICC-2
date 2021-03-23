#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*funcao para copiar os valores dos livros para um vetor de floats*/
void extrair_valores(char *livro, float *valores){
  int tam = strlen(livro);
  char aux[200];
  int j = 0;
  for(int i = 0; i<tam; i++){
    if(livro[i]==','){
      j = i+2;
      int k = 0;
      while(livro[j]!='\0'){
        aux[k]=livro[j];
        k++;
        j++;
      }
      livro[i]='\0';
    }
  }
  *valores=atof(aux); 
}

/*funcao que ordena os valores*/
void merge(float valores[], int meio, int fim){
    if (fim < 2)
        return;

    int i=0, j=meio, k=0;
    float aux[fim];
    while (i < meio && j < fim)
        aux[k++] = (valores[i] < valores[j]) ? valores[i++] : valores[j++];

    memcpy(aux+k, valores+i, (meio-i) * sizeof *valores);
    memcpy(valores, aux, (k + (meio-i)) * sizeof *valores);
}

/*funcao para chamar a ordenacao se forem inseridos ate 3 valores*/
void mersort(float valores[], int fim){
  if (fim < 2)
    return;

  int meio = fim/2;
  mersort(valores, meio);
  mersort(valores+meio, fim-meio);
  merge(valores, meio, fim);
}

/*funcao que divide os valores inseridos em 3 partes*/
void mersort3(float valores[], int fim){

  
  for(int i = 0; i<fim; i++){
    printf("%.2f ", valores[i]);
  }
  printf("\n");
  
  if(fim==2){
    for(int i = 0; i<fim; i++){
      printf("%.2f\n", valores[i]);
    }
  }
  if (fim < 3){
    mersort(valores, fim);
    return;
  }
  
    int j;
    if(fim%3==0){
      j = 0;
    }else{
      j = 1;
    }
    int m1 = (fim/3)+j;
    int m2 = ((2 * fim)/3)+j;
    mersort3(valores, m1);        //parte 1 da divisao do vetor
    mersort3(valores+m1, m2-m1);  //parte 2 da divisao do vetor
    mersort3(valores+m2, fim-m2); //parte 3 da divisao do vetor  
    merge(valores, m1, m2);   //chamar a primeira ordencao
    merge(valores, m2, fim);  //chamr aa segunda ordenacao
}

int main(){
  char **livros, **copia_valores, **copia_livros;
  float *valores;
  int fim = 0, qtd_entradas, i;

  scanf("%d", &qtd_entradas);
  fim = qtd_entradas;

  /*alocar todas as memorias necessarias*/
  livros = (char**)malloc(qtd_entradas*sizeof(char*));
  copia_valores = (char**)malloc(qtd_entradas*sizeof(char*));
  copia_livros = (char**)malloc(qtd_entradas*sizeof(char*));
  
  for(i= 0; i<qtd_entradas; i++){
    livros[i]=(char*)malloc(100*sizeof(char));
    copia_livros[i]=(char*)malloc(100*sizeof(char));
    copia_valores[i]=(char*)malloc(qtd_entradas*sizeof(char));
  }
  valores = (float*)malloc((qtd_entradas)*sizeof(float));
  

  /*inserir os livros e separar seus valores*/
  for(i = 0; i <qtd_entradas; i++){
    scanf(" %[^\n]s",livros[i]);
    strcpy(copia_livros[i], livros[i]);
    extrair_valores(livros[i],&valores[i]);
  }

  /*ordenar os valores*/
  mersort3(valores, fim);
  printf("\n");
  
  /*criar uma copia dos valores numa string*/
  for(i=0; i<qtd_entradas; i++){
    sprintf (copia_valores[i], "%.2f", valores[i]); 
  }

  /*imprimir os nomes dos livros e seus valores em ordem crescente de valores*/
  for(i=0; i<qtd_entradas; i++){
    for(int j = 0 ; j<qtd_entradas; j++){
      char *res;
      char aux[200];
      float aux2;	
      res = strstr(copia_livros[j], copia_valores[i]);

      /*a variavel aux vai receber uma copia do livro
      vai ser extraido o valor do livro que está na variavel auxiliar
      e armazenado na variavel aux2 para ser usado na comparacao*/	
      strcpy(aux, copia_livros[j]);
      extrair_valores(aux, &aux2);
      if(res!=NULL && aux2==valores[i]){
	      printf("%s, R$%.2f\n", livros[j], valores[i]);
      }
    }
  }


  free(livros);
  free(valores);
  free(copia_livros);
  free(copia_valores);
  return 0;
}

