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
/*              Especifica Conjunto de Funcoes para EVENTO            */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/* Inicia os eventos inciais: 
 * Ex: Criação de herois e de missão 
 * Retorna 1 em caso de sucesso ou 0 erro*/
int eventos_iniciais(struct mundo *mundo){
   /* mundo ou lista de eventos nao existem */
   if (!mundo || !mundo->LEF)
      return 0;
   
   /* Cria eventos de chegada de herois em bases aleatorias */
   for (int i = 0; i < mundo->NHerois; i++){
      int id_base = base_aleatoria(mundo->NBases); // Base aleatoria
      int tempo = aleat(0,4230); // Tempo aleatório nos 3 primeiros dias
      cria_evento(tempo, i, id_base, CHEGA, mundo); // cria evento chega
   }
    
   /* Cria as missoes com posicoes e tempos aleatorios pelo mundo */
   for (int i = 0; i < mundo->NMissoes; i++){
      int tempo = aleat(0, T_FIM_DO_MUNDO); // Do inicio e antes do fim do mundo
      cria_evento(tempo, -1, i, MISSAO, mundo); // cria evento missao
   }
   
   programa_fim(mundo);
   return 1;
}

/* Cria um evento e o adiciona na LEF respeitando a prioridade:
 * O Tipo eh a especificacao do evento a ser processado */
void cria_evento(int tempo, int id_heroi, int ID, int tipo, struct mundo *mundo){
   if (!mundo || !mundo->LEF) 
      return;
   if (tempo > T_FIM_DO_MUNDO)
      return;

   //printf("EVENTO %c NO TEMPO %d\n", tipo, tempo);
   struct evento *e = malloc(sizeof(struct evento));
   if (!e)
      return;
   e->data = tempo;
   e->tipo = tipo;
   e->heroi = id_heroi;
   e->ID = ID;
   
   add_LEF(mundo->LEF, e);
}

/* Destroi evento desalocando seu ponteiro */
void destroi_evento(struct evento *e){
   if (!e)
      return;
   free(e);
}
   
/* Add evento na LEF respeitando horario/data */
void add_LEF(struct fprio_t *LEF, struct evento *novo){
   fprio_insere(LEF, (void *)novo, 1, novo->data);
}

/* Tira o evento pra executa-lo */
struct evento *remove_evento(struct fprio_t *LEF){
   int tempo, tipo;
   struct evento *e = (struct evento * )(fprio_retira(LEF, &tipo, &tempo));
   /* Acabou eventos ou evento nao existe */
   if (!e)
      return NULL;
   return e;
}

/* Processa um evento baseado no seu tipo :
 * tipo = 's' evento sai, tipo = 'm' evento missao */
void processa_evento(struct mundo *m, struct evento *e){
   /* Evento nao existe ou mundo ou lista de eventos nao existem */ 
   if (!e || !m || !m->LEF)
      return; // Erro
   /* Atualiza horario do mundo */
   m->Relogio = e->data;
   
   /* Decide qual evento sera executado */
   switch (e->tipo) {
      case CHEGA:
         chega(e->data, e->heroi, e->ID, m);
         break; // chega
      case ESPERA:
         espera(e->data, e->heroi, e->ID, m);
         break; // espera - wait
      case SAI: 
         sai(e->data, e->heroi, e->ID, m);
         break; // sai
      case DESISTE: 
         desiste(e->data, e->heroi, e->ID, m);
         break; // desite
      case AVISA:
         avisa(e->data, e->ID, m);
         break; // avisa
      case ENTRA: 
         entra(e->data, e->heroi, e->ID, m);
         break; // entra
      case VIAJA: 
         viaja(e->data, e->heroi, e->ID, m);
         break; // viaja
      case MORRE:
         morre(e->data, e->heroi, e->ID, m);
         break; // morre - die
      case MISSAO:
         missao(e->data, e->ID, m);
         break; // missao
      case FIM: 
         fim(e->data, m);
         break; // fim
   }

   destroi_evento(e);
}

/* Processa o evento CHEGA */
void chega(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Procura o heroi e base no mundo */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   struct base *b = encontra_base_mundo(id_base, m);
   
   /* Nao encontrou base ou heroi */
   if (!h || !b){
      printf("BASE OU HEROI NAO EXISTEM\n"); 
      return;
   }
   /* Heroi esta morto */
   if (!h->vivo) 
      return;

   /* Atualiza base de H */
   atualiza_base_heroi(h, id_base);
   
   /* calcula a decisao do heroi ao chegar na base e a qntd de presentes nela */
   int decisao_heroi = chega_base(b,h);
   int qntd_presentes = cjto_card(b->presentes);
   printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ", tempo, h->ID, b->ID, qntd_presentes, b->tam);

   /* decide se o heroi espera ou desiste */
   switch (decisao_heroi) {
      case 0:
         printf("ESPERA\n");
         cria_evento(tempo, id_heroi, id_base, ESPERA, m); // entra na espera
         break;
      case 1:
         printf("DESISTE\n");
         cria_evento(tempo, id_heroi, id_base, DESISTE, m); // nao espera
      break;
   }
}

