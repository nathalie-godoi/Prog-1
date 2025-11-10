#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "herois.h"
#include "base.h"
#include "missao.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                 Define estrutura de um evento                      */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* structs usadas nas definicao de evento ou nas funcoes dela */
struct cjto_t;
struct fila_t;
struct fprio_t;
struct heroi;
struct local;
struct base;
struct missao;
struct mundo;

/* Definicao de evento :
 * caso nao haja o campo eh add -1 nele */
struct evento {
   int data; /* data do evento na LEF */
   int tipo; /* identifica tipo de evento */
   int heroi ; /* ID do heroi */ 
   int ID; /* ID da base ou missao */
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Define Conjunto de Funcoes para EVENTO                */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


/* Cria um evento e o adiciona na LEF */
void cria_evento(int tempo, int id_heroi, int ID, int tipo, struct mundo *m);

/* Destroi evento */
void destroi_evento(struct evento *e);

/* Add evento na LEF respeitando horario/data */
void add_LEF(struct fprio_t *LEF, struct evento *novo);

/* Inicia os eventos inciais 
 * Ex: Criação de herois
 * Criação de missão */
int eventos_iniciais(struct mundo *mundo);

/* Tira o evento pra executa-lo retornando seu ponteiro */
struct evento *remove_evento(struct fprio_t *LEF);

/* Processa um evento baseado no seu tipo :
 * tipo = 's' evento sai, tipo = 'm' evento missao */
void processa_evento(struct mundo *m, struct evento *e);

/* Evento CHEGA */
void chega(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento ESPERA */
void espera(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento DESISTE */
void desiste(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento AVISA */
void avisa (int tempo, int id_base, struct mundo *m);

/* Evento ENTRA */
void entra(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento SAI */
void sai(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento VIAJA */
void viaja(int tempo, int id_heroi, int id_base, struct mundo *m);

/* Evento MORRE */
void morre(int tempo, int id_heroi, int id_missao, struct mundo *m);

/* Evento MISSAO */
void missao(int tempo, int id_missao, struct mundo *m);

/* Evento FIM */
void fim (int tempo, struct mundo *mundo);

#endif
