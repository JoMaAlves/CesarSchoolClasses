#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
        char str[80] = "This is - www.tutorialspoint.com - website";
        char s[2] = " ";
        char * token;

        token = strtok(str, s);

        while(token != NULL){
                printf("%s\n", token);

                token = strtok(NULL, s);
        }
}


        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                        printf("%d\t",maximum[i][j]);
                }
                printf("\n");
        }