/* Processa o evento ESPERA */
void espera(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Procura o heroi e base no mundo */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   struct base *b = encontra_base_mundo(id_base, m);
   /* base ou heroi nao existem */
   if (!b || !h){
      printf("BASE OU HEROI NAO EXISTEM\n");
      return;
   }
   /* heroi esta morto */
   if (!h->vivo)
      return;  
   
   /* Insere o heroi no final da fila de espera */
   entra_espera(b, h);
   
   /* tam da espera desconsiderando o heroi */
   int tam_espera = fila_tamanho(b->espera) -1; 
   printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, tam_espera);
   cria_evento(tempo, -1, id_base, AVISA, m); //  evento avisa
}

/* Processa o evento DESISTE */
void desiste(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Procura o heroi e base no mundo */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   struct base *b = encontra_base_mundo(id_base, m);
   /* heroi ou base nao existem */
   if (!b || !h){
      printf("BASE OU HEROI NAO EXISTEM\n");
      return;
   }
   /* heroi esta morto */
   if (!h->vivo)
      return;

   printf("%6d: DESIST HEROI %2d BASE %d\n", tempo, id_heroi, id_base);
   int nova_base = base_aleatoria(m->NBases);

   cria_evento(tempo, id_heroi, nova_base, VIAJA, m); // evento viaja
}

/* Processa o evento AVISA */
void avisa (int tempo, int id_base, struct mundo *m){
   /* Procura base no mundo */
   struct base *b = encontra_base_mundo(id_base, m);
   /* base nao existe */
   if (!b){
      printf("BASE NAO EXISTE\n");
      return;
   }
   
   /* calcula tam da espera e dos presentes */
   int espera = fila_tamanho(b->espera);
   int presentes = cjto_card(b->presentes);
   
   /* Atualiza o maior tamanho da espera nessa base */
   if (b->maxFILA < espera)
      b->maxFILA = espera;
   
   /* Imprime lista de espera */
   printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, id_base, presentes, b->tam);
   fila_imprime(b->espera);
   printf("]\n");
   
   /* Adiciona herois da espera na base se houver vaga */
   while((b->tam > presentes) && espera > 0){
      /* Retira heroi da lista de espera e o adiciona na base */
      struct heroi *h = sai_espera(b);
      
      /* Se heroi existe e esta vivo entra base */
      if (h && h->vivo){
         entra_base(b, h, m);  
         printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, h->ID);   
         cria_evento(tempo, h->ID, id_base, ENTRA, m); // evento entra
      }
      
      /* recalcula tam da espera e dos presentes */
      espera = fila_tamanho(b->espera);
      presentes = cjto_card(b->presentes);
   }
}

/* Processa o evento ENTRA */
void entra(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Procura o heroi e a base no mundo */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   struct base *b = encontra_base_mundo(id_base, m);
   /* base ou heroi nao existem */
   if (!b || !h){
      printf("BASE OU HEROI NAO EXISTEM\n");
      return;
   }
   /* Heroi esta morto */
   if (!h->vivo)
      return;

   /* Calcula temp de permanencia e cria evento de saida */
   int tpm = calcula_permanencia(h);
   int qntd_atual = cjto_card(b->presentes); // qtd de presentes na base b
   
   /* Imprime status do evento */
   printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, id_heroi, id_base, qntd_atual, b->tam, tempo + tpm);
   cria_evento(tempo + tpm, id_heroi, id_base, SAI, m);
}

/* Processa o evento SAI */
void sai(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Encontra base atual do heroi no mundo */
   struct base *b_atual = encontra_base_mundo(id_base, m);
   /* base nao existe */
   if (!b_atual){
      printf("BASE NAO EXISTE\n");
      return;
   }
   /* Procura se o heroi existe no mundo */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   /* heroi nao existe ou nao esta vivo */
   if (!h)
      return;
   if (!h->vivo)
      return;

   /* Retira heroi da base */
   sai_base(b_atual, id_heroi, m);
   
   /* Escolhe aleatoriamente uma nova base */
   int nova_base_id = base_aleatoria(m->NBases);
   int tam = cjto_card(b_atual->presentes);
   
   /* Imprime status do evento */
   printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, id_heroi, id_base, tam, b_atual->tam);
   cria_evento(tempo, id_heroi, nova_base_id, VIAJA, m); // evento viaja 
   cria_evento(tempo, -1, id_base, AVISA, m); // evento avisa - base anterior
}

