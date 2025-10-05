#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Define a struct racional */
struct racional {
   long num;          /* numerador   */
   long den;          /* denominador */
};

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b){
   // Transforma a e b em valores absolutos
   a = labs(a);
   b = labs(b);

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

   // Retorna o mdc
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

   MMC = labs(MMC); // Transforma em valor absoluto

   return MMC;
}

/* Simplifica o número racional indicado no parâmetro */
int simplifica_r (struct racional *r){
   long p = r->num, q = r->den, divisor;

   // Retorna 0 se a fracao for inválida ou nula
   if (q == 0 || p == 0) {
     return 0;
   }

   // Caso nao seja, simplifica denominador
   divisor = mdc(p, q);
   p = p / divisor;
   q = q / divisor;

   // Corrige sinais caso denominador for negativo
   if (q < 0) {
      p = -p;
      q = -q;
   }

   r->num = p;
   r->den = q;

   return 1;
}

/* Retorna o numerador do racional r */
long numerador_r (struct racional *r){
   return r->num;
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional *r){
   return r->den;
}

/* Cria um numero racional com o numerador e denominador indicados */
struct racional *cria_r (long numerador, long denominador){
   // Aloca o ponteiro r que aponta para uma struct racional
   struct racional *r = malloc(sizeof(struct racional));
   
   // Verifica se a alocacao ocorreu corretamenta 
   if (r == NULL) 
      return NULL;

   // Atribui os valores
   r->num = numerador;
   r->den = denominador;
   
   // Simplifica racional antes de retornar 
   simplifica_r(r);

   // Retorna o ponteiro
   return r;
}

/* Libera a memoria alocada para o racional apontado por r */
void destroi_r (struct racional **r){
   if (r != NULL && *r != NULL){
      free(*r);
      *r = NULL; 
   }
}

/* Testa se o racional eh valido e se foi alocado */
int valido_r (struct racional *r){
   // Retorna 0 se o racional nao esta alocado
   if (r == NULL) 
      return 0;
   
   // Retorna 0 se o racional for invalido
   if (r->den == 0)
      return 0;

   // Retorna 1 se for valido
   return 1;
}

/* Imprime o racional baseado em criterios pre-definidos */
void imprime_r (struct racional *r){
   if (r == NULL)
      printf("NULL"); // Se ponteiro nao foi alocado imprime NULL
   else if (valido_r(r) == 0)
      printf("NaN"); // Se for invalido imprime NaN (Not a Number)
   else if (r->num == 0)
      printf("0"); // Se for uma fracao nula imprime 0
   else if (r->den == 1) // Se denominador for 1 imprime soh o numerador
      printf("%ld", r->num);
   else if (r->num == r->den) // Se os fatores forem iguais imprime 1
      printf("1");
   else 
      printf("%ld/%ld", r->num, r->den); // Imprime a fracao      
}

/* Compara dois números racionais r1 e r2 */
int compara_r (struct racional *r1, struct racional *r2){
   long MMC;

   // Calcula mmc
   MMC = mmc(r1->den, r2->den);

   // Retorna -2 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return -2;

   // Retorna 0 se os racionais forem iguais
   if ((r1->num == r2->num) && (r1->den == r2->den))
      return 0;

   // Retorna 1 se r1 > r2
   if ((MMC / r1->den)*r1->num > (MMC / r2->den)*r2->num)
      return 1;

   // Retorna -1 se r1 < r2
   return -1;
}

/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2 */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3){
   long MMC;
   
   // Retorna 0 se o ponteiro for nulo
   if (r3 == NULL)
      return 0;
      
   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;

   // Calcula MMC
   MMC = mmc (r1->den, r2->den);

   // Realiza soma
   r3->num = (MMC / r1->den)*r1->num + (MMC / r2->den)*r2->num;
   r3->den = MMC;

   // Se a fracao irredutivel for invalida ou nula retorna 0
   if (simplifica_r(r3) == 0) 
      return 0;

   // Caso o resultado for valido retorna 1 
   return 1;
}

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2 */
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3){
   long MMC;
   
   // Retorna 0 se o ponteiro nao foi alocado
   if (r3 == NULL) 
      return 0;

   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;

   // Calcula MMC
   MMC = mmc (r1->den, r2->den);

   // Faz operacao
   r3->num = (MMC / r1->den)*r1->num - (MMC / r2->den)*r2->num;
   r3->den = MMC;

   // Simplifica fracao e retorna 0 se for nulo ou invalido
   if (simplifica_r(r3) == 0)
      return 0;

   // Caso o resultado for valido retorna 1
   return 1;
}

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2 */
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){
    
   // Retorna 0 se o ponteiro nao foi alocado
   if (r3 == NULL) 
      return 0;
   
   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;

   // Executa a operação se os denominadores forem validos
   r3->num = r1->num * r2->num;
   r3->den = r1->den * r2->den;

   // Retorna 0 se a simplificacao nao ocorreu por r ser nulo ou invalido 
   if (simplifica_r(r3) == 0)
      return 0;

   // Se a multiplicacao for valida retorna 1
   return 1;
}

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2 */
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){
    
   // Retorna 0 se o ponteiro nao foi alocado
   if (r3 == NULL) 
      return 0;

   // Retorna 0 se algum dos racionais nao for valido
   if (!(valido_r(r1) && valido_r(r2)))
      return 0;

   // Executa a divisao se os denominadores forem validos
   r3->num = r1->num * r2->num;
   r3->den = r1->den * r2->den;

   // Retorna 0 se a simplificacao nao ocorreu por r ser nulo ou invalido 
   if (simplifica_r(r3) == 0)
      return 0;

   // Se a divisao for valida retorna 1
   return 1;
}

