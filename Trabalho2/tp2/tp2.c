#define  MAX 100 // Maximo tamanho do vetor

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

// Cabecalho de funcoes auxiliares
void imprime_vetor(int tam, struct racional v[]);
void retira_r(int i, int n, struct racional vetor[]);
void ordena_vetor(int tam, struct racional vetor[]);

// Programa principal
int main (){
   int n, tam, invalido = 0;
   struct racional vetor[MAX], soma, *ptr_soma ;
   long num, den;

   // Inicializa soma e seu ponteiro
   soma = cria_r(0, 1);
   ptr_soma = &soma;

   // Le a quantidade de racionais que formarao o vetor
   scanf("%d", &n); 
   
   // Caso n nao satisfaça 1 < n < 100 retorna 0
   if (!(1 < n && n < 100)) 
      return 0;

   // Le o vetor de racionais e os simplifica 
   for ( int i = 0; i < n; i++){ 
      scanf("%ld %ld", &num, &den);
      vetor[i] = cria_r (num, den);
   }
   
   // Imprime o vetor completo
   printf("VETOR = ");
   imprime_vetor(n, vetor);
   
   // Conta a quantidades de numeros invalidos
   for ( int i = 0; i < n; i++){
      if (!(valido_r(vetor[i])))
         invalido++;
   }

   // Retira os racionais invalidos
   for ( int i = 0; i < n; i++){
      if (!valido_r(vetor[i]))
         /* Caso nao seja valido, substitui-o por 
         um racional valido do final do vetor*/
         retira_r(i, n, vetor); 
   }

   // Calcula o novo tamanho do vetor sem os valores invalidos
   tam = n - invalido; 

   // Imprime o vetor sem os racionais invalidos
   printf("VETOR = ");
   imprime_vetor(tam, vetor);
   
   // Ordena o vetor
   ordena_vetor(tam, vetor);

   // Imprime o vetor ordenado
   printf("VETOR = ");
   imprime_vetor(tam, vetor);

   // Calcula a soma dos elementos do vetor
   for ( int i = 0; i < tam; i++)
      soma_r(soma, vetor[i], ptr_soma);

   // Imprime a soma dos valores no vetor 
   printf("SOMA = ");
   imprime_r(soma);
   printf("\n");

   return 0 ;
}

/* Funcoes auxiliares */
/* Imprime os elementos do vetor */
void imprime_vetor (int tam, struct racional v[]){
   for ( int i = 0; i < tam; i++){
      imprime_r(v[i]);
      printf(" ");
   }
   printf("\n");
}

// Remove os racionais invalidos 
void retira_r ( int i, int n, struct racional vetor[]) {
   for ( int j = n - 1; j > i; j--) {
      if (valido_r(vetor[j])){
         vetor[i] = vetor[j];
         vetor[j].den = 0;
         break;
       }
   }
}

// Ordena o vetor usando select sort
void ordena_vetor (int tam, struct racional vetor[]){
   for (int i = 0; i < tam; i++){
      struct racional aux;
      int menor = i;

      // Encontra menor valor no vetor
      for ( int j = i + 1; j < tam; j++)
         if (compara_r(vetor[menor], vetor[j]) == 1)
            menor = j;

      // Substitui o v[i] pelo menor valor
      aux = vetor[i];
      vetor[i] = vetor[menor];
      vetor[menor] = aux;
   }
}
