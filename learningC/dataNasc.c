#include <stdio.h>

int main() {
    int dia, mes, ano, idade;

    scanf("%d %d %d",&dia, &mes, &ano);
    idade = 2021 - ano;
    if (mes > 4) 
        printf("%d\n",idade - 1);
    else if (mes < 4)
	printf("%d\n",idade);
    else if (dia > 29)
	printf("%d\n",idade - 1);
    else printf("%d\n",idade);
}
   
