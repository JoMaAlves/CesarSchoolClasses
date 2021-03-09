#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap (int *p, int *q)
{
	int t;

	t = *p;
	*p = *q;
	*q = t;
}


void selectionsort(int array[], int n) //n = tamanho do array
{
	int i, j, min_index;

	for(i=0; i < n-1; i++)
	{
		min_index = i;

		for(j = i+1; j < n; j++)
		{
			if (array[j] < array[min_index])
			{
				min_index = j;
			}
		}
		swap(&array[min_index], &array[i]);
	}
}


void main()
{
	clock_t Start, End; 
	double Total_Time;
	Start = clock();

	int array[] = {};                //Colocar números
	int tamanho = sizeof(array)/sizeof(int);
	
	selectionsort(array, tamanho);
	
	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	End = clock();
	Total_Time = (double)(End - Start) / CLOCKS_PER_SEC;
	printf("Tempo: %f s", Total_Time);
}