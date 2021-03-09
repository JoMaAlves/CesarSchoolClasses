#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento{
	struct elemento *prox;
	int valor;
};

void empilhar(struct elemento *ultimo){
	struct elemento *novo;
	novo = malloc(sizeof(struct elemento));
	scanf("%d",&novo->valor);
	novo->prox = ultimo->prox;
	ultimo->prox = novo;
}

void imprimir(struct elemento *ultimo){
	struct elemento *print;
	print = ultimo;
	while(1){
		print = print->prox;
		if(print->prox==NULL){
			printf("%d\n",print->valor);
			break;
		}
		printf("%d ",print->valor);
	}
}

void desempilhar(struct elemento *ultimo){
	struct elemento *out,*nlast;
	out = ultimo->prox;
	nlast = out->prox;
	ultimo->prox = nlast;
	free(out);
}


int main(){
	struct elemento ultimo;
	ultimo.prox = NULL;
	char a[12];

	while(1){
		scanf("%s",a);
		if(strcmp(a,"Empilhar") == 0) empilhar(&ultimo);
		else if(strcmp(a,"Imprimir") == 0) imprimir(&ultimo);
		else if(strcmp(a,"Desempilhar") == 0) desempilhar(&ultimo);
		else if(strcmp(a,"Finalizar") == 0) break;
	}
	return 0;
}