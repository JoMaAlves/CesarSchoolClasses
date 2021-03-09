#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//========================= FOLHA =========================

struct folha{
	int info, height;
	struct folha *dir, *esq, *pai;
};

//========================= ALTURA =========================

int altura(struct folha *raiz){
	if (raiz == NULL) return (0);
	else return (raiz->height);
}

void attAltura(struct folha *raiz){
	int alt_dir,alt_esq;
	if (raiz != NULL){
		alt_dir = altura(raiz->dir);
		alt_esq = altura(raiz->esq);
		if(alt_dir > alt_esq) raiz->height = alt_dir + 1;
		else if (alt_esq > alt_dir) raiz->height = alt_esq + 1;
	}

}

//========================= ROTAÇÕES =========================

struct folha *rotaçãoEsq(struct folha *raiz){
	struct folha *aux;

	aux = malloc(sizeof(struct folha));
	aux = raiz->dir;
	raiz->dir = aux->esq;
	aux->esq = raiz;
	aux->pai = raiz->pai;
	raiz->pai = aux;
	raiz->dir->pai = raiz;
	attAltura(raiz->esq);
	attAltura(raiz);
	return (aux);
}

struct folha *rotaçãoDir(struct folha *raiz){
	struct folha *aux;

	aux = malloc(sizeof(struct folha));
	aux = raiz->esq;
	raiz->esq = aux->dir;
	aux->dir = raiz;
	aux->pai = raiz->pai;
	raiz->pai = aux;
	raiz->esq->pai = raiz;
	attAltura(raiz->dir);
	attAltura(raiz);
	return (aux);
}

struct folha *rotaçãoDuplaEsq(struct folha *raiz){
	struct folha *result;

	result = malloc(sizeof(struct folha));
	raiz->dir = rotaçãoDir(raiz->dir);
	result = rotaçãoEsq(raiz);
	return(result);
}

struct folha *rotaçãoDuplaDir(struct folha *raiz){
	struct folha *result;

	result = malloc(sizeof(struct folha));
	raiz->esq = rotaçãoEsq(raiz->esq);
	result = rotaçãoDir(raiz);
	return(result);
}

//========================= CHECAGEM =========================

void check(int number){
}

//========================= AÇÕES =========================

struct folha *addleaf(int number){
	struct folha *novo;
	novo = malloc(sizeof(struct folha));
	novo->pai = NULL;
	novo->dir = NULL;
	novo->esq = NULL;
	novo->info = number;
	novo->height = -1;
	return (novo);
}

//========================= ARVORE =========================

int addtreeAVL(int number,struct folha *raiz){
	if (raiz == NULL){
		raiz = addleaf(number);
	}
	else{
		if (number < raiz->info){
			addtreeAVL(number,raiz->esq);
			if ( (altura(raiz->esq)) - (altura(raiz->dir)) == 2 ){
				if (number < raiz->esq->info) rotaçãoDir(raiz);
				else rotaçãoDuplaDir(raiz);
				return 0;
			}
			return 0;
		}
		else{
			addtreeAVL(number,raiz->dir);
			if ((altura(raiz->dir)) - (altura(raiz->esq)) == 2){
				if (number > raiz->dir->info) rotaçãoEsq(raiz);
				else rotaçãoDuplaEsq(raiz);
				return 0;
			}
			return 0;
		}
		attAltura(raiz);
	}
	return 0;
}

//========================= MAIN =========================

int main(){
	struct folha *raiz;
	int a,caso,number;
	scanf("%d",&a);
	for(int b=0;b!=a;b++){
		scanf("%d",&caso);
		scanf("%d",&number);
		if(caso == 1){
      addtreeAVL(number,raiz);
    }
		else if (caso == 2) check(number);
		else break;
	}
	return 0;
}