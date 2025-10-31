// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

/* Cria uma fila vazia. */
struct fprio_t *fprio_cria (){
   struct fprio_t *fila = malloc(sizeof(struct fprio_t));
   /* Testa se fila foi alocada */
   if (fila == NULL)
      return NULL;

   /* Inicializa fprio */ 
   fila->prim = NULL;
   fila->num = 0;
   
   /* Retorna ponteiro */
   return fila;
}

/* Libera todas as estruturas de dados da fila, inclusive os itens. */
struct fprio_t *fprio_destroi (struct fprio_t *f){
   /* Fila nao alocada */
   if (f == NULL)
      return NULL;
   
   struct fpnodo_t *atual, *prox;
   atual = f->prim;

   /* Desaloca nodos */
   while(atual != NULL){
      prox = atual->prox;
      if(atual->item)
         free(atual->item);
      free(atual);
      atual = prox;
   }
    
   /* Libera fprio */
   free(f);
   f = NULL;
   return NULL;
}

/* Insere o item na fila, mantendo-a ordenada por prioridades crescentes. */
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
   /* Ponteiro NULL */
   if (f == NULL)
      return -1;
   
   /* Item NULL */
   if (item == NULL)
      return -1;

   struct fpnodo_t *atual = f->prim;
   /* Garante que o novo item nao existe na fprio */
   while (atual != NULL) {
      if (atual->item == item)
         return -1; // ERRO
      atual = atual->prox;
   }

   /* Aloca novo nodo */
   struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
   
   /* Nao conseguiu alocar */
   if (novo == NULL)
      return -1;
   
   /* Inicializa nodo */   
   novo->item = item;
   novo->tipo = tipo;
   novo->prio = prio;
   novo->prox = NULL;

   atual = f->prim;
   struct fpnodo_t *ant = NULL;
   /* Encontra pos pro nodo */
   while(atual != NULL && atual->prio <= prio){
      ant = atual;
      atual = atual->prox;
   }
   // while(atual != NULL && atual->prio == prio){
   //    ant = atual;
   //    atual = atual->prox;
   // }
   
   if (ant == NULL){
      novo->prox = f->prim;
      f->prim = novo;
   }
   else {
      /* Adiciona nodo na pos correta */
      novo->prox = ant->prox;
      ant->prox = novo;
   }
   f->num = f->num + 1; 
   return f->num;
}

/* Retira o primeiro item da fila e o devolve; o tipo e a prioridade */
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
   /* Lista nao alocada */
   if (f == NULL || f->num == 0)
      return NULL;
   if (f->prim == NULL)
      return NULL;
   /* Remove nodo */
   struct fpnodo_t *prim = f->prim;
   void *item_re = prim->item;
   if (tipo == NULL) // Retorna NULL erro 
      return NULL;
   *tipo = prim->tipo;
   if (prio == NULL) // Retorna se o ponteiro passado eh valido
      return NULL;
   *prio = prim->prio;
   f->prim = prim->prox;
   free(prim);
   (f->num)--;
   return item_re;
}

/* Informa o número de itens na fila. */
int fprio_tamanho (struct fprio_t *f){
   /* Testa se fila foi alocada */
   if (f == NULL)
      return -1;
   
   /* Erro */
   if (f->num < 0)
      return -1;
   
   /* Retorna qntd de elementos na fila */
   return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f){
   if (f == NULL)
      return;
   struct fpnodo_t *aux = f->prim;
   /* Fila vazia */
   if (aux == NULL)
      return;
   /* Imprime fila com fprio > 1 */
   while (aux->prox != NULL){
      printf("(%d %d) ", aux->tipo, aux->prio);
      aux = aux->prox;
   }
   /* Imprime ultimo elemento */
   printf("(%d %d)", aux->tipo, aux->prio);
}
