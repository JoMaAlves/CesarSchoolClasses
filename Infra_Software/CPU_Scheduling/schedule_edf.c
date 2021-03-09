#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "list.h"

struct node *head = NULL;

//===============CITAÇÃO DE FUNÇÕES====================

void printExec(char **progs, int *timevalue, int quant);
void printMetric(char **progs, int *tatTime, int *waitTime, int *responseTime,int quant);
void add(char *name, int priority, int burst);
int getSize(struct node *head);
char **loc_matrix(int n);

//==================TERMINA AQUI=======================



























//========================================================
//=====FUNCAO PRINCIPAL QUE PEGA DADOS DOS PROCESSOS======
//========================================================

void schedule(){
    int size = getSize(head);

    char **names = loc_matrix(size);
    int *burstTimes = malloc(sizeof(int)*size);
    int *period = malloc(sizeof(int)*size);


    int *lostDeadLine = malloc(sizeof(int)*size);
    int *completeExec = malloc(sizeof(int)*size);
    int *killed = malloc(sizeof(int)*size);

    struct node *aux = head;
	struct node *aux_2 = head;

    int i = 0;
    int endtime;
    //COMECO A RODAR A LINKED LIST
    while(aux_2!=NULL){
        //UMA AUX VAI PERCORRENDO E COMPARANDO A PRIORIDADE COM A DA AUX_2, SE FOR MENOR, AUX_2 ASSUME ESSA POSIÇÃO
        if(aux->task->priority < aux_2->task->priority) aux_2 = aux;
        
        aux = aux->next;
        //TERMINOU DE PERCORRER AUX FICA NULL E AUX_2 FINALMENTE É USADA
        if(aux == NULL){
            if(names[i] == "TT"){ 
                endtime = aux_2->task->priority;
                break;
            }
            burstTimes[i] = aux_2->task->burst; //SALVO CADA BURST TIME NO ARRAY EM ORDEM
            names[i] = aux_2->task->name;//SALVO CADA NOME DE PROCESSO NO ARRAY EM ORDEM
            
            period = aux_2->task->priority;
            
            i++;
            aux = head;
            //run(aux_2->task, aux_2->task->burst);
            delete(&head, aux_2->task);
            aux_2 = head;
        }
    }

    int j = 0;
    int k = 0;
    while(j <= endtime){
        int addtime;
        addtime = burstTimes[k];

        if                
        

        j += addtime;
    }
 

    printExec(names, burstTimes, size);
	printMetric(names, tatTimes, waitingTimes, responseTimes, size);
}

//==================TERMINA AQUI=======================
































//==================================================
//=====FUNCAO QUE ADICIONA TASK NA LINKED LIST======
//==================================================

void add(char *name, int priority, int burst){
	Task *newTask = malloc(sizeof(Task));

	newTask->name = name;
	newTask->priority = priority;
	newTask->burst = burst;

	insert(&head, newTask);

}
//=============TERMINA AQUI========================



//============================================
//=====FUNCAO PRA PEGAR QNT DE PROCESSOS======
//============================================

int getSize(struct node *head){
	struct node *aux = head;
	int size=0;

	while(aux!=NULL){
		size++;
		aux = aux->next;
	}
	return size;

}
//=============TERMINA AQUI===================



//============================================
//=====FUNCAO PRA ALOCAR ARRAY DE STRINGS=====
//============================================
char **loc_matrix(int n){
  
  char **matrix = (char**)malloc(n*sizeof(char*));

  for(char i = 0; i < n; i++){
    if (matrix[i+1] == NULL) matrix[i] = "TT";
    matrix[i] = (char*)malloc(2*sizeof(char));
  }

  return matrix;
}
//=============TERMINA AQUI===================



//=====================================================
//=====FUNCAO QUE PRINTA PARTE DE CIMA DO ARQUIVO======
//=====================================================

void printExec(char **progs, int *timevalue, int quant){
    FILE *f = fopen("priority.txt", "w");

    fprintf(f, "EXECUTION BY EDF\n\n");

    for(int i = 0; i < quant; i++)
        fprintf(f,"[%s] for %d units\n",progs[i], timevalue[i]);
    
    fprintf(f, "\n");
    fclose(f);
}

//==================TERMINA AQUI=======================



//=====================================================
//=====FUNCAO QUE PRINTA PARTE DE BAIXO DO ARQUIVO=====
//=====================================================

void printMetric(char **progs, int *tatTime, int *waitTime, int *responseTime,int quant){
    FILE *f = fopen("priority.txt", "a");
    float total_tat = 0;
    float total_wait = 0;
    float total_response = 0;

    fprintf(f, "METRICS\n\n");

    for(int i = 0; i < quant; i++){
        fprintf(f, "[%s]\n", progs[i]);
        fprintf(f, "Turnaround time: %d\n", tatTime[i]);
        fprintf(f, "Waiting time: %d\n", waitTime[i]);
        fprintf(f, "Response time: %d\n\n", responseTime[i]);
        total_tat += tatTime[i];
        total_wait += waitTime[i];
        total_response += responseTime[i];
    }

    float mediaturnaround = total_tat / quant;
    float mediawait = total_wait / quant;
    float mediarespo = total_response / quant;
    
    fprintf(f, "Average turnaround time = %.2f\n", mediaturnaround);
    fprintf(f, "Average waiting time = %.2f\n", mediawait);
    fprintf(f, "Average response time = %.2f\n", mediarespo);

    fclose(f);
}

//==================TERMINA AQUI=======================