//Multiplicação de Matrizes
#include <stdio.h>

int main(){
	int a,b,c,d,e,f;

	int matriz1[3][3]={{2,6,6},
					   {3,5,6},
					   {4,7,2}};

	int matriz2[3][3]={{1,6,3},
					   {7,4,8},
					   {8,7,2}};

	int matrizf[3][3]={};

	for(a = 0; a != 3; a++){
		for(b = 0;b != 3; b++){
			for(c=0; c!=3; c++){
				d = d + matriz1[a][c] * matriz2[c][b];
			}
		matrizf[a][b] = d;
		d=0;
		}
	}
	for(e=0;e!=3;e++){
		for(f=0;f!=3;f++){
			printf("%d\t",matrizf[e][f]);
		}
		printf("\n");
		f=0;
	}

}