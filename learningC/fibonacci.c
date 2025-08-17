#include <stdio.h> 

int main() { 
   int n, ant = 1, atual = 1, aux, i;
 
   scanf("%d",&n);
   printf("%d", ant);
   
   if (n > 1) {
	for (i = 1; i < n; i++) {
		printf(", %d", atual);
		aux = ant + atual;
		ant = atual;
		atual = aux;
	}
    }
   
   printf("\n");
   
   return 0;
}
