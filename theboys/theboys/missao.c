#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "fila.h"
#include "conjunto.h"
#include "herois.h"
#include "base.h"
#include "evento.h"
#include "missao.h"
#include "mundo.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*            Especifica Conjunto de Funcoes para MISSAO              */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Criar missoes com pos e habillidades necessarias aleatorias */
struct missao *cria_missao(int n){
   struct missao *mi = malloc(sizeof(struct missao));

   if (!mi)
      return NULL;
   /* Inicializacao da missao */
   mi->ID = n;
   mi->habilidades = cjto_aleat(aleat(6, 10), 10); /* cjto aleatorio com 6 a 10 elementos de 0 10 */
   mi->local = local_aleat(); /* localizao aleatoria */
   mi->status = 0;
   mi->tentativas = 0;
   return mi;
};

/* Destroi missao */
void destroi_missoes(struct missao **m){
   if (!m)
      return;
   for(int i = 0; i < N_MISSOES; i++){
      if (m[i]){
         if (m[i]->habilidades)
            cjto_destroi(m[i]->habilidades); /* destroi cjto de hab */
         if (m[i]->local)
            destroi_local(m[i]->local); /* destroi struct local */
         free(m[i]); /* destroi missao */
      }
   }
   free(m); /* destroi vetor */
};

/* Retorna o ponteiro para a missao ou NULL em caso de erro */
struct missao *encontra_missao_mundo(int id_missao, struct mundo *m){
   if (!m || id_missao < 0)
      return NULL; // missao ou mundo nao existem

   if (id_missao >= m->NMissoes)
      return NULL; // missao nao existe
   
   struct missao *missao = m->missoes[id_missao];
   if (!missao)
      return NULL;
   return missao;
}

/* Incrementa quantidade de missoes concluidas pela base B 
 * e atualiza status da missao para concluida (1) */
void completa_missao(struct missao *m, struct base *b){
   if (!m || !b)
      return;
   (b->missoes) = (b->missoes) + 1;
   (m->status) = 1;
}

/* Testa se os herois possuem habi necesaarias pra missao 
 * Retorna 1 se sim e 0 se nao possuem */
int tenta_missao(struct missao *m, struct base *b){
   if (!b || !m)
      return 0;
   /* testa se a base b contem as habs precisas */
   if (cjto_contem (b->habilidades, m->habilidades) == 1)
      return 1;
   return 0;
}

/* Procura a base mais prox para realizar a missao */
struct base *prox_missao(struct missao *missao, struct mundo *mundo){
    struct base *b_prox;
    int menor = mundo->dimensao->x + mundo->dimensao->y; // tam do mapa 

    /* o ponteiro b_prox aponta pra base mais proxima */
    for(int i = 0; i < mundo->NBases; i++){
       int d = distancia_a_base(mundo->bases[i], missao->local);
       if (d < menor){
          menor = d;
          b_prox = mundo->bases[i];
       }
    }
    return b_prox;
}

/* Imprime o satus da missao apos conclusao */
void imprime_missao_completa(int tempo, int id_missao, struct base *b){
   printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, id_missao, b->ID);
   cjto_imprime(b->habilidades); // Imprime todas as habilidades dos herois da base
   printf(" ]\n");
}

/* Adia a missao pois nao eh possivel concluila */
void adia_missao(int tempo, struct missao *missao, struct mundo *mundo){
   /* Imprime status da missao */
   printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, missao->ID);
   missao->tentativas = missao->tentativas + 1;
   
   cria_evento(tempo + 24*60, -1, missao->ID, MISSAO, mundo);
}

/* Testa se o heroi pode usar o composto
 * TA = 2500 * n , ou seja, 2500 deve ser divisivil por 2500. 
 * Retorna 1 se eh divisil e 0 caso contrario */
int testa_CompostoV(struct mundo *m){
   if (m->Relogio % 2500 == 0)
      return 1;
   return 0;
}

/* Usa composto V, da as habilidades necessarias ao heroi */
void usa_compostoV(struct heroi *h, struct missao *missao, struct mundo *mundo){
   /* União entre habilidades necessarias para missao e habilidades do heroi */
   struct cjto_t *habilidades_novas = cjto_uniao(missao->habilidades, h->habilidades);
   struct cjto_t *aux = h->habilidades;

   /* heroi ganha novas habilidades */
   h->habilidades = habilidades_novas;

   /* Desaloca estruturas auxiliares */
   cjto_destroi(aux);
   /* Diminui qntd de compostos V disponivies no mundo */
   diminui_compostosV(mundo);
   printf("HEROI %2d USOU COMPOSTOV NA MISSAO %2d\n", h->ID, missao->ID);
}

/* Retorna qntd de compostos V disponiveis */ 
int qntd_CompostosV(struct mundo *m){
   return m->NCompostosV;
}

/* Diminui qntd de compostos V disponiveis */
void diminui_compostosV(struct mundo *m){
   m->NCompostosV = (m->NCompostosV) - 1;
}

/* Imprime as estatisticas da missao */
void estatistica_missao(struct mundo *m){
   int missoes_completas = 0;
   int min = m->missoes[0]->tentativas, max = 0, media = 0;
   
   /* calcula a menor, o maximo e a media das tentativas em missoes 
    * e a quantidade de missoes completas */
   for (int i = 0; i < m->NMissoes; i++){
      if (m->missoes[i]){
         if (m->missoes[i]->tentativas < min)
            min = m->missoes[i]->tentativas;
         if (m->missoes[i]->tentativas > max)
            max = m->missoes[i]->tentativas;
         if (m->missoes[i]->status == 1)
            missoes_completas++;
         media+= m->missoes[i]->tentativas;
      }
   };
   
   /* transforma em float o resultado */
   float qnts, MEDIA, mortalidade = 0;
   qnts = ((float)missoes_completas/m->NMissoes) * 100;
   MEDIA =((float)media /m->NMissoes);

   /* Calcula mortalidade */
   for (int i = 0; i < m->NHerois; i++)
      if (m->herois[i] && m->herois[i]->vivo == 0)
         mortalidade++;
   
   /* Imprime estatisticas extras */
   mortalidade = (mortalidade/ (float)m->NHerois) * 100;
   printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", missoes_completas, m->NMissoes, qnts);
   printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min, max, MEDIA);
   printf("TAXA MORTALIDADE: %.1f%%\n", mortalidade);
   printf("COMPOSTOS V USADOS: %d\n", N_COMPOSTOS_V - m->NCompostosV);
}
