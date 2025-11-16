#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "../extras/fprio.h"
#include "../extras/fila.h"
#include "../extras/conjunto.h"
#include "herois.h"
#include "../eventos/evento.h"
#include "../eventos/missao.h"
#include "mundo.h"
#include <math.h>

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Especifica Conjunto de Funcoes para BASES             */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Cria uma base e retorna seu ponteiro */
struct base *cria_base(){
   struct base *b = malloc(sizeof(struct base));

   /* Garante que foi alocada */
   if (!b)
      return NULL;

   /* Inicializa base */
   b->ID = -1;
   b->tam = 0;
   b->presentes = NULL;
   b->espera = NULL;
   b->local = NULL;
   b->habilidades = NULL;
   b->maxFILA = 0;
   b->missoes = 0;

   return b;
};

/* Inicia uma base */
void inicia_base(struct base *b, int i){
   /* Garante que foi alocada */
   if (!b)
      return ;

   /* Inicializa base */
   b->ID = i;
   b->tam = aleat(3, 10); /* min 3, max 10 herois */
   b->presentes = cjto_cria(N_HEROIS);
   b->espera = fila_cria(); /* fila vazia */
   b->local = local_aleat();
   b->habilidades = cjto_cria(N_HABILIDADES);
   b->maxFILA = 0;
   b->missoes = 0;
};

/* Destroi vetor de ponteiro de bases */
void destroi_bases(struct base **b){
   /* Ponteiro NULL */
   if (!b)
      return;
   /* Percorre o vetor desalocando as bases e seus conteudos */
   for(int i = 0; i < N_BASES; i++){
      if (b[i]){
         if(b[i]->presentes) /* destroi cjto dos id dos herois */
            cjto_destroi(b[i]->presentes);
         if (b[i]->local)
             destroi_local(b[i]->local); /* destroi struct localizacao */
         if (b[i]->espera)
            fila_destroi(b[i]->espera); /* destroi fila de espera */
         if (b[i]->habilidades)
            cjto_destroi(b[i]->habilidades); /* destroi cjto de habilidades */
         free(b[i]); /* libera ponteiro para essa base b[i] */
      }
   }
   free(b); /* libera vetor */
}

/* Calcula a distancia ate a base destino
 * Eh usado distancia de pontos/raio de circunferencia */
int distancia_a_base(struct base *b, struct local *d){
   int r, n1, n2;
   n1 = b->local->x - d->x;  
   n2 = b->local->y - d->y;
   r = sqrt((n1*n1 + n2*n2));
   return r;
}

/* Retorna o ID identificação da base */
int indentifica_base(struct base *b){
   if (!b)
      return -1;
   return b->ID;
}

/* Testa capacidade da base 
 * Retorna numero de herois na base */
int testa_capcdd(struct cjto_t *p){
   if (!p)
      return -1;
   int tam = cjto_card(p);
   return tam;
}

/* Retorna o numero de herois na fila de espera
 *  ou -1 em caso de erro */
int tam_espera(struct base *b){
   if (!b)
      return -1;
   int tam = fila_tamanho(b->espera);
	return tam;
}

/* Lista os herois que estam na base */
void lista_presentes(struct base *b){
   if (!b)
      return;
   /* Imprime os herois presentes na base b */
   printf("HEROIS NA BASE %d [ ", b->ID);
   cjto_imprime(b->presentes);
   printf(" ]\n");
}

/* Testa se heroi quer entrar na espera 
 * espera = (paciencia de H ) > (10 * tam da fila na base) */
int testa_espera(struct base *b, struct heroi *h){
   int espera;
   
   espera = h->paciencia - 10 * tam_espera(b);
   return espera;
}

/* Retira o primeiro heroi da espera pois liberou espaco na base */
struct heroi *sai_espera(struct base *b){ 
   /* Retira o primeiro "item" da espera */
   void *item = fila_retira(b->espera);
   if (!item)
      return NULL;
   /* Faz um cast para struct heroi */
   struct heroi *h = (struct heroi *)(item);
   return h;
}

