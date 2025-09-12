#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Cabecalho das funcoes auxiliares*/
void le_vetor(struct racional **vetor_ptr, int n);
void imprime_vetor(int tam, struct racional **v);
void ordena(struct racional **v, int tam);
void remove_invalidos(struct racional **vetor_ptr, int *n);
void calcula_soma(struct racional *soma, struct racional **vetor_ptr, int n); 

/* programa principal */
int main (){  
   int n;
   struct racional *soma = cria_r(0, 1);
   
   // Le a quantidade de racionais 
   scanf("%d", &n);
   
   // Testa se n satisfaz 0 < n < 100
   if (!(0 < n && n < 100)) 
      return 1;
   
   // Aloca dinamicamente um ponteiro de ponteiros que apontam para racionais
   struct racional **vetor_ptr = malloc(n * sizeof(struct racional *));

   // Preenche o vetor
   le_vetor(vetor_ptr, n);
   
   // Imprime vetor completo
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Remove racionais invalidos
   remove_invalidos(vetor_ptr, &n);
   
   // Imprime vetor sem invalidos
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Ordena vetor em ordem crescente
   ordena(vetor_ptr, n);

   // Imprime vetor ordenado
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);

   // Calcula Soma
   calcula_soma(soma, vetor_ptr, n);

   // Imprime soma
   printf("SOMA = ");
   imprime_r(soma);
   printf("\n");

   // Libera racionais apontados pelo vetor
   for(int i = 0; i < n; i++){
      free(vetor_ptr[i]);
      vetor_ptr[i] = NULL;
   }

   // Imprime vetor liberado
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Libera o vetor de ponteiros
   free(vetor_ptr);
   vetor_ptr = NULL;

   // Libera espaco da soma
   free(soma);
   soma = NULL;

   return 0;
}

/* Funcoes Auxiliares */
/* Imprime os racionais apontados pelo vetor */
void imprime_vetor(int tam, struct racional **v){
   /* Percorre o vetor de ponteiros e imprime 
   o racional apontado por cada um */
   for(int i = 0; i < tam - 1; i++){
      imprime_r(v[i]);
      printf(" ");
   }
   
   /*Imprime o ultimo elemento separado se o tamanho 
   for maior que 0 para evitar um espaco extra no fim*/
   if (tam > 0)
      imprime_r(v[tam-1]);
   printf("\n");
}

/* Remove os racionais invalidos */
void remove_invalidos(struct racional **vetor_ptr, int *n){
   int j = 0; 
   
   // Copia os valores validos para o inicio do vetor
   for (int i = 0; i < *n; i++)
         if (valido_r(vetor_ptr[i]))
            vetor_ptr[j++] = vetor_ptr[i];

   // Libera racionais invalidos
   for (int i = j; i < *n; i++)
      if (!valido_r(vetor_ptr[i]))
         destroi_r(&vetor_ptr[i]);

   // Corrige o tamanho do vetor
   *n = j;
}

/* Ordena o vetor usando Select Sort */
void ordena(struct racional **v, int tam){
   
   // Percorre o vetor encontrando o menor valor
   for (int i = 0; i < tam; i++){
      struct racional *p_aux = NULL; // Ponteiro auxiliar
      int menor = i;

      // Encontra menor valor apontado pelos ponteiros no vetor
      for ( int j = i + 1; j < tam; j++)
         if (compara_r(v[menor], v[j]) == 1)
            menor = j;

      // Substitui o local apontado pelos ponteiros
      p_aux = v[i];
      v[i] = v[menor];
      v[menor] = p_aux;
   }
}

/* Calcula soma de todos os elementos do vetor */
void calcula_soma(struct racional *soma, struct racional **vetor_ptr, int n){
 // Percorre o vetor e realiza a soma
 for (int i = 0; i < n; i++)
    soma_r(soma, vetor_ptr[i], soma);
}

/* Le vetor de ponteiros de racionais */
void le_vetor(struct racional **vetor_ptr, int n){
   long num, den;
   // Preenche o vetor
   for (int i = 0; i < n; i++){
      scanf("%ld %ld", &num, &den);
      vetor_ptr[i] = cria_r(num, den);
   }
}

