// programa principal do projeto "The Boys - 2025/2"
// Autor: Nathalie, GRR 20253518

#include <stdio.h>
#include <stdlib.h>
#include "extras/fprio.h"
#include "extras/fila.h"
#include "extras/conjunto.h"
#include "entidades/herois.h"
#include "entidades/base.h"
#include "eventos/evento.h"
#include "eventos/missao.h"
#include "entidades/mundo.h"

/* programa principal */
int main ()
{  /* Cria o mundo */
   struct mundo *terra = cria_mundo(); 
   
   /* Inicia os campos do mundo */
   inicia_mundo(terra); 

   /* Executa simulacao do mundo */
   return simula_mundo(terra);
}

