#include <stdio.h>

int main(){
	int seq[10]={};
	int seqm[]={};
	int i,j,k,l,soma,maior,tamanho;
	float media;
	s = 0;
	tamanho = ((sizeof seqm)/sizeof(int));
	media = maior/tamanho;

	
	for(i=0;i!=10;i++){
		printf("Digite o %dº número:\n",i);
		scanf("%d", &seq[i-1]);
	}

	for(i=0;i!=10;i++){
		for(j=i;j!=10;j++){
			soma = soma + seq[j];
		}
		
		if(soma > maior){
			maior = soma;
			for(k=i,l=0; k!=10; k++,l++){
        		seqm[l] = seq[k];
    		}
		}
		
		else if(soma = maior){
			if( (soma/(10-i)) < media){
				maior = soma;
				
				for(k=i,l=0; k!=10; k++,l++){
        			seqm[l] = seq[k];
    			}
			}
		}
	}
	printf("A maior soma foi: %d\n",maior);
	printf("A sequencia foi:\n");
	for(l = 0; l != tamanho; l++){
		printf("%d",seqm[l]);
	}
}