/* Processa o evento VIAJA */
void viaja(int tempo, int id_heroi, int id_base, struct mundo *m){
   /* Encontra base e heroi */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   struct base *b_nova = encontra_base_mundo(id_base, m);
   /* base ou heroi nao existem */
   if (!b_nova || !h){
      printf("BASE OU HEROI NAO EXISTEM\n");
      return;
   }
   /* heroi esta morto */
   if (!h->vivo)
      return;

   /* encontra base anterior do heroi e testa se ela existe */
   struct base *b_ant = encontra_base_mundo(h->base, m);
   if (!b_ant){
      printf("BASE NAO EXISTE");
      return;
   }
   
   /* Calcula distancia entre as bases e duracao da viagem */
   int di = distancia_a_base(b_ant, b_nova->local);
   int duracao = di / h->velo;

   /* Imprime status do evento */
   printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, id_heroi, b_ant->ID, id_base, di, h->velo, tempo + duracao);
   cria_evento(tempo + duracao, id_heroi, id_base, CHEGA, m); // evento chega
}

/* Processa o evento MORRE */
void morre(int tempo, int id_heroi, int id_missao, struct mundo *m){
   /* Procura heroi e garante que exista */
   struct heroi *h = encontra_heroi_mundo(id_heroi, m);
   if (!h){
      printf("HEROI NAO EXISTE\n");
      return;
   }
   /* Procura base do heroi */
   struct base *b = encontra_base_mundo(h->base, m);
   /* Garante que a base exista */
   if (!b){
      printf("BASE NAO EXISTE\n");
      return;
   }
   
   /* retira o heroi da base b e heroi morre */
   sai_base(b, id_heroi, m); 
   heroi_morre(m, id_heroi);
   
   /* Imprime status do evento */
   printf("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, id_heroi, id_missao);
   cria_evento(tempo, -1, b->ID, AVISA, m); // evento aviso, liberou vaga na base
}

/* Processa o evento MISSAO */
void missao(int tempo, int id_missao, struct mundo *m){
   /* Procura missao no mundo e garante que exista */
   struct base *b; 
   struct missao *missao = encontra_missao_mundo(id_missao, m);
   if (!missao)
      return;

   /* Imprime status do evento missao */
   printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, id_missao, missao->tentativas);
   cjto_imprime(missao->habilidades);
   printf(" ]\n");
   
   /* Encontra base mais proxima da missao e testa se ela existe */
   b = prox_missao(missao, m);
   if (!b)  
      adia_missao(tempo, missao, m);

   /* Tenta concluir a missao */
   if (tenta_missao(missao, b)){
      /* se for possivel completa missao */
      completa_missao(missao, b);
      /* Imprime status da missao apos sua conclusao */
      imprime_missao_completa(tempo, id_missao, b);
      /* aumenta experiencia de todos os herois participante */
      aumenta_XP_herois(m,b);
   }
   /* Caso nao seja possivel concluir a missao tenta usar compostoV */
   else {
      if (testa_CompostoV(m) && qntd_CompostosV(m) > 0){  
         /* Procura heroi mais experiente na base */
         struct heroi *aux = heroiExp(b, m);
         if (aux && aux->vivo){
            /* Usa composto para adquirir habili necessarias e completa missao */
            usa_compostoV(aux, missao, m);
            completa_missao(missao, b);   
            
            /* Recalcula habilidades da base e imprime status da missao */
            calcula_habilidades_base(b,m); 
            imprime_missao_completa(tempo, id_missao, b);
            /* Atualiza experiencias dos outros heroi */
            aumenta_XP_herois(m,b);
            cria_evento(tempo, aux->ID, id_missao, MORRE, m); // evento morre
         }
         else 
            adia_missao(tempo, missao, m); // adia missao pois heroi nao existe
      }
      else 
         adia_missao(tempo, missao, m); // adia missao 
   }
}

/* Processa o evento FIM */
void fim (int tempo, struct mundo *mundo){
   printf("%6d: FIM\n", tempo);

   for(int i = 0; i < mundo->NHerois; i++)
      estatistica_heroi(mundo->herois[i]);

   for(int i = 0; i < mundo->NBases; i++)
      estatistica_base(mundo->bases[i]);
   
   estatistica_missao(mundo);
   
   destroi_mundo(mundo);
}
   
