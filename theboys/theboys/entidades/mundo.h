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


/* ENUM para tipo de evento */
enum tipo_evento {
   CHEGA,
   ESPERA,
   SAI,
   DESISTE,
   AVISA,
   ENTRA,
   VIAJA,
   MORRE,
   MISSAO,
   FIM
};

/* Includes */
#include <stdio.h>
#include <stdlib.h>

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
int aleat(int min, int max);

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

/* Simula o mundo */
int simula_mundo(struct mundo *m);

#endif
