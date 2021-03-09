#include <stdio.h>

int main(){
	int casos,conta;
	int a,b,c,e;
	int config[200][2];

	c = 0;

	scanf("%d",&casos);
	int numeros[casos][200];
	while(c!=casos){
		a = 0;
		scanf("%d %d",&config[c][0],&config[c][1]);

		while(a != config[c][1]){
			scanf("%d",&numeros[c][a]);
			a++;
		}
		c++;
	}
	c = 0;
	while(c!=casos){
		int hash[200][200]={};
		for(b=0;b!=config[c][1];b++){
			a = 0;
			conta = numeros[c][b] % config[c][0];
			while((hash[conta][a]) > 0){
				a++;
				}
				hash[conta][a] = numeros[c][b];


		}

		for(e=0;e!=config[c][0];e++){
			a = 1;
			if (hash[e][0] <= 0){
				printf("%d -> \\\n",e);
			}
			else{
				printf("%d -> %d",e,hash[e][0]);
					while(hash[e][a] > 0){
						if(hash[e][a]<=0){
							break;
						}
						printf(" -> %d",hash[e][a]);
						a++;
					}
				printf(" -> \\\n");
			}
		}
	if(casos-1==c){
		break;
    }
	printf("\n");
  c++;
	}
	return 0;
}