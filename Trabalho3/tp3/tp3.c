#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Cabecalho das funcoes auxiliares */
void le_vetor(struct racional **vetor_ptr, int n);
void imprime_vetor(int tam, struct racional **v);
void ordena(struct racional **v, int tam);
void remove_invalidos(struct racional **vetor_ptr, int *n);
void calcula_soma(struct racional *soma, struct racional **vetor_ptr, int n); 

/* programa principal */
int main (){  
   int n;
   
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
   struct racional *soma = cria_r(0, 1);
   calcula_soma(soma, vetor_ptr, n);

   // Imprime soma
   printf("SOMA = ");
   imprime_r(soma);
   printf("\n");

   // Libera racionais apontados pelo vetor
   for(int i = 0; i < n; i++)
      destroi_r(&vetor_ptr[i]);

   // Imprime vetor liberado
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Libera o vetor de ponteiros
   free(vetor_ptr);
   vetor_ptr = NULL;

   // Libera espaco da soma
   destroi_r(&soma);

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
   
   /* Imprime o ultimo elemento separado se o tamanho 
   for maior que 0 para evitar um espaco extra no fim */
   if (tam > 0)
      imprime_r(v[tam-1]);
   printf("\n");
}

/* Remove os racionais invalidos */
void remove_invalidos(struct racional **vetor_ptr, int *n){
   int i = 0;
   int fim = *n - 1;
   
   while (i <= fim) {
      if (valido_r(vetor_ptr[i])) 
         i++;
      else {
         destroi_r(&vetor_ptr[i]);
         // Troca pelo racional do final
         if (i != fim) 
            vetor_ptr[i] = vetor_ptr[fim];
         // Libera o ponteiro do fim
         vetor_ptr[fim] = NULL;
         fim--;
      }
   }

   // Atualiza o número de elementos válidos
   *n = i;
}

/* Ordena o vetor usando Select Sort */
void ordena(struct racional **v, int tam){
   
   // Ponteiro racional auxiliar
   struct racional *aux = NULL;
   
   // Percorre o vetor encontrando o menor valor
   for (int i = 0; i < tam; i++){
      int menor = i;

      // Encontra menor valor apontado pelos ponteiros no vetor
      for ( int j = i + 1; j < tam; j++)
         if (compara_r(v[menor], v[j]) == 1)
            menor = j;

      // Substitui o local apontado pelos ponteiros
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
   }
}

/* Calcula soma de todos os elementos do vetor */
void calcula_soma(struct racional *soma, struct racional **vetor_ptr, int n){
   // Se a soma nao foi alocada retorna 0
   if (soma == NULL)
      return;

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

