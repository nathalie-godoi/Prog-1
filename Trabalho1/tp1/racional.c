/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional simplifica_r (struct racional r);
long aleat (long min, long max);
long mmc (long a, long b);

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){
    struct racional novo_racional;

    novo_racional.num = numerador;
    novo_racional.den = denominador;

    return (novo_racional);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r){
    int denominador = r.den;

    if (denominador == 0) 
        return (0);
    else 
        return (1);
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max) {
   struct racional racional_sorteado;

   racional_sorteado.num = aleat (min, max);
   racional_sorteado.den = aleat (min, max);

   return (racional_sorteado);
}
/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r){ 
   r = simplifica_r(r);   

   if (!valido_r(r)){
       printf("INVALIDO");
       return;
   }
   else { 
       if (r.num == 0) 
           printf("0");
       else {
	   if (r.den == 1)
	      printf("%ld", r.num);
           else {
                if (r.num == r.den)
	            printf("1");
                else
                    printf("%ld/%ld", r.num, r.den); 
		}
	   }
   }
} 

/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2){
    struct racional resul_soma;
    long MMC;

    MMC = mmc (r1.den, r2.den);
    resul_soma.num = (MMC / r1.den)*r1.num + (MMC / r2.den)*r2.num;
    resul_soma.den = MMC;
	
    return (resul_soma);
}

/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2){
    struct racional resul_sub;
    long MMC;

    MMC = mmc (r1.den, r2.den);
    resul_sub.num = (MMC / r1.den)*r1.num - (MMC / r2.den)*r2.num;
    resul_sub.den = MMC;

    return (resul_sub);
}

/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional resul_mult;
   
    if (!(valido_r(r1) || valido_r(r2))){
        resul_mult.num = 1;
        resul_mult.den = 0;   // Inválido   
        return (resul_mult);
    }

    // Executa a operação se os denominadores forem válidos 
    resul_mult.num = r1.num * r2.num;
    resul_mult.den = r1.den * r2.den;

    // Testa se o resultado é válido
    if (resul_mult.den == 0) {
	resul_mult.num = 1;
        resul_mult.den = 0;
    }

    return (resul_mult);
}

/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
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
    
    random = min + rand() % (max - min + 1);// Gera um número aleatório 
    
    return (random);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
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

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
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

/* implemente as demais funções aqui */

