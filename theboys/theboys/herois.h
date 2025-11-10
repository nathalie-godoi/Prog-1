#ifndef HEROI
#define HEROI

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "base.h"
#include "evento.h"
#include "missao.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                      Define estrutura dos herois                   */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* structs usadas para definir herois ou nas suas funcoes */
struct cjto_t;
struct fila_t;
struct fprio_t;
struct local;
struct base;
struct missao;
struct mundo;

/* define a struct heroi */
struct heroi {
   int ID; /* identifica heroi */
   struct cjto_t *habilidades; /* conjunto das habilidades */
   int paciencia; /* paciencia */
   int velo; /* velocidade */
   int exp; /* experiencia do heroi */
   int base; /* ID identifica base */
   int vivo; /* 0 morto 1 vivo */
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Define Conjunto de Funcoes para HEROIS                */                
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Cria um ponteiro para uma struct heroi */ 
struct heroi *cria_heroi();

/* Inica heroi e suas caracteristicas, ainda nao esta em nenhuma base */
void inicia_heroi(struct heroi *h, int qntd_h);

/* Destoi vetor de ponteiros de herois */
void destroi_herois(struct heroi **h);

/* Heroi morre, atualiza seu status para 0 (morto) */
void heroi_morre(struct mundo *m, int id_heroi);

/* Calcula permanencia de um heroi em uma base:
 * tpm = 15 + paciencia * numero aleatorio 
 * Retorna a permanencia ou -1 em caso de erro */
int calcula_permanencia(struct heroi *h);

/* Atualiza experiencia apos concluir missao  + 7 */
void atualiza_exp(struct heroi *h);

/* Atualiza as habilidades que o heroi h possui para concluir missao 
 * Nesse caso o composto V eh usado */
void atualiza_habli(struct heroi *h, struct missao *m);

/* Retorna velocidade do heroi ou -1 se erro */
int velo_heroi(struct heroi *h);

/* Retorna experiencia atual do heroi h ou -1 se erro */
int exp_heroi(struct heroi *h);

/* Retorna ponteiro para o heroi mais experiente da base b */
struct heroi *heroiExp(struct base *b, struct mundo *mundo);

/* Encontra heroi no mundo e retorna seu ponteiro */
struct heroi *encontra_heroi_mundo(int id_heroi, struct mundo *m);

/* Aumenta a experiencia de todos os herois da base b
 * que participaram da missao */
void aumenta_XP_herois(struct mundo *m, struct base *b);

/* Retorna o ID (identificacao) da base do heroi
 * ou -1 em caso de erro */
int base_heroi(struct heroi *h);

/* atualiza a base que o heroi esta */
void atualiza_base_heroi(struct heroi *h, int id_base);

/* Mostra estatistica do heroi h */
void estatistica_heroi(struct heroi *h); 

#endif
