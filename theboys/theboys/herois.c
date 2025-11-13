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


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*               Funcoes usadas e disponiveis para os herois              */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Cria um ponteiro para struct heroi */ 
struct heroi *cria_heroi(){
   struct heroi *h = malloc(sizeof(struct heroi));
   /* Testa se foi possivel alocar */
   if (!h)
      return NULL;
   return h;
}

/* Inicia heroi e suas caracteristicas */
void inicia_heroi(struct heroi *h, int qntd_h){
   if (!h)
      return;
   h->ID = qntd_h;
   h->exp = 0;
   h->paciencia = aleat(0, 100);
   h->velo = aleat(50, 5000);
   h->habilidades = cjto_aleat(aleat(1, 3), 10); // Conjunto de 1 a 3 elementos de 0..10
   h->base = -1; // SEM BASE  
   h->vivo = 1; // VIVO
}

/* Destroi os vetor de pontiros para herois */
void destroi_herois(struct heroi **h){
   /* Ponteiro nao existe */
   if (!h)
      return;
   /* Percorre e desaloca os herois */
   for(int i = 0; i < N_HEROIS; i++){
      if (h[i]){
         if (h[i]->habilidades)
            cjto_destroi(h[i]->habilidades); // Libera conjunto de habilidades
         free(h[i]);
      }
   }
   free(h);
}

/* Heroi morre, atualiza seu status para 0 */
void heroi_morre(struct mundo *m, int id_heroi){
   if (!m)
      return;
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   /* heroi morre = 0 */ 
   if (h)
      h->vivo = 0;
}

/* Calcula permanencia
 * tpm = 15 + paciencia * numero aleatorio */
int calcula_permanencia(struct heroi *h){
   if (!h)
      return -1; // Erro
   int p;   
   p = 15 + h->paciencia * aleat(1, 20);
   return p;
}

/* Atualiza experiencia apos concluir missao */
void atualiza_exp(struct heroi *h){
   if (h)
      h->exp += 7;
}

/* Retorna velocidade do heroi */
int velo_heroi(struct heroi *h){
   if (!h)
      return -1; // ERRO
   return h->velo;
}

/* Retorna experiencia atual do heroi h */
int exp_heroi(struct heroi *h){
   if (!h)
      return -1; //ERRO
   return h->exp;
}

/* Retorna ponteiro para o heroi mais experiente */
struct heroi *heroiExp(struct base *b, struct mundo *mundo){
   int exp = -1, id_heroi = - 1;
   struct heroi *aux;

   /* Procura heroi no mundo, testando se pertence ao conjunto */
   for(int i = 0; i < mundo->NHerois; i++){
      if (cjto_pertence(b->presentes, i)){
	      /* caso pertenca testa se sua experiencia eh maior*/
         aux = encontra_heroi_mundo(i, mundo);
         if (aux && aux->exp > exp){
         exp = aux->exp;
         id_heroi = i;
         }
      }
   }
   /* Encontra heroi mais experiente */
   if (id_heroi != -1){
      aux = encontra_heroi_mundo(id_heroi, mundo);
      return aux;
   }
   /* nao encontrou / nao existe */
   return NULL; 
}

/* Encontra heroi no mundo e retorna seu ponteiro */
struct heroi *encontra_heroi_mundo(int id_heroi, struct mundo *m){
   /* Garente que seja possivel encontrar o heroi */
   if (!m || !m->herois || id_heroi < 0 || id_heroi >= m->NHerois)
      return NULL;
   struct heroi *h = m->herois[id_heroi];
   if (h)
      return h;
   
   /* heroi nao existe */
   return NULL;
}

/* Aumenta a experiencia de todos os herois que participaram da missao */
void aumenta_XP_herois(struct mundo *m, struct base *b){
   /* Garante que o mundo, herois, e base existam */
   if (!m) 
      return;
   if (!m->herois || !b)
      return;
   
   /* Procura os herois da base b e aumenta suas experiencias */
   for (int i = 0; i < m->NHerois; i++){
      if (cjto_pertence(b->presentes, i) == 1)
         if (m->herois[i])
            atualiza_exp(m->herois[i]);
   }
}

/* Atualiza a base do heroi */
void atualiza_base_heroi(struct heroi *h, int id_base){
   /* heroi nao existe */
   if (!h)
      return;
   h->base = id_base;
}

/* Retorna o ID (identificacao) da base do heroi */
int base_heroi(struct heroi *h){
   if (!h)
      return -1; // ERRO
   return h->base;
}

/* Mostra estatistica do heroi */
void estatistica_heroi(struct heroi *h){
   /* heroi existe e esta vivo */
   if (h && h->vivo)
      printf("HEROI %2d VIVO PAC %3d VELO %4d EXP %4d HABS [ ", h->ID, h->paciencia, h->velo, h->exp);
   else 
      /* heroi existe mas esta morto */
      if (h)
         printf("HEROI %2d MORTO PAC %3d VELO %4d EXP %4d HABS [ ", h->ID, h->paciencia, h->velo, h->exp);
   else 
      return;
   /* Imprime habilidades do heroi */
   cjto_imprime(h->habilidades);
   printf(" ]\n");
}
