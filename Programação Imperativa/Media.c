#include <stdio.h>

int main(){
	float total;
	float n;
	float media;
	float final;
	char resposta;
	int cont;

	printf("Digite a sua nota da 1VA:\n");
	scanf("%f",&n);

	if (n < 0){
			printf("Nota da Seg chamada:\n");
			scanf("%f", &n);
		cont = cont++;
	}
	total = total + n;
	n = 0;


	printf("Digite a sua nota da 2VA:\n");
	scanf("%f",&n);

	if (n < 0 && cont < 1){
			printf("Nota da Seg chamada:\n");
			scanf("%f", &n);
		cont = cont++;
	}
	total = total + n;
	n = 0;

	printf("Digite a sua nota da 3VA:\n");
	scanf("%f",&n);

	if (n < 0 && cont < 1){
			printf("Nota da Seg chamada:\n");
			scanf("%f", &n);
		cont = cont++;
	}
	total = total + n;
	n = 0;

	media = total / 3;

	

	if (media < 7 ){
		printf("Você vai para final!");
		printf("Nota da final:\n");
		scanf("%f", final);
		if (final >= 7){
			printf("Você passou!");
			return 0;
		}
		else{
			printf("Você não passou!");
			return 0;
		}
		
	}

	else{
		printf("Você passou com media %f\n", media);
		return 0;
	}
}