#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento{
   struct elemento *prox;
   int item;
};

struct elemento fim;

void additem(struct elemento *inicio,int a){
	struct elemento *novo;
	novo = malloc(sizeof(struct elemento));
	scanf("%d",&novo->item);
	novo->prox = NULL;
	if(!a){
		inicio->prox = novo;
		fim.prox = novo;
	}
	else{
		fim.prox->prox = novo;
		fim.prox = novo;	
	}
}

void fora(struct elemento *primeiro,int valor){
	struct elemento *antes, *depois,*out;
	antes = primeiro;
	depois = antes->prox;
	while(depois->item!=valor){
		antes = antes->prox;
		depois = depois->prox;
	}
	out = depois;
	depois = depois->prox;
	free(out);
	antes->prox = depois;
}


int main(){
	struct elemento *print;
	struct elemento inicio;
	inicio.prox = NULL;
	
	int a,b;
	int tamanho,retira;
	
	scanf("%d",&tamanho);
	for(a=0;a!=tamanho;a++){
		additem(&inicio,a);
	}
	scanf("%d",&retira);
	for(a=0;a!=retira;a++){
		scanf("%d",&b);
		fora(&inicio,b);
	}

	print = &inicio;
	while(1){
		print = print->prox;
		if(print->prox==NULL){
			printf("%d",print->item);
			break;
		}
		printf("%d ",print->item);
	}
	return 0;
}