/* Remove heroi da base, retirando-o da lista de presentes 
 * e recalcula as habilidades possuidas pela base */
void sai_base(struct base *b, int id_heroi, struct mundo *m){
   if (!b || !m)
      return;
   /* Retira heroi dos presentes se esta neles */
   if (cjto_pertence (b->presentes, id_heroi))
      cjto_retira (b->presentes, id_heroi);  
   /* Recalcula as habilidades que a base possui */
   calcula_habilidades_base(b, m);
}

/* Atualiza habilidaes da base 
 * Destroi o conjunto atual de habilidades e 
 * recalcula as habilidades da base */
void calcula_habilidades_base(struct base *b, struct mundo *m){
   if (!b || !m)
      return;
   
   /* Destroi conjunto antigo */
   if (b->habilidades) {
      cjto_destroi(b->habilidades);
      b->habilidades = NULL;
   }
   /* Cria novo conjunto sem elementos */
   b->habilidades = cjto_cria(m->NHabilidades);
   
   /* Percorre o mundo testando se o heroi pertence a base */
   for (int i = 0; i < m->NHerois; i++){
      if (m->herois[i]){
         /* se o heroi existe e pertence eh criado um 
          * novo conjunto a partir da uniao dos outros */
         if (cjto_pertence(b->presentes, m->herois[i]->ID)) 
            uni_habilidades(b, m->herois[i]->habilidades); /* add habilidades do heroi a base */
      }
   }
}

/* Chega na base e tenta entrar, caso nao consigo entra na lista de espera */
int chega_base(struct base *b, struct heroi *h){
   
   /* Entra na espera direto pois existe vaga e a fila esta vazia*/
   if (cjto_card(b->presentes) < b->tam && tam_espera(b) == 0)
      return 0;
   
   /* Entra na espera pois tem paciencia suficiente para aguardar */
   if (testa_espera(b, h) > 0)
      return 0;

   /* Desiste da espera */
   return 1;
}

/* Retorna posicao da base */
struct local *pos_base(struct base *b){
   /* Garante que existam */
   if (!b || !b->local)
      return NULL;
   return b->local;
}

/* Sorteia uma base aleatoria 
 * usa a funcao de aleatorio para 
 * sortear uma posicao no vetor de base */
int base_aleatoria(int NBases){
   int ramdom = aleat(0, NBases -1);
   return ramdom;
}

/* Atualiza os herois na base */
void entra_base(struct base *b, struct heroi *h){
   if (!b || !h)
      return;
   if (!b->presentes)
      return;
   /* Entra na base */
   cjto_insere(b->presentes, h->ID);
   h->base = b->ID;
   uni_habilidades(b, h->habilidades);
}

/* Uniao das habilidades do heroi com a da base b */
void uni_habilidades(struct base *b, struct cjto_t *h_habilidades){
   if (!b || !h_habilidades)
      return;
   /* cria um conjunto uniao */
   struct cjto_t *novo = cjto_uniao(b->habilidades, h_habilidades);
   /* destroi conjunto antigo */
   cjto_destroi(b->habilidades);
   b->habilidades = novo;
}

/* Entra na fila de espera e porteiro e avisado para verificar fila */
void entra_espera(struct base *b, struct heroi *h){
   if (!b || !h)
      return;
   if (!b->espera)
      return;
   
   fila_insere(b->espera, (void *)h); 
}

/* Encontra base no mundo , recebe o ID da base */
struct base *encontra_base_mundo(int id_base, struct mundo *m){
   if(!m || id_base < 0 || id_base >= m->NBases)
      return NULL;
   return m->bases[id_base];
}

/* Imprime estatistica da base */
void estatistica_base(struct base *b){
   printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", b->ID, b->tam, b->maxFILA, b->missoes);
}



