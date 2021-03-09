#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int ierr;
    ierr = MPI_Init(&argc,&argv);
    printf("Hello World\n");

    ierr = MPI_Finaliize();
    return 0;
}