#include <stdio.h>
#include <stdlib.h>
//OpenMP header
#include <omp.h>

int main(int argc, char* argv[]){

    //Beginning of parallel region 
    #pragma omp parallel
    {
        //Parallel region code
        printf("Hello World... from thread = %d\n", omp_get_thread_num());
    }
    return 0;
}