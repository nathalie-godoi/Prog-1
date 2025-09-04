#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional simplifica_r(struct racional r);

/*Retorna numerador*/
long numerador_r (struct racional r){
   return r.num;
}

/*Retorna denominador*/ 
long denominador_r (struct racional r){
   return r.den;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){
   struct racional novo_r;

   novo_r.num = numerador;
   novo_r.den = denominador;

   return novo_r;
}

/* Retorna 0 se denominador for invalido, ou seja, 
igual a 0, e 1 se for valido */
int valido_r (struct racional r){
   int denominador = r.den;

   if (denominador == 0)
      return 0;

   return 1;
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){
   long random;

   random = min + rand() % (max - min + 1); // Gera um número aleatório 

   return random;
}

/* Máximo Divisor Comum entre a e b      */
long mdc (long a, long b){
   // Transforma a e b em valores absolutos
   if (a < 0)
      a = -a;
   if (b < 0)
      b = -b;

   // Caso um deles seja = 0, o mdc é o outro
   if (a == 0)
      return b;
   if (b == 0)
      return a;

   // Algoritmo de Euclides
   while (b != 0) {
      long aux = a % b; // Resto da divisão
      a = b;
      b = aux;
   }

   return a;
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

   return MMC;
}

/* Recebe um numero racional e o simplifica */
struct racional simplifica_r (struct racional r){
   long p = r.num, q = r.den, divisor;
   struct racional resultado;

   // Fração inválida
   if (q == 0) {
     return r;
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

   return resultado;
}

/* Sorteia numerador e denominador entre min e max */
struct racional sorteia_r (long min, long max){
   struct racional sorteado;

   sorteado.num = aleat (min, max);
   sorteado.den = aleat (min, max);
  
   sorteado = simplifica_r(sorteado);
  
   return (sorteado);
}

/* Imprime racional com base em criterios
definidos no arquivo de cabecalho */
void imprime_r (struct racional r){

   if (!valido_r(r)){
      printf("NaN"); // Se o racional nao for real, imprime (Not a Number)
   }

   else {
      if (r.num == 0)
         printf("0"); // Se o numerador for nulo, imprime 0
      else {
         if (r.den == 1)
            printf("%ld", r.num); // Se o denominador for 1, imprime apenas o numerador
         else {
            if (r.num == r.den)
               printf("1"); // Se o denominador e o numerador forem iguais, imprime 1
            else
               printf("%ld/%ld", r.num, r.den); // Racional valido
         }
      }
   }
}

/* Compara dois racionais r1 e r2 */
int compara_r (struct racional r1, struct racional r2){
   long MMC;
   
   // Calcula mmc
   MMC = mmc(r1.den, r2.den);

   // Retorna -2 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return -2;
   
   // Retorna 0 se os racionais forem iguais
   if ((r1.num == r2.num) && (r1.den == r2.den))
      return 0;
   
   // Retorna 1 se r1 > r2
   if ((MMC / r1.den)*r1.num > (MMC / r2.den)*r2.num)
      return 1;
   
   // Retorna -1 se r1 < r2
   return 1;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3 */
int soma_r (struct racional r1, struct racional r2, struct racional *r3){
   struct racional resul_soma;
   long MMC;

   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;
   
   // Calcula MMC
   MMC = mmc (r1.den, r2.den);
   
   // Realiza soma
   resul_soma.num = (MMC / r1.den)*r1.num + (MMC / r2.den)*r2.num;
   resul_soma.den = MMC;
   
   // Transforma em fracao irredutivel
   resul_soma = simplifica_r(resul_soma);

   // Retorna 0 se numerador for nulo 
   if (resul_soma.num == 0) 
      return 0;
   
   // Caso o resultado for valido, passa o resultado e retorna 1 
   r3->num = resul_soma.num;
   r3->den = resul_soma.den;
   return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3 */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
   struct racional resul_sub;
   long MMC;
   
   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;
   
   // Calcula MMC
   MMC = mmc (r1.den, r2.den);

   // Faz operacao
   resul_sub.num = (MMC / r1.den)*r1.num - (MMC / r2.den)*r2.num;
   resul_sub.den = MMC;

   // Simplifica fracao
   resul_sub = simplifica_r(resul_sub);
   
   // Retorna 0 se numerador for nulo
   if (resul_sub.num == 0)
      return 0;
   
   // Caso o resultado for valido, passa o resultado e retorna 1
   r3->num = resul_sub.num;
   r3->den = resul_sub.den;
   return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3 */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
   struct racional resul_mult;
   
   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;

   // Executa a operação se os denominadores forem validos
   resul_mult.num = r1.num * r2.num;
   resul_mult.den = r1.den * r2.den;
   
   // Simplifica fracao
   resul_mult = simplifica_r(resul_mult);

   // Retorna 0 se o numerador eh 0
   if (resul_mult.num == 0) 
      return 0;

   // Caso a multiplicacao for valida, passa o resultado e retorna 1
   r3->num = resul_mult.num;
   r3->den = resul_mult.den;
   return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3 */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){
   struct racional resul_div;

   // Retorna 0 se algum dos racionais nao for valido
   if (!valido_r(r1) || !valido_r(r2) || r2.num == 0) 
      return 0;
   
   // Executa a operação se os denominadores forem válidos
   resul_div.num = r1.num * r2.den;
   resul_div.den = r1.den * r2.num;
   
   // Simplifica fracao
   resul_div = simplifica_r(resul_div);

   // Testa se o resultado é válido (numerador = 0)
   if (resul_div.num == 0)
      return 0;

   // Caso a multiplicacao for valida, passa o resultado e retorna 1
   r3->num = resul_div.num;
   r3->den = resul_div.den;
   return 1;
}

