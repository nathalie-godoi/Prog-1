#ifndef BASE
#define BASE

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "herois.h"
#include "evento.h"
#include "missao.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*           Define estrutura das bases e da localizacao              */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Define a struct localizacao (ponto no plano) */
struct local {
   int x; /* coordenada x */
   int y; /* coordenada y */
};

/* structs usadas na definicao de base ou nas funcoes dela */
struct cjto_t;
struct fila_t;
struct fprio_t;
struct heroi;
struct base;
struct missao;
struct mundo;

/* Define uma struct base */
struct base {
   int ID; /* numero de identificacao da base */
   int tam; /* capacidade maxima de herois na base */
   struct cjto_t *presentes; /* cojunto dos ID dos herois presentes */
   struct fila_t *espera; /* fila de espera de herois */
   struct cjto_t *habilidades; /* conjunto de habilidades da base */
   struct local *local; /* struct lcoal que define posicao no plano (x0,y0) */
   int maxFILA; /* qnts maxima de herois que ficaram simultaneamente na fila */ 
   int missoes; /* numero de missoes completas pela base */
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Define Conjunto de Funcoes para BASES                 */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


/* Cria uma base e retorna seu ponteiro */
struct base *cria_base();

/* Inicia uma base com i sendo o numero de identificacao da base  */
void inicia_base(struct base *b, int i); // conjunto vazio  - presentes

/* Destroi o vetor de ponteiros para bases e o vetor */
void destroi_bases(struct base **b);

/* Calcula a distancia da base b ate a base destino
 * a distancia eh medida usando raio de uma circunferencia
 * d/r = sqrt((Xb - Xd)^2 + (Yb - Yd)^2) */
int distancia_a_base(struct base *b, struct local *d);

/* Retorna o ID identificação da base */
int indentifica_base(struct base *b);

/* Retorna numero de herois na base 
 * Retorna -1 se conjunto nao existe ou tam */
int testa_capcdd(struct cjto_t *p);

/* Retorna o numero de herois na fila de espera */
int tam_espera(struct base *b);

/* Lista os herois que estam na base */
void lista_presentes(struct base *b);

/* Atualiza o conjunto de habilidades possuidas pela base */
void calcula_habilidades_base(struct base *b, struct mundo *m);

/* Testa se heroi quer entrar na espera da base b
 * espera = (paciencia de H ) > (10 * tam da fila na base) */
int testa_espera(struct base *b, struct heroi *h);  

/* Retira o primeiro heroi da espera pois liberou espaco na base 
 * Retorna o ponteiro do heroi ou NULL em caso de erro ou espera vazia */
struct heroi *sai_espera(struct base *b);

/* Remove heroi da base, retirando-o da lista de presentes
 * e recalculando o conjunto de habilidades presentes na base */ 
void sai_base(struct base *b, int id_heroi, struct mundo *m);

/* Chega na base e tenta entrar, caso nao consigo entra na lista de espera: 
 * Retorna 0 se heroi ja esta na base
 * Retorna 1 caso tenha vaga na base e a fila de espera esteja vazia
 * Retorna 2 se eh eh possivel entrar na espera ou -1 se desiste dela */
int chega_base(struct base *b, struct heroi *h); 

/* Retorna ponteiro para posicao da base */
struct local *pos_base(struct base *b);

/* Porteiro verifica a lista de espera: 
 * Retorna tam da fila de espera ou -1 se erro */
int verifica_espera(struct base *b);

/* Sorteia uma base aleatoria 
 * usa a funcao de aleatorio para 
 * sortear uma posicao no vetor de base */
int base_aleatoria(int NBases); 

/* Adiciona heroi na base e atualiza o conjunto de habilidades da base */
void entra_base(struct base *b, struct heroi *h);

/* Uni as habilidades do heroi com a base b */
void uni_habilidades(struct base *b, struct cjto_t *h_habilidades);

/* Entra na fila de espera da base */
void entra_espera(struct base *b, struct heroi *h);

/* Encontra base no mundo atraves do numero de identificacao (ID) da base */
struct base *encontra_base_mundo(int id_base, struct mundo *m);

/* Imprime estatistica da base */
void estatistica_base(struct base *b);

#endif 
