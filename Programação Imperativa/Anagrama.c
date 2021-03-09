#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar(char *p1,char *p2){
	char *pos1, *pos2, *chec;
	int a,b,c,cont=0;
	int repet=0;
	int repet2=0;

	pos1 = p1;
	pos2 = p2;
	chec = p1;

	for(a=0;a!=strlen(p1);a++){
		for(c=0;c!=strlen(p1);c++){
			if (chec[c]==pos1[a]){
				repet++;
			}
		}
		for(b=0;b!=strlen(p2);b++){
			if(pos2[b]==pos1[a]){
				repet2++;
			}
		}
		if (repet!=repet2) break;
		cont++;
	}
	return cont;
}

int main(int argc,char *argv[]){
	if (argc == 2){
		printf("0");
		return -1;
	}
	int a = strlen(argv[1]);
	int b = strlen(argv[2]);
	int resulta;
	if (a==b){
		resulta = comparar(argv[1],argv[2]);
		if (resulta != strlen(argv[1])){
			printf("0");
			return 0;
		}
		else if(resulta==strlen(argv[1])){
			printf("1");
			return 0;
		}
	}
	else{
		printf("0");
		return 0;
	}
}