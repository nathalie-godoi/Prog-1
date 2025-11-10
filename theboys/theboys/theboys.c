// programa principal do projeto "The Boys - 2025/2"
// Autor: Nathalie, GRR 20253518

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

/* programa principal */
int main ()
{
   struct mundo *terra = cria_mundo(); /* Cria o mundo */
   
   /* Inicia os campos do mundo */
   inicia_mundo(terra); 

   /* Inicia eventos iniciais */
   if (!eventos_iniciais(terra)){
      destroi_mundo(terra);
      free(terra);
      return 1;
   }
   
   /* Inicia simulacao retirando eventos da LEF */
   struct evento *evento_atual = remove_evento(terra->LEF);
   int NEventos = 0;
   while(evento_atual != NULL && evento_atual->tipo != FIM){ 
      processa_evento(terra, evento_atual);
      evento_atual = remove_evento(terra->LEF);
      NEventos++;
   }
   
   /* Evento atual fim do mundo */
   if (evento_atual!= NULL && evento_atual->tipo == FIM)
      processa_evento(terra, evento_atual);
   
   /* Finaliza simulacao destruindo o mundo e seus objetos */
   printf("EVENTOS TRATADOS: %d\n", NEventos);
   free(terra);
   return 0;
}

