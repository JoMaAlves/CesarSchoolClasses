#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

//===========================[FUNCTIONS]=============================
void staPrint(int choice, int student, int chair,int remainingChairs);
void * studentActions(void *arg);
void * taActions(void * arg);
//===================================================================

//=============================[GLOBAL]==============================
int chairQuantUsed = 0;
int chair[3] = {0,0,0};
int next_seat = 0;
int stdQuant;
int staSleeping = 0;
pthread_mutex_t mutex;
sem_t chairs[3];
sem_t sleeping;
sem_t class;
//===================================================================



//===================================================================
//=============================[ MAIN ]==============================
//===================================================================

int main(int argc, char *argv[]){
    int quant = atoi(argv[1]);
    
    pthread_t student[quant];
    pthread_t sleepingTA;
    
    //INICIALIZE THE TA FIRST, SO HE CAN GET THE NUMBER OF STUDENTS
    pthread_create(&sleepingTA, NULL, taActions, &quant);

    sem_init(&class, 0, 0);
    sem_init(&sleeping, 0, 0);
    for(int i = 0; i< 3; i++)
        sem_init(&chairs[i], 0, 0);

    //IDENTIFIES THE STUDENTS
    int ids[quant];
    for(int i = 0; i < quant; i++) 
        ids[i] = i+1;

    //INICIALIZES THE STUDENTS
    for (int i = 0; i < quant; i++)
        pthread_create(&student[i], NULL, studentActions, &ids[i]);
    
    
    //THE ONLY THREAD THAT NEEDS JOIN IS TA'S, HE ALWAYS WILL BE THE LAST TO FINISH
    pthread_join(sleepingTA, NULL);
    staPrint(11, 0, 0, 0);
    return 0;
}

//===================================================================
//===================================================================
//===================================================================


//===================================================================
//============================[STUDENT]==============================
//===================================================================

void * studentActions(void *arg)
{
    int id = * (int *) arg;
    int position;
    int quant;
    while(1)
    {
        sleep(rand() % 10);
        staPrint(5, id, 0, 0);

        //FIRST CASE, SLEEP
        if(staSleeping){
            staSleeping = 0;
            sem_post(&sleeping);
            staPrint(6, id, 0, 0);

            staPrint(7, id, 0, 0);
            staPrint(3, id, 0, 0);

            sleep(5);
            
            staPrint(4, id, 0, 0);
            staPrint(8, id, 0, 0);

            sem_post(&class);
            stdQuant--;
            break;
        }
        //SECOND CASE, CHAIRS
        else
        {
            //LOCK
            pthread_mutex_lock(&mutex);
            if(chairQuantUsed == 3)
            {
                pthread_mutex_unlock(&mutex);
                //UNLOCK
                staPrint(9, id, 0, 0);
                continue;
            }
            else
            {
                chairQuantUsed++;
                quant = chairQuantUsed;
                position = next_seat;
                chair[position] = 1;
                next_seat++;
                if(next_seat == 3) next_seat = 0;
                pthread_mutex_unlock(&mutex);
                //UNLOCK

                staPrint(10, id, position+1, 3-quant);
                
                //WAIT FOR CLASS
                sem_wait(&chairs[position]);
                
                //DURING CLASS
                pthread_mutex_lock(&mutex);
                chairQuantUsed--;
                chair[position] == 0;
                pthread_mutex_unlock(&mutex);

                staPrint(7, id, 0, 0);
                staPrint(3, id, 0, 0);

                sleep(5);

                staPrint(4, id, 0, 0);
                staPrint(8, id, 0, 0);

                sem_post(&class);
                stdQuant--;
                break;
                //END CLASS
            }
        }
    }    
    return NULL;
}

//===================================================================
//===================================================================
//===================================================================

//===================================================================
//==============================[ TA ]===============================
//===================================================================

void * taActions(void * arg){
    staPrint(1, 0, 0, 0);
    stdQuant = * (int *) arg;
    
    while(1){
        if(stdQuant == 0) break;
        staSleeping = 1;
        sem_wait(&sleeping);
        sem_wait(&class);
        while(1)
        {
            //CASE NO ONE IS THERE, GO TO SLEEP
            if(chairQuantUsed == 0)
            {
                staPrint(2, 0, 0, 0);
                break;
            }
            //IF THERE IS, TEACH THEM
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    if(stdQuant == 0) break;
                    if(chair[i] == 1)
                    {
                        sem_post(&chairs[i]);
                        sem_wait(&class);
                    }                
                }
            }
            if(stdQuant == 0) continue; //CHECK FOR THE EXISTENCE OF STUDENTS
        }
        if(stdQuant == 0) break;
    }
    return NULL;
}

//===================================================================
//===================================================================
//===================================================================

//===================================================================
//=============================[PRINTS]==============================
//===================================================================

void staPrint(int choice, int student, int chair,int remainingChairs){
    switch(choice){
        case 1:
            printf("TA is sleeping.\n");
            break;
        case 2:
            printf("TA went back to sleep.\n");
            break;
        case 3:
            printf("TA is teaching student #%d.\n", student);
            break;
        case 4:
            printf("TA finished teaching student #%d.\n", student);
            break;
        case 5:
            printf("Student #%d is going to TA room.\n", student);
            break;
        case 6:
            printf("Student #%d is awaking the TA.\n", student);
            break;
        case 7:
            printf("Student #%d is getting inside TA room.\n", student);
            break;
        case 8:
            printf("Student #%d left TA room.\n", student);
            break;
        case 9:
            printf("There is no available chair to student #%d. The student will return late.\n", student);
            break;
        case 10:
            printf("Student #%d sat on chair #%d. #%d chair(s) remain.\n", student, chair, remainingChairs);
            break;
        case 11:
            printf("There is no more students to help. TA left the room\n");
            break;
    }
}
//===================================================================
//===================================================================
//===================================================================