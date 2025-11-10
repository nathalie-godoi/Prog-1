#ifndef MISSAO_H
#define MISSAO_H

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "herois.h"
#include "base.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                       Define estrutura da MISSAO                   */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* structs auxiliares para definir missao e suas funcoes */
struct cjto_t;
struct fila_t;
struct fprio_t;
struct heroi;
struct local;
struct base;
struct mundo;

/* Define a stuct missao */
struct missao {
   int ID;
   struct cjto_t *habilidades; /* conjunto necessario para concluir missao */
   struct local *local; /* struct de localizacao da missao */
   int status; /* concluida ou impossivel 1/0 */
   int tentativas;
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*             Especifica Conjunto de Funcoes para MISSAO             */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Cria missao com posisao e habillidades necessarias aleatorias 
 * Retorna o ponteiro para esse missao */
struct missao *cria_missao(int n);

/* Destroi as missoes apontadas pelo vetor inclusive o vetor */
void destroi_missoes(struct missao **m);

/* Encontra a missao no mundo e retorna o ponteiro  
 * para a missao ou NULL em caso de erro */
struct missao *encontra_missao_mundo(int id_missao, struct mundo *m);

/* Incrementa quantidade de missoes concluidas pela base B 
 * e atualiza status da missao para concluida (1) */
void completa_missao(struct missao *m, struct base *b);

/* Testa se os herois possuem habilidades necessarias pra missao 
 * Retorna 1 se sim e 0 se nao possuem */
int tenta_missao(struct missao *m, struct base *b);

/* Procura a base mais prox para realizar a missao */
struct base *prox_missao(struct missao *missao, struct mundo *mundo);

/* Imprime status de missao completa pela base b no tempo t */
void imprime_missao_completa(int tempo, int id_missao, struct base *b);

/* Adia a missao pois nao eh possivel conclui-la e corrige data da missao */
void adia_missao(int tempo, struct missao *missao, struct mundo *mundo);

/* Testa se o heroi pode usar o CompostoV
 * TA = 2500 * n , ou seja, 2500 deve ser divisivil por 2500. 
 * Retorna 1 se eh divisil e 0 caso contrario */
int testa_CompostoV(struct mundo *m);

/* Usa CompostoV, dando as habilidades necessarias 
 * ao heroi par a conclusao da missao */
void usa_compostoV(struct heroi *h, struct missao *missao, struct mundo *mundo); 

/* Retorna quantidade de CompostosV disponiveis */ 
int qntd_CompostosV(struct mundo *m);

/* Diminui qntd de compostos V disponiveis */
void diminui_compostosV(struct mundo *m);

/* Imprime as estatisticas da missao */
void estatistica_missao(struct mundo *m);

#endif
