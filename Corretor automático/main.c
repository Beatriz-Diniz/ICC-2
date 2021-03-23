#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"
#include <ctype.h>

int main() {
  skiplist *sk = criar(20, 0.5);
  char *line;
  int i = 0, j = 0, k = 0, l = 0, erro = 0;
  FILE *fp;
  ler_arquivo(&fp);

  /*alocar memoria*/
  line = (char*)malloc(500*sizeof(char));

  /*Extrair as informacaoes do arquivo*/
  while(fgets(line, 500, fp)){
    char *token;
    
    /*separar as palvras do texto*/
    token = strtok(line, " ");
    while(token!=NULL){
      char aux[200] = {'\0'};

      /*copiar o conteudo do token para uma variavel auxiliar*/
      strcpy(aux, token);
      for(j = 0; j<strlen(aux); j++)
        aux[j] = tolower(aux[j]);
      if(i==0)
        inserir(sk, aux);

      /*retirar o ultimo "'" de uma palvra entre ' '*/
      if(aux[strlen(aux)-1] == 39)
        aux[strlen(aux)-1] = '\0';

      /*retirar os caracteres especias do inicio da palavra*/
      if((aux[0] == '(' && aux[1]!='c') || aux[0] == '"' || aux[0] == 39 || aux[0]=='['){
        for(j = 0; j<strlen(aux); j++){
          aux[j] = aux[j+1]; 
        }
      }
      
      /*para retirar o "--" do inicio de uma palavra*/
      if(aux[0]=='-'){
        for(j = 0; j<strlen(aux); j++){
          aux[j] = aux[j+2];
        }
      }
      
      /*para retirar os caracteres especiais do fim*/
      for(j = 0; j<strlen(token); j++){
        if(aux[j] == '?' || aux[j] == '!'  || (aux[j] == ')' && aux[j-1] !='c' && aux[j-2]!='(' ) || aux[j] == '"'  || aux[j] == '\n'){
          aux[j] = '\0';
        }

        if(aux[j] == '.' || aux[j] == ',' || aux[j] == ':'  || aux[j+1] =='\n'|| aux[j] == ';' || (aux[j]=='-' && aux[j+1]=='-')){
          if(aux[j+2] != '.')
            aux[j] = '\0';

          break;
        }
      }

      j = 0;
      /*para verificar se esxistem palavras separadas por um "-" e quebra-las*/
      for(k=0; k<strlen(aux); k++){
        if(aux[k]=='-' || aux[k]==39){
          int m = 0, n = 0, a = 0, b = 0;
          j = 1;
          char aux1[50] = {'\0'}, aux2[50] = {'\0'};
          char aux3[50] = {'\0'}, aux4[50] = {'\0'};
            
          /*para inserir a primeira palavra*/
          for(m = 0; m<k; m++)
            aux1[m] = aux[m];
          inserir(sk,  aux1);

          /*salvar a segunda palavra numa variavel*/
          for(m = m+1; m<strlen(aux); m++){
            aux2[n] = aux[m];
            n++;
          }

          /*verificar se a segunda palavra tambem contem outra palavra separada por "-"*/
          if(aux2[1]=='-'){
            a = 1;

            /*inserir a segunda palavra*/
            aux3[0] = aux2[0];
            inserir(sk, aux3);
            m = 0;

            /*salvar e inserir a terceira palavra*/
            for(b = 2; b<strlen(aux2); b++){
              aux4[m] = aux2[b];
              m++;
            }
            inserir(sk, aux4);
          }

          /*salvar a segunda palavra se ela nao tiver outras com ela*/
          if(a==0)
            inserir(sk, aux2);
          break;
        }
      }

      /*inserir a palavra se ela estiver sozinha*/
      if(j==0)
        inserir(sk, aux);
    
      /*zerar o token*/
      token = strtok(NULL, " ");

      
    }
    i++;
  }
  free(line);
  fclose(fp);

  ler_arquivo(&fp);
  i = 0;
  char line2[1000];
  
  /*Extrair as informacaoes do arquivo*/
  while(fgets(line2, 500, fp) != NULL){
    char *aux = (char*)calloc(800, sizeof(char*));
    char *aux2 = (char*)calloc(800, sizeof(char*));
    char *token;

    /*salvar as informacoes em uma variavel auxiiar*/
    strcpy(aux, line2);
    k = 0;

    /*retirar os espacos vazios na frente do conteudo*/
    for(j = 0; j<=strlen(aux); j++){
      while(aux[j]==' ' && k ==0){
        j++;
      }
      aux2[k] = aux[j+1];
      k++;
    }

    /*verificar se o conteudo eh um texto*/
    if(strncmp(aux2, "text:", 4)==0){
      /*variavel que indica se encontrou um conteudo tipo text no arquivo tweet*/
      erro = 1;
      token = strtok(aux2, " ");

      while(token!=NULL){

        /*copiar a palavra atual para uma variavel auxiliar*/
        strcpy(aux, token);
      
        int tam = 0;
        tam = strlen(aux);
        token = strtok(NULL, " ");

        /*eliminar os caracteres ", # & @ do inicio da palavra*/
        if(aux[0]=='"' || aux[0]=='#' || aux[0]=='@')
          for(j = 0; j<strlen(aux); j++)
            aux[j] = aux[j+1];

        /*eliminar os caracteres que nao estao na tabela ascii*/
        if(aux[0]<0 || aux[0]>122)
          for(j = 0; j<strlen(aux); j++)
            aux[j] = aux[j+3];

        /*se a palavra for T.V., eliminar o T.*/
        if(aux[0]=='T' && aux[1]=='.')
          for(j = 0; j<strlen(aux); j++)
            aux[j] = aux[j+2];

      
        /*eliminar os numeros do inicio da palavra*/
        if(aux[0]>47 && aux[0]<58){
          int m = 0;
          while(aux[m]>47 && aux[m]<58)
            m++;
          for(j = 0; j<strlen(aux); j++)
            aux[j] = aux[j+m];
          }
      
        /*salvar a ultima palavra da linha numa variavel auxiliar*/
        char aux3[50] ={'\0'};
        if(aux[tam-3] == '"'){
          strcpy(aux3, aux);
        } 

        /*eliminar os caracteres especias do fim da palavra*/
        for(i=0; i<strlen(aux); i++)
          if((aux[i] < 65 && aux[i]!=45) || (aux[i] > 90 && aux[i] < 97) || aux[i] > 122)
            aux[i]='\0';
     
        /*verificar se a palavra existe no texto, ignorando a palavra text:*/
        if(strncmp(aux, "text:", 4)!=0 && aux[0]!='-' && aux[0]>57){
          k = 0;
          for(j = 0; j<strlen(aux); j++){
            i = 0;

            /*verificar se a palavra buscada tem duas palavras separadas por '-'*/
            if(aux[j]=='-'){
              k =2;
              char aux5[25] = {'\0'};
              
              /*buscar a primeira palavra*/
              while(i<j){
                aux5[i] = aux[i];
                i++;
              }
              busca(sk, aux5);
              
              j++;
              char aux4[25] ={'\0'};
              i = 0;

              /*buscar a segunda palavra*/
              while(j<strlen(aux)){
                aux4[i] = aux[j];
                i++;
                j++;
              }
              busca(sk, aux4);
            }
          }

          /*realizar a busca se a palavra estiver sozinha*/
          if(k==0)
            busca(sk, aux);
        }
      }
      printf("\n");
    }
  }
  
  /*se o arquivo tweet nao tiver nenhum conteudo tipo text*/
  if(erro == 0)
    printf("No tweets to check\n");

  fclose(fp);
  return 0;
} 