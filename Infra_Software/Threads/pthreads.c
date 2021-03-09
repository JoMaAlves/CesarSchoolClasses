#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mu;

void* myturn(void * arg){
    
    pthread_mutex_lock(&mu);
    for(int i = 0; i < 8; i++){
        sleep(1);
        printf("My turn!\n");
    }
    pthread_mutex_unlock(&mu);
    
    printf("dance");
    return NULL;
}

void yourturn(){
    for(int i = 0; i < 3; i++){
        sleep(2);
        printf("Your turn!\n");
    }
}

int main(){
    pthread_t newthread;  //Declare a new thread
    pthread_t bla;
    pthread_create(&newthread, NULL, myturn, NULL);
    pthread_create(&bla, NULL, myturn, NULL);
    //myturn();
    //yourturn();
    pthread_join(newthread, NULL);
    pthread_join(bla, NULL);
    return 0;
}

