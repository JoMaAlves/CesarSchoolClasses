#include <stdio.h>
#include <stdlib.h>

int len(FILE* fp);
int** getMatrix(char* file);
void printMatrix(int** matrix);


//==================[MAIN]===============

int main(int argc,char* argv[]) {

	int** matrix = getMatrix(argv[1]);

	printMatrix(matrix);

	return 0;
}


//=========[FUNCOES]=================

int len(FILE* fp) {

	char c;
	int count = 0;

	rewind(fp);

	for (c = getc(fp); c != EOF; c = getc(fp)) {

		if (c == '\n')
			count += 1;
	}

	return count;
}


int** getMatrix(char* file) {

	FILE *fp;
	char letra[100];
	int size;

	fp = fopen(file, "r");

	size = len(fp);


	int** matrix = malloc(sizeof(int*) * size);

	for(int i = 0; i < size;i++)
		matrix[i] = malloc(sizeof(int) * size);



	int i = 0;
	int j = 0;
	rewind(fp);


	for(int i = 0; i < size;i++) {
		for(int j = 0;j < size;j++) {
			fscanf(fp,"%s",letra);
			matrix[i][j] = atoi(letra);
		}
	}

	return matrix;
}

void printMatrix(int** matrix) {

	for(int i = 0; i < 3;i++) {
		for(int j = 0;j < 3;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}