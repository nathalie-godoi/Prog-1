#include "lista.h"
#include <stdlib.h>

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
   struct lista *listaN;
   listaN = malloc(sizeof(struct lista));

   if (listaN == NULL)
      return NULL;
   
   listaN->ini = NULL;
   listaN->ptr = NULL;
   listaN->tamanho = 0;

   return listaN;
}

void lista_destroi (struct lista **lista){
   if (lista == NULL || *lista == NULL)
      return;
   
   struct nodo *atual = (*lista)->ini;
   struct nodo *segt;
   
   while (atual != NULL){
      segt = atual->prox;
      free(atual);
      atual = segt;
   }

   free(*lista);
   *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
   if (lista == NULL)
      return 0;

   struct nodo *novo = malloc(sizeof(struct nodo));
   if (novo == NULL)
      return 0;
   
   novo->chave = chave;
   novo->prox = lista->ini;
   lista->ini = novo;
   lista->tamanho++;
   return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
   if (lista == NULL)
      return 0;

   struct nodo *novo = malloc(sizeof(struct nodo));

   if (novo == NULL)
      return 0;
   
   novo->chave = chave;
   novo->prox = NULL;
   
   if (lista->tamanho == 0)
      lista->ini = novo;
   else {
      lista_inicia_iterador(lista);
   
      while (lista->ptr->prox != NULL)
         lista->ptr = lista->ptr->prox; 
   
      lista->ptr->prox = novo;
   }

   lista->tamanho++;
   return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
   if (lista == NULL)
      return 0;

   struct nodo *novo = malloc(sizeof(struct nodo));
    
   if (novo == NULL)
      return 0;
  
   novo->chave = chave;
   novo->prox = NULL;
   
   if (lista->ini == NULL || lista->ini->chave >= chave){
      novo->prox = lista->ini;
      lista->ini = novo;
      lista->tamanho++;
      return 1;
   }

   lista_inicia_iterador(lista);
   
   struct nodo *anterior = NULL;

   while(lista->ptr != NULL && lista->ptr->chave < chave){
      anterior = lista->ptr;
      lista_incrementa_iterador(lista, NULL);
   }

   novo->prox = lista->ptr;
   anterior->prox = novo;
   lista->tamanho++;
   return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
   if (lista == NULL)
      return 0;
   
   if (lista->ini == NULL)
      return 0;
   
   struct nodo *temp = lista->ini;
   *chave = temp->chave;
   lista->ini = temp->prox;
   free(temp);
   lista->tamanho--;
   return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
   if (lista == NULL)
      return 0;
   if (lista->ini == NULL)
      return 0;
   
   if (lista->tamanho == 1){
      *chave = lista->ini->chave;
      free(lista->ini);
      lista->ini = NULL;
      lista->tamanho--;
      return 1;
   }

   lista_inicia_iterador(lista);
   struct nodo *anterior = NULL;
   
   while (lista->ptr->prox != NULL){
      anterior = lista->ptr;
      lista_incrementa_iterador(lista, chave);
   }
   
   *chave = lista->ptr->chave;
   free(lista->ptr);
   anterior->prox = NULL;
   lista->tamanho--;
   return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
   if (lista == NULL )
      return 0;

   if (lista->ini == NULL)
      return 0;
  
   struct nodo *atual = lista->ini;
   struct nodo *anterior = NULL;
   
   while(atual != NULL && atual->chave != chave){
      anterior = atual;
      atual = atual->prox;
   }
   
   if (anterior == NULL) 
      lista->ini = atual->prox;
   else
      anterior->prox = atual->prox;
   
   free(atual);
   lista->tamanho--;

   return 1;
}

int lista_vazia (struct lista *lista){
   if (lista == NULL)
      return 1;

   if (lista->ini == NULL && lista->tamanho == 0)
      return 1;
   
   return 0;
}

int lista_tamanho (struct lista *lista){
   if (lista == NULL)
      return 0;
   return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
   if (lista == NULL)
      return 0;

   lista_inicia_iterador(lista);
   int valor;
   
   while(lista_incrementa_iterador(lista, &valor))
      if (chave == valor)
         return 1;
   return 0;
}

void lista_inicia_iterador (struct lista *lista){
   if (lista != NULL)
      lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
   if (lista == NULL)
      return 0;

   if (lista->ptr == NULL)
      return 0;
   if (chave != NULL)
      *chave = lista->ptr->chave;
   
   lista->ptr = lista->ptr->prox;

   return 1;
}
