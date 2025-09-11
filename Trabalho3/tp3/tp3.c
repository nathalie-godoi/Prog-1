#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Cabecalho das funcoes auxiliares*/
void imprime_vetor(int tam, struct racional **v);
void ordena(struct racional **v, int tam);

/* programa principal */
int main ()
{  
   int n, invalido = 0;
   long num, den;
   struct racional *soma = cria_r(0, 1);
   
   // Le a quantidade de racionais 
   scanf("%d", &n);
   
   // Testa se n satisfaz 0 < n < 100
   if (!(0 < n && n < 100)) 
      return 0;
   
   // Aloca dinamicamente um ponteiro de ponteiros que apontam para racionais
   struct racional **vetor_ptr = malloc(n * sizeof(struct racional *));

   // Preenche o vetor
   for (int i = 0; i < n; i++){
      scanf("%ld %ld", &num, &den);
      vetor_ptr[i] = cria_r(num, den);
   }
   
   // Imprime vetor completo
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Calcula quantidade de invalidos
   for (int i = 0; i < n; i++)
      if (!valido_r(vetor_ptr[i]))
         invalido++;
   
   // Substitui racional invalido do inicio por um valido do fim
   for (int i = 0; i < n; i++){
      if (!valido_r(vetor_ptr[i])){
         for (int j = n - 1; j >= i; j--){
            struct racional *aux = NULL;
            if (valido_r(vetor_ptr[j])){
               aux = vetor_ptr[j];
               vetor_ptr[j] = vetor_ptr[i];
               vetor_ptr[i] = aux;
               break;
            }
         }
      }
   }
   
   // Remove racionais invalidos
   for (int i = n - invalido; i < n; i++)
      if (!valido_r(vetor_ptr[i]))
         destroi_r(&vetor_ptr[i]);
   
   // Corrige o tamanho do vetor
   n = n - invalido;

   // Imprime vetor sem invalidos
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);
   
   // Ordena vetor em ordem crescente
   ordena(vetor_ptr, n);

   // Imprime vetor ordenado
   printf("VETOR = ");
   imprime_vetor(n, vetor_ptr);

   // Calcula Soma
   for (int i = 0; i < n; i++)
      soma_r(soma, vetor_ptr[i], soma);

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

void imprime_vetor(int tam, struct racional **v){
   /* Percorre o vetor de ponteiros e imprime 
   o racional apontado por cada um */
   for(int i = 0; i < tam - 1; i++){
      imprime_r(v[i]);
      printf(" ");
   }
   
   /*Imprime o ultimo elemento separado
   para nao ter um espaco extra*/
   if (tam > 0)
      imprime_r(v[tam-1]);
   printf("\n");
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

