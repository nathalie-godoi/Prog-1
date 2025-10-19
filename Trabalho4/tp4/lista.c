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

/* Cria uma lista, devolvendo ponteiro para ela */
struct lista *lista_cria (){
   struct lista *listaN;
   listaN = malloc(sizeof(struct lista));
   
   /* Se a lista nao foi alocada retorna NULL */
   if (listaN == NULL)
      return NULL;

   /* Inicializa a lista */
   listaN->ini = NULL;
   listaN->ptr = NULL;
   listaN->tamanho = 0;
   
   /* Retorna ponteiro para a lista criada */
   return listaN;
}

/* Destroi lista */
void lista_destroi (struct lista **lista){
   /* Se a lista nao foi alocada retorna */
   if (lista == NULL || *lista == NULL)
      return;
   
   /* Cria ponteiros auxiliares */
   struct nodo *atual = (*lista)->ini;
   struct nodo *prox;
   
   /* Enquanto nao chegar no fim da lista desaloca nodos */ 
   while (atual != NULL){
      prox = atual->prox; /* Guarda prox nodo */
      free(atual); /* Desaloca nodo atual */
      atual = prox; /* Vai para prox nodo */
   }
   
   /* Libera o ponteiro da lista */
   free(*lista);
   *lista = NULL;
}

/* Insere elemento no inicio da lista */
int lista_insere_inicio (struct lista *lista, int chave){
   /* Lista nao alocada retorna 0 */
   if (lista == NULL)
      return 0;
   
   struct nodo *novo = malloc(sizeof(struct nodo));

   /* Testa se o ponteiro foi alocado */
   if (novo == NULL)
      return 0;
   
   /* Insere elemento */
   novo->chave = chave;
   novo->prox = lista->ini;
   lista->ini = novo;

   /* Aumenta tamanho da lista */  
   lista->tamanho++; 

   /* Retorna 1, sucesso */
   return 1;
}

/* Insere elemento no fim */
int lista_insere_fim (struct lista *lista, int chave){
   /* Lista nao alocada retorna 0 */
   if (lista == NULL)
      return 0;

   struct nodo *novo = malloc(sizeof(struct nodo));
   
   /* Testa se o ponteiro foi alocado */
   if (novo == NULL)
      return 0;
   
   /* Inicializa elemento */
   novo->chave = chave;
   novo->prox = NULL;
   
   /* Lista vazia, insere no inicio */
   if (lista->tamanho == 0)
      lista->ini = novo;
   else {
      lista_inicia_iterador(lista);

      /* Enquanto nao chegou no fim incrementa iterador */
      while (lista->ptr->prox != NULL)
         lista_incrementa_iterador(lista, NULL); 
      
      /* Adiciona elemento no final */
      lista->ptr->prox = novo;
   }

   /* Aumenta tamanho da lista */
   lista->tamanho++;
   return 1;
}

/* Insere elemento ordenado */
int lista_insere_ordenado (struct lista *lista, int chave){
   /* Lista nao alocada retorna 0 */
   if (lista == NULL)
      return 0;

   struct nodo *novo = malloc(sizeof(struct nodo));
   
   /* Ponteiro nao alocado retorna 0 */ 
   if (novo == NULL)
      return 0;

   /* Inicializa novo elemento */
   novo->chave = chave;
   novo->prox = NULL;
   
   /* Se a lista for vazia ou chave for menor que valor 
    * do inicio,  adiciona elemento no inicio da lista */
   if (lista->ini == NULL || lista->ini->chave >= chave){
      novo->prox = lista->ini;
      lista->ini = novo;
      lista->tamanho++;
      return 1;
   }
   
/* Outros casos: Insere elemento no meio ou no fim da lista */
   lista_inicia_iterador(lista);

   /* Enquanto nao chegar no fim da lista e a chave ainda
    * for maior incrementa iterador */
   while(lista->ptr->prox != NULL && lista->ptr->prox->chave < chave)
      lista_incrementa_iterador(lista, NULL);

   /* Adiciona elemento na posição correta */
   novo->prox = lista->ptr->prox;
   lista->ptr->prox = novo;
   lista->tamanho++;
   return 1;
}

