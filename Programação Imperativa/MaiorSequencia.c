#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    int savedValue = 0;
    int inifim[2];

    for(int i = 1; i < argc; i++){
        //printf("I: %d\n", i);
        
        for(int j = (argc - 1); j >= i; j--)
        {
            int soma = 0;
            //printf("J: %d\n", j);
            
            for(int k = j; k >= i; k--)
            {
                //printf("K: %d\t", k);
                int valor = atoi(argv[k]);
                soma += valor;
            }
            
            if (soma > savedValue) 
            {
                savedValue = soma;
                inifim[0] = i;
                inifim[1] = j;
            }
            //printf("savedValue: %d\n", savedValue);
        }
        
    }
    for(int i = inifim[0]; i <= inifim[1];i++) printf("%s\t", argv[i]);
    printf("\n");
    printf("%d\n", savedValue);
    
    return 0;
}