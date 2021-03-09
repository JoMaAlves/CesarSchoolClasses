#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void insertionsort(int array[], int n)
{
    int i, j, joker; //joker é número que muda de posição, acho que sim né

    for(i = 1; i < n; i++)
    {
        joker = array[i]; 

        j = i-1;

        while (j >= 0 && joker < array[j])
        {
            array[j+1] = array[j]; //move joker para direita.

            j--;
        }

        array[j+1] = joker;
    }
}


void main()
{
	clock_t Start, End; 
	double Total_Time;
	Start = clock();

	int array[] = {};                //Colocar números
	int tamanho = sizeof(array)/sizeof(int);
	
	insertionsort(array, tamanho);
	
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	End = clock();
	Total_Time = (double)(End - Start) / CLOCKS_PER_SEC;
	printf("Tempo: %f s", Total_Time);
}