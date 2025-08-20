#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional simplifica_r (struct racional r);
long aleat (long min, long max);
long mmc (long a, long b);

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){
   struct racional novo_racional;

   novo_racional.num = numerador;
   novo_racional.den = denominador;

   return (novo_racional);
}
/* Retorna 0 se denominador for invalido, ou seja, 
igual a 0, e 1 se for valido*/
int valido_r (struct racional r){
   int denominador = r.den;

   if (denominador == 0) 
       return (0);

   return (1);
}

struct racional sorteia_r (long min, long max) {
   struct racional sorteado;

   // Sorteia numerador e denominador entre min e max
   sorteado.num = aleat (min, max); 
   sorteado.den = aleat (min, max); 

   sorteado = simplifica_r(sorteado); 

   return (sorteado);
}

void imprime_r (struct racional r){    

   if (!valido_r(r)){
      printf("INVALIDO"); // Se o racional nao for real, imprime INVALIDO
   }

   else { 
      if (r.num == 0) 
         printf("0"); // Se o numerador for nulo, imprime 0
      else {
         if (r.den == 1)
            printf("%ld", r.num); // Se o denominador for 1, imprime apenas o denominador 
         else {
            if (r.num == r.den)
               printf("1"); // Se o denominador e o numerador forem iguais, imprime 1
            else
               printf("%ld/%ld", r.num, r.den); // Racional valido
         }
      }
   }
} 

struct racional soma_r (struct racional r1, struct racional r2){
   struct racional resul_soma;
   long MMC;

   MMC = mmc (r1.den, r2.den); // Calcula mmc

   /* Para realizar a soma, multiplico o numerador e o denominador pelo mmc
   e depois faço a operacao normalmente*/
   resul_soma.num = (MMC / r1.den)*r1.num + (MMC / r2.den)*r2.num;
   resul_soma.den = MMC;
	
   return (resul_soma);
}

struct racional subtrai_r (struct racional r1, struct racional r2){
   struct racional resul_sub;
   long MMC;

   /* Repete o mesmo processo da soma porem com o sinal 
   oposto na segunda fracao*/
   MMC = mmc (r1.den, r2.den);
   resul_sub.num = (MMC / r1.den)*r1.num - (MMC / r2.den)*r2.num;
   resul_sub.den = MMC;

   return (resul_sub);
}

struct racional multiplica_r (struct racional r1, struct racional r2){
   struct racional resul_mult;

   if (!(valido_r(r1) || valido_r(r2))){
      resul_mult.num = 1;
      resul_mult.den = 0;   // Invalido   
      return (resul_mult);
   }

   // Executa a operação se os denominadores forem validos 
   resul_mult.num = r1.num * r2.num;
   resul_mult.den = r1.den * r2.den;

   // Testa se o resultado é válido
   if (resul_mult.den == 0) {
      resul_mult.num = 1;
      resul_mult.den = 0;
   }

   return (resul_mult);
}

struct racional divide_r (struct racional r1, struct racional r2){
   struct racional resul_div;

   if (!valido_r(r1) || !valido_r(r2) || r2.num == 0) {
      resul_div.num = 1;
      resul_div.den = 0;  // Inválido	    
   }

   // Executa a operação se os denominadores forem válidos 
   else {
      resul_div.num = r1.num * r2.den;
      resul_div.den = r1.den * r2.num;
   }

   // Testa se o resultado é válido
   if (resul_div.den == 0){
      resul_div.num = 1;
      resul_div.den = 0;  // Inválido
   }

   return (resul_div);
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){
   long random;

   random = min + rand() % (max - min + 1); // Gera um número aleatório 

   return (random);
}

/* MDC é o valor absoluto */
long mdc (long a, long b){
   // Transforma a e b em valores absolutos
   if (a < 0)
      a = -a;
   if (b < 0)
      b = -b;

   // Caso um deles seja = 0, o mdc é o outro
   if (a == 0)
      return (b);
   if (b == 0)
      return (a);

   // Algoritmo de Euclides
   while (b != 0) {
      long aux = a % b; // Resto da divisão
      a = b;
      b = aux;
   }

   return (a);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
/* mmc é o valor absoluto, ou seja, 
=> mmc >=  1, sempre que a e b forem diferentes de 0 */
long mmc (long a, long b){
   long p = a, q = b, MDC, MMC;

   MDC = mdc(p, q);
   MMC = (p * q) / MDC; // Calcula MMC

   if (MMC < 0)
      MMC = -MMC; // Transforma em valor absoluto

   return (MMC);
}

/* Recebe um número racional e o simplifica.*/
struct racional simplifica_r (struct racional r){
   long p = r.num, q = r.den, divisor;
   struct racional resultado;
    
   // Fração inválida
   if (q == 0) {
     return(r);
   }

   //Simplifica denominador
   divisor = mdc(p, q);
   p = p / divisor;
   q = q / divisor;

   // Corrige sinais caso denominador for negativo
   if (q < 0) {
      p = -p;
      q = -q;
   }

   resultado.num = p;
   resultado.den = q;

   return(resultado);
}
