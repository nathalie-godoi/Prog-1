#define  MAX 100

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional simplifica_r(struct racional r);

int main (){
   int n, novo_n = 0, invalido = 0;
   struct racional vetor[MAX];
   
   scanf("%d", &n); // Le quantidade de racionais 
   
   // Le o vetor de racionais e os simplifica 
   for ( int i = 0; i < n; i++){ 
      scanf("%ld %ld", &vetor[i].num, &vetor[i].den);
      vetor[i] = simplifica_r (vetor[i]);
   }
   
   // Imprime o vetor completo
   printf("VETOR = ");
   for ( int i = 0; i < n; i++){ 
      imprime_r(vetor[i]);
      printf(" ");
   }

   printf("\n");
   
   // Retira os racionais invalidos
   printf("VETOR = ");
   for ( int i = 0; i < n-invalido; i++){
      if (!valido_r(vetor[i])){
         invalido++;
         /* Substitui o racional invalido do inicio 
          por um racional valido do final*/
         for ( int j = n - 1; i < n; j--) {
            if (valido_r(vetor[j])){
               vetor[i] = vetor[j];
               vetor[j].den = 0;
               break;
            };
         };
      };
   };
   
   novo_n = n - invalido;

   // Imprime o vetor sem os racionais invalidos
   for (int i = 0; i < novo_n; i++) {
      if (valido_r(vetor[i])) {
         imprime_r(vetor[i]);
        printf(" ");
      }
   }
   printf("\n");
   
   // Ordena o vetor
   
   // Imprime o vetor ordenado
   return (0) ;
}
