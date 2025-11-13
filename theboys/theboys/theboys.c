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
{  /* Cria o mundo */
   struct mundo *terra = cria_mundo(); 
   
   /* Inicia os campos do mundo */
   inicia_mundo(terra); 

   /* Executa simulacao do mundo */
   return simula_mundo(terra);
}

