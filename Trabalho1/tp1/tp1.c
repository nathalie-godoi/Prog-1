#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/* programa principal */
int main ()
{   
   int n, max, i ;
   struct racional r1, r2, soma, sub, mult, div;
   srand (0); /* use assim, com zero */

   scanf("%d %d", &n, &max);    

   for (i = 1; i <= n; i++) {
      printf("%d: ", i);

      r1 = sorteia_r(-max, max); // Sorteia racional
      r2 = sorteia_r(-max, max); 

      imprime_r(r1);
      printf(" ");
      imprime_r(r2);
      printf(" ");

      // Verifica se um dos numeros eh uma fracao invalida 
      if (valido_r(r1) == 0 || valido_r(r2) == 0) {
         printf("NUMERO INVALIDO\n");
         return (1);
      }

      // Realiza as operacoes
      soma = soma_r (r1, r2);
      sub = subtrai_r (r1, r2);
      mult = multiplica_r (r1, r2);
      div = divide_r (r1, r2);

      // Verifica se a divisao eh valida
      if (!valido_r(div)){
         printf("DIVISAO INVALIDA \n");
         return (1);
      }

      // Imprime os resultados das operacoes
      imprime_r(soma);
      printf(" ");
      imprime_r(sub);
      printf(" ");
      imprime_r(mult);
      printf(" ");
      imprime_r(div);
      printf("\n");
   }

   return (0) ;
}
