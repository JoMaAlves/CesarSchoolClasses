#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=========================== LEAF ===========================

struct folha{
	int info, height;
	struct folha *dir, *esq, *pai;
};

struct folha *raiz;

//========================= ADDFOLHA =========================

struct folha *addleaf(int number){
	struct folha *novo;
	novo = malloc(sizeof(struct folha));
	novo->pai = NULL;
	novo->dir = NULL;
	novo->esq = NULL;
	novo->info = number;
	novo->height = 1;
	return (novo);
}

//========================== ALTURA ==========================

int altura(struct folha *position){
	if (position == NULL) return 0;
	else return (position->height);
}

void attAltura(struct folha *position){
	int alt_dir,alt_esq;
	if (position != NULL){
		alt_dir = altura(position->dir);
		alt_esq = altura(position->esq);
		if(alt_dir > alt_esq) position->height = alt_dir + 1;
		else if (alt_dir < alt_esq) position->height = alt_esq + 1;
		else if (alt_dir == alt_esq) position->height = alt_dir + 1;
	}
}

//========================= ORGANIZA =========================

void organiza(struct folha *root,struct folha *help){
	while(1){
		if (help->info < root->info){
			if(root->esq == NULL){
				root->esq = help;
				help->pai = root;
				break;
			}
			else root = root->esq;
		}
		else{
			if (root->dir == NULL){
				root->dir = help;
				help->pai = root;
				break;
			}
			else root = root->dir;
		}
	}
}

//========================= ROTAÇÕES =========================

struct folha *rotaçãoEsq(struct folha *root){
	struct folha *aux;

	aux = root->dir;
	root->dir = aux->esq;
	aux->esq = root;
	if (root->pai != NULL) aux->pai = root->pai;
	else {
		raiz = aux;
		aux->pai = root->pai;
	}
	root->pai = aux;
	root->dir->pai = root;
	return (aux);
}

struct folha *rotaçãoDir(struct folha *root){
	struct folha *aux;

	aux = root->esq;
	root->esq = aux->dir;
	aux->dir = root;
	if (root->pai != NULL) aux->pai = root->pai;
	else {
		raiz = aux;
		aux->pai = root->pai;
	}
	root->pai = aux;
	root->esq->pai = root;
	return (aux);
}

struct folha *rotaçãoDuplaEsq(struct folha *root){
	struct folha *result;

	root->dir = rotaçãoDir(root->dir);
	result = rotaçãoEsq(root);
	return(result);
}

struct folha *rotaçãoDuplaDir(struct folha *root){
	struct folha *result;

	root->esq = rotaçãoEsq(root->esq);
	result = rotaçãoDir(root);
	return(result);
}

//========================= POSIÇOES =========================



//========================== ARVORE ==========================

int addtreeAVL(int number, int b){
	struct folha *ajudante,*alfred;
	
	if (!b) raiz = addleaf(number);
	
	else{
		ajudante = addleaf(number);
		organiza(raiz,ajudante);
		alfred = ajudante;

		while(ajudante != NULL){
			if ( ajudante->esq->height - ajudante->dir->height >= 2 ){
				if (alfred->info < ajudante->esq->info) rotaçãoDir(ajudante);
				else rotaçãoDuplaDir(ajudante);
			}
			else if (ajudante->dir->height - ajudante->esq->height >= 2){
				if (alfred->info > ajudante->dir->info) rotaçãoEsq(ajudante);
				else rotaçãoDuplaEsq(ajudante);
			}
			attAltura(ajudante);
			ajudante = ajudante->pai;
		}
	}
	return 0;
}

//========================= CHECAGEM =========================

//Não to conseguindo corrigir as rotações


//=========================== MAIN ===========================

int main(){
	int a,caso,number;
	scanf("%d",&a);
	for(int b=0;b!=a;b++){
		scanf("%d",&caso);
		scanf("%d",&number);
		if(caso == 1) addtreeAVL(number,b);
		else if (caso == 2) check(number);
		else break;
	}
	return 0;
}