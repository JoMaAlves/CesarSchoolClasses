#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct folhas{
	int num;
	struct folhas *right;
	struct folhas *left;
	struct folhas *pai;
};

struct folhas *first;

struct folhas *addleaf(int number){
	struct folhas *novo;

	
	novo = malloc(sizeof(struct folhas));
	novo->pai = NULL;
	novo->right = NULL;
	novo->left = NULL;
	novo->num = number;
	return (novo);
}

int addTree(int b){
	struct folhas *ajudante,*check;
	int number;
	scanf("%d",&number);
	if(!b){
		first = addleaf(number);
		return 0;
	}
	check = first;
	ajudante = addleaf(number);
	while(1){
		if(ajudante->num <= check->num){
			if (check->left == NULL) {
				check->left = ajudante;
				ajudante->pai = check;
				break;
			}
			else check = check->left;
		}
		else{
			if(check->right == NULL) {
				check->right = ajudante;
				ajudante->pai = check;
				break;
			}
			else check = check->right;
		}
	}
	return 0;
}
void preordem(){
	struct folhas *print;
	print = first;
	printf("Pre.: ");
	printf("%d",print->num);
	while(1){
		if(print->left != NULL){
			while(print->left != NULL){
				printf(" %d",print->left->num);
				print = print->left;
			}
		}
		if(print->right != NULL){
			while(print->right != NULL){
				printf(" %d",print->right->num);
				print = print->right;
			}
		}
	}

}

void imprimir(int b){
	printf("Case %d",b);
	preordem();
}


int main(){

	int casos,quant;
	scanf("%d",&casos);

	for(int a=0;a!=casos;a++){
		scanf("%d",&quant);
		for(int b=0;b!=quant;b++){
			addTree(b);
		}
		imprimir(a);
	}
}