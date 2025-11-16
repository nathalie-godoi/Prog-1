#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../extras/fprio.h"
#include "../extras/fila.h"
#include "../extras/conjunto.h"
#include "herois.h"
#include "base.h"
#include "../eventos/evento.h"
#include "../eventos/missao.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Especifica Conjunto de Funcoes para MUNDO             */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

struct local;
struct mundo;

/* Gera valores aleatorios entre min e max */
int aleat (int min, int max){
   int random;

   random = min + rand() % (max - min + 1); /* Gera um número aleatório */
   return (random);
}

/* Cria e inicia o mapa */
struct local *cria_mapa(){
   struct local *l = malloc(sizeof(struct local));
   if (!l)
      return NULL;
   l->x = TAMANHO_MUNDO;
   l->y = TAMANHO_MUNDO;
   return l;
}

/* Cria local aleatorio */
struct local *local_aleat(){
   struct local *l = malloc(sizeof(struct local));
   if (!l)
      return NULL;
   l->x = aleat(0, TAMANHO_MUNDO - 1);
   l->y = aleat(0, TAMANHO_MUNDO - 1);
   return l;
}

/* Destroi local aleatorio */
void destroi_local(struct local *l){
   if (!l)
      return;
   free(l);
}

/* Programa evento fim do mundo */
void programa_fim(struct mundo *m){
   cria_evento(T_FIM_DO_MUNDO, -1, -1, FIM, m);
}

/* Cria e inicializa o mundo / simulacao campos = NULL */
struct mundo *cria_mundo(){
   struct mundo *m = malloc(sizeof(struct mundo));
   if (!m)
      return NULL;
   /* Inicia herois */
   m->NHerois = N_HEROIS;
   m->herois = malloc(sizeof(struct heroi *) * N_HEROIS);
   for(int i = 0; i < N_HEROIS; i++)
      m->herois[i] = NULL;

   /* Inicia bases */
   m->NBases = N_BASES;
   m->bases = malloc(sizeof(struct base *) * N_BASES);
   for(int i = 0; i < N_BASES; i++)
      m->bases[i] = NULL;

   /* Inicia missoes */
   m->NMissoes = N_MISSOES;
   m->missoes = malloc(sizeof(struct missao *) * N_MISSOES);
     for(int i = 0; i < N_MISSOES; i++)
        m->missoes[i] = NULL;

   /* Inicia resto */
   m->LEF = fprio_cria();
   m->NHabilidades = N_HABILIDADES;
   m->NCompostosV = N_COMPOSTOS_V;
   m->dimensao = cria_mapa();
   m->Relogio = T_INICIO;
   return m;
}

/* Destroi o mundo desalocando todas as suas estruturas */
void destroi_mundo(struct mundo *m){
   destroi_herois(m->herois);
   destroi_bases(m->bases);
   destroi_missoes(m->missoes);
   destroi_local(m->dimensao);
   fprio_destroi(m->LEF);
}

/* Inicializa os campos do mundo */
void inicia_mundo(struct mundo *mundo){
   /* Mundo nao existe */
   if (!mundo)
      return;
   
   /* Inicia srand time */
   srand(time(NULL));

   /* Inicializa bases */
   for(int i = 0; i < N_BASES; i++){
      mundo->bases[i] = cria_base();
      inicia_base(mundo->bases[i], i);
      estatistica_base(mundo->bases[i]);
   };

   /* Inicializa herois */
   for(int i = 0; i < N_HEROIS; i++){
      mundo->herois[i] = cria_heroi();
      inicia_heroi(mundo->herois[i], i);
      estatistica_heroi(mundo->herois[i]);
   };

   /* Inicializa missoes */
   for(int i = 0; i < N_MISSOES; i++)
      mundo->missoes[i] = cria_missao(i); 
}

/* Simula o mundo */
int simula_mundo(struct mundo *m){
   /* Inicia eventos iniciais */
   if (!eventos_iniciais(m)){
      destroi_mundo(m);
      free(m);
      return 1;
   }

   /* Inicia simulacao retirando eventos da LEF */
   struct evento *evento_atual = remove_evento(m->LEF);
   int NEventos = 0;
   while(evento_atual != NULL && evento_atual->tipo != FIM){
      processa_evento(m, evento_atual);
      evento_atual = remove_evento(m->LEF);
      NEventos++;
   }

   /* Evento atual fim do mundo */
   if (evento_atual!= NULL && evento_atual->tipo == FIM)
      processa_evento(m, evento_atual);

   /* Finaliza simulacao destruindo o mundo e seus objetos */
   printf("EVENTOS TRATADOS: %d\n", NEventos);
   free(m);
   return 0;
}
