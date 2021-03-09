#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int lista[] = {};
	int len = sizeof(lista)/sizeof(int);
	int swap,teste;
	
	for(int a = 1;a<len;a++){
		swap = lista[a];
		teste = a - 1;
		while(lista[teste] > swap && teste >= 0){	
			lista[teste + 1] = lista[teste];
			teste = teste - 1;
		}
		lista[teste+1] = swap;
	}
	
	for (int i = 0; i < len; i++)
	{
		printf("%d ", lista[i]);
	}

	printf("\n");

	//~Google-sensei conta o tempo
	clock_t Ticks[2];
	Ticks[0] = clock();
	Ticks[1] = clock();

	double Time = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	printf("Tempo: %g ms", Time);
	return 0;
}