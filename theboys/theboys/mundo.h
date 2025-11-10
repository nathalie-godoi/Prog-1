#ifndef MUNDO
#define MUNDO

/* Variaveis pre-definidas do MUNDO */
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define TAMANHO_MUNDO  20000
#define N_HABILIDADES  10
#define N_HEROIS 50 
#define N_BASES 10
#define N_MISSOES 5256
#define N_COMPOSTOS_V 30


/* Valor inteiro para tipo de evento */ 
#define CHEGA 0
#define ESPERA 1
#define SAI 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define VIAJA 6
#define MORRE 7
#define MISSAO 8
#define FIM 9

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "herois.h"
#include "base.h"
#include "evento.h"
#include "missao.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                     Define estrutura do MUNDO                      */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Define o struct localizacao */
struct local;
struct cjto_t;
struct fila_t;
struct fprio_t;
struct heroi;
struct base;
struct missao;
struct mundo;


/* Define a estrutura mundo que sera usada */
struct mundo {
   int NHerois;
   struct heroi **herois;
   int NBases;
   struct base **bases;
   int NMissoes;
   struct missao **missoes;
   int NHabilidades;
   int NCompostosV;
   struct local *dimensao;
   int Relogio;
   struct fprio_t *LEF;
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Define Conjunto de Funcoes no MUNDO                   */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Gera valores aleatorios entre min e max */
int aleat (int min, int max);

/* Cria e inicia o mapa, retorna NULL em caso de erro */
struct local *cria_mapa();

/* Cria local aleatorio, retorna um ponteiro de um local aleatorio */
struct local *local_aleat();

/* Desaloca o ponteiro do local aleatorio */
void destroi_local(struct local *l);

/* Programa evento fim do mundo */
void programa_fim(struct mundo *m);

/* Cria e inicializa os campos do mundo / simulacao 
 * Retorna um ponteiro para o mundo ou NULL se erro */
struct mundo *cria_mundo();

/* Destroi o mundo desalocando todas as suas estruturas */
void destroi_mundo(struct mundo *m);

/* Inicializa os campos do mundo */
void inicia_mundo(struct mundo *mundo);

#endif
