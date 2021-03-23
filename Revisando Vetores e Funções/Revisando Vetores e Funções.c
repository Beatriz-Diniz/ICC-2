#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

/*funcao readline*/
char *readline(FILE *stream){
  char *string = NULL;
  int pos = 0; 
  int qt_n = 0;   
  do {
    string = (char *) realloc(string, pos+500);
    string[pos] = (char) fgetc(stdin);
    if(string[pos] == ' '){
      qt_n++;
    }
  /*qnt_n<100 para limitar a quantidade de valores inseridos ate 100*/
  }while (string[pos++] != '\n' && !feof(stdin) && qt_n <100);
  string[pos-1] = '\0';
  return string;
}

int main() {
  
  int qnt_numeros=0, i=0, j=0, contador = 0, *number, aux2=0, rep=0;
  char *numeros = readline(stdin);
  
  /*alocar memoria*/
  char **aux1 = malloc(1000*sizeof(char));
  for(i=0; i<100; i++){
    aux1[i]=malloc(1000*sizeof(char));
  }
  
  /*variavel para determinar onde deve ocorrer a quebra da string*/
  const char quebra[2] = " ";

  /*variavel que vai receber a string repartida em varias e subtring*/             
  char *texto_quebrado;
   
  /*para ocorer a quebra da string*/
  texto_quebrado = strtok(numeros, quebra);
  
  i = 0;
  while( texto_quebrado != NULL ) {

    /*para copiar os valores inseridos para uma variavel auxiliar*/
    strcpy(aux1[i], texto_quebrado);

    /*para reposisionar a quebra da string*/
    texto_quebrado = strtok(NULL, quebra);
    qnt_numeros += 1;
    i++;
  }

  /*alocar memoria*/
  number = (int*)malloc(qnt_numeros*sizeof(int));

  for(i=0; i<qnt_numeros; i++){
    /*a funcao atoi transfere o numeros dentro da string para um int*/
    number[i] = atoi(aux1[i]);
  }

  /*loop para encontra as repeticoes*/
  for(i=0; i<qnt_numeros; i++){
    rep = 0;
    /*para verificar se o primeiro numero tem repeticoes*/
    if(contador == 0){
      for(j=0; j<qnt_numeros; j++){
        if(number[i]==number[j]){
          rep++;
        }
      }
      /*para imprimir o primeiro numero e sua quantidade de repeticoes*/
      printf("%d (%d)\n", number[i], rep);
    }
    /*para verificar as repeticoes dos demais numeros*/
    if(contador>0){
      /*para verificar se o atual numero ja apareceu anteriormente*/
      for(int k = contador-1; k>=0; k--){
        if(number[i]==number[k]){
          aux2 = 1;
        }
      }
      /*se o numero nao tiver aparecido anteriormente*/
      if(aux2 == 0){
        /*verificar quantas repeticoes o numero teve*/
        for(j=0; j<qnt_numeros; j++){
        if(number[i]==number[j]){
          rep++;
        }
      }
      printf("%d (%d)\n", number[i], rep);
      }
    }
    contador++;
    aux2 = 0;
  }

  free(numeros);
  free(number);
  return 0;
}