/* Remove elemento do inicio */
int lista_remove_inicio (struct lista *lista, int *chave){
  /* Lista nao alocada retorna 0 */
  if (lista == NULL)
      return 0;
   
   /* Lista vazia, sem elementos */
   if (lista->ini == NULL)
      return 0;
   
   /* Remove elemento do inicio */
   struct nodo *temp = lista->ini;
   *chave = temp->chave; /* Retorna a chave no parametro */
   lista->ini = temp->prox; /* Corrige inicio */
   free(temp); /* Libera elemento do inicio */
   lista->tamanho--; /* Decrementa tamanho da lista */
   return 1;
}

/* Remove elemento do fim da lista */
int lista_remove_fim (struct lista *lista, int *chave){
   /* Lista nao alocada retorna 0 */
   if (lista == NULL)
      return 0;
   /* Lista vazia, sem elementos */
   if (lista->ini == NULL)
      return 0;
   
   /* Se tamanho = 0 remove do inicio */
   if (lista->tamanho == 1){
      *chave = lista->ini->chave;
      free(lista->ini);
      lista->ini = NULL;
      lista->tamanho--;
      return 1;
   }
   
   /* Inicia o iterador */
   lista_inicia_iterador(lista);
   
   /* Percorre a lista ate alcancar o fim */
   while (lista->ptr->prox->prox != NULL)
      lista_incrementa_iterador(lista, NULL);
   
   struct nodo *ultimo = lista->ptr->prox;
   /* Passa valor da chave no parametro */
   if (chave != NULL)
        *chave = ultimo->chave; 

   /* Remove fim */
   lista->ptr->prox = NULL; /* Penultimo elemento aponta para NULL */
   free(ultimo); /* Libera ultimo elemento */
   lista->tamanho--; /* Reduz tamanho da lista */
   return 1;
}

/* Remove elemento ordenado */
int lista_remove_ordenado (struct lista *lista, int chave){
   /* Caso a lista nao esteja alocado retorna 0 */
   if (lista == NULL )
      return 0;
   
   /* Se a lista nao tem elementos retorna 0 */
   if (lista->ini == NULL)
      return 0;
   
   struct nodo *atual = lista->ini;
   struct nodo *anterior = NULL;
   
   /* Encontra chave na lista */ 
   while(atual != NULL && atual->chave != chave){
      anterior = atual;
      atual = atual->prox;
   }
   
   /* Caso a lista seja vazia */
   if (anterior == NULL) 
      lista->ini = atual->prox;
   else
      anterior->prox = atual->prox;
  
   /* Libera elemento atual e reduz tamanho da lista */
   free(atual); 
   lista->tamanho--; 

   return 1;
}

/* Retorna 1 se a lista esta vazia */
int lista_vazia (struct lista *lista){
   /* Se a lista nao foi alocada retorna 1 */
   if (lista == NULL)
      return 1;
   
   /* Retorna 0 se a lista esta vazia */
   if (lista->ini == NULL && lista->tamanho == 0)
      return 1;
   
   return 0;
}

/* Passa tamanho da lista */
int lista_tamanho (struct lista *lista){
   /* Se a lista nao foi alocado retorna 0*/
   if (lista == NULL)
      return 0;
   /* Retorna tamanho da lista */
   return lista->tamanho;
}

/* Testa se um elemento pertence ah lista */
int lista_pertence (struct lista *lista, int chave){
   /* Se a lista nao foi alocado retorna 0*/
   if (lista == NULL)
      return 0;
   
   /* Lista sem elementos */
   if (lista_tamanho(lista) == 0)
      return 0;
   
   /* Inicia iterador */
   lista_inicia_iterador(lista);
   int valor;
   
   /* Percorre a lista até encontrar o valor, retornando 1 */
   while(lista_incrementa_iterador(lista, &valor))
      if (chave == valor)
         return 1;

   /* Retorna 0, pois percorreu toda a lista e nao achou o valor */
   return 0;
}

/* Inicia iterador */
void lista_inicia_iterador (struct lista *lista){
   /* Se a lista foi alocada inicia iterador */
   if (lista != NULL)
      lista->ptr = lista->ini;
}

/* Incrementa iterador */
int lista_incrementa_iterador (struct lista *lista, int *chave){
   /* Lista nao alocada retorna 0 */
   if (lista == NULL)
      return 0;
   
   /* Se o ptr atual eh NULL retorna 0 */
   if (lista->ptr == NULL)
      return 0;
   
   /* Se a chave existe retorna-a no parametro */
   if (chave != NULL)
      *chave = lista->ptr->chave;
   
   /* Incrementa iterador */
   lista->ptr = lista->ptr->prox;

   return 1;
}
