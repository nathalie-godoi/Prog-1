#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "herois.h"
#include "conjunto.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*              Especifica Conjunto de Funcoes para FILA              */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

struct fila_nodo_t;
struct fila_t;
struct heroi;

/* Cria uma fila e a incializa
 * Retorna ponteiro ou NULL em erro */
struct fila_t *fila_cria (){
   struct fila_t *fila;
   fila = malloc(sizeof(struct fila_t));

   if (!fila)
      return NULL;
   
   fila->prim = NULL;
   fila->fim = NULL;
   fila->num = 0;

   return fila;
}

/* Nao libera os ponteiros para o item 
 * para nao ocorrer double free herois */
struct fila_t *fila_destroi (struct fila_t *f){
   if (!f)
      return NULL;
   
   struct fila_nodo_t *atual = f->prim;
   struct fila_nodo_t *segt;
   
   while (atual != NULL){
      segt = atual->prox;
      free(atual);
      atual = segt;
   }

   free(f);
   return NULL;
}

/* Insere no final da fila o item 
 * Eh criado um nodo para isso 
 * Itens repetidos nao sao adicionados */
int fila_insere (struct fila_t *f, void *item){
   /* Fila nao existe */
   if (!f)
      return -1;

   /* Item NULL */
   if (!item)
      return -1;
 
   struct fila_nodo_t *atual = f->prim;
   /* Garante que o novo item nao existe na fprio */
   while (atual != NULL) {
      if (atual->item == item)
         return -1; // ERRO
      atual = atual->prox;
   }

   struct fila_nodo_t *novo = malloc(sizeof(struct fila_nodo_t));
   if (!novo)
      return -1;
   
   /* Inicializacao */
   novo->prox = NULL;
   novo->item = item;
   
   /* Fila vazia */
   if (!f->prim){
      f->fim = novo;
      f->prim = novo;
   }
   /* Adiciona no fim da fila */
   else {
   f->fim->prox = novo;
   novo->prox = NULL;
   f->fim = novo;
   }
   f->num++;
   return 1;
}

/* Retira primeiro nodo da fila 
 * Retorna o ponteiro pra o item */
void *fila_retira (struct fila_t *f){
   /* Fila nao existe */
   if (!f)
      return NULL;
   /* Fila vazia */ 
   if (f->num == 0 || f->prim == NULL)
      return NULL;
   
   struct fila_nodo_t *temp = f->prim;
   void *item = temp->item;
   f->prim = f->prim->prox;
   /* Novo inicio = NULL atualiza fim */
   if (!f->prim)
      f->fim = NULL;
   
   f->num--;
   free(temp);
   
   return item;
}

/* Retorna o numero de nodos na fila
 * ou -1 em caso de erro */
int fila_tamanho (struct fila_t *f){
   /* Fila nao existe */
   if (!f)
      return -1;
   return f->num;
};


/* Imprime o conteúdo da fila
 * Nesse caso os ID dos herois */
void fila_imprime (struct fila_t *f){
   if (!f){
      printf("fila nao existe\n");
      return;
   }

   struct fila_nodo_t *atual = f->prim;

   while (atual != NULL){
      struct heroi *h = (struct heroi *)atual->item;

      if (h)
         printf("%d ", h->ID);
      else
         printf("HEROI NAO EXISTE\n");
      
      atual = atual->prox;
   }

}
