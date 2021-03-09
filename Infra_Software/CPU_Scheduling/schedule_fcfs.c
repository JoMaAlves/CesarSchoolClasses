#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "list.h"

struct node *head = NULL;


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
    matrix[i] = (char*)malloc(2*sizeof(char));
  }

  return matrix;
}
//=============TERMINA AQUI===================


//=====================================================
//=====FUNCAO QUE PRINTA PARTE DE CIMA DO ARQUIVO======
//=====================================================

void printExec(char **progs, int *timevalue, int quant){
    FILE *f = fopen("fcfs.txt", "w");

    fprintf(f, "EXECUTION BY FCFS\n\n");

    for(int i = 0; i < quant; i++)
        fprintf(f,"[%s] for %d units\n",progs[i], timevalue[i]);
    
    fprintf(f, "\n");
    fclose(f);
}

//==================TERMINA AQUI=======================



//=====================================================
//=====FUNCAO QUE PRINTA PARTE DE BAIXO DO ARQUIVO======
//=====================================================

void printMetric(char **progs, int *tatTime, int *waitTime, int *responseTime,int quant){
    FILE *f = fopen("fcfs.txt", "a");
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

//==================TERMINA AQUI=================================



//========================================================
//=====FUNCAO PRINCIPAL QUE PEGA DADOS DOS PROCESSOS======
//========================================================

void schedule(){
	int size = getSize(head);//PEGA QUANTIDADE DE PROCESSOS

	//ALOCA ESPACO PARA ARRAYS QUE SERAO UTILIZADOS
	char **names = loc_matrix(size);
	int *tatTimes = malloc(sizeof(int)*size);
    int *burstTimes = malloc(sizeof(int)*size);
    int *waitingTimes = malloc(sizeof(int)*size);
    int *responseTimes = malloc(sizeof(int)*size);

	struct node *aux = head;
	struct node *aux_2 = head;

    int i = 0;
//COMECO A RODAR A LINKED LIST
	while(aux!=NULL){
		tatTimes[i] = 0;
		burstTimes[i] = aux->task->burst;//SALVO CADA BURST TIME NO ARRAY EM ORDEM
		names[i] = aux->task->name;//SALVO CADA NOME DE PROCESSO NO ARRAY EM ORDEM
		while(aux_2 != aux){
			tatTimes[i] += aux_2->task->burst;//CADA TAT TIME VAI SER A SOMA DOS ANTERIORES SOMADO COM SEU PROPRIO BURST TIME
			aux_2 = aux_2->next;
		}
		tatTimes[i] += aux->task->burst;//SOMA O PROPRIO BURST TIME
		i++;
		aux_2 = head;
		aux = aux->next;
	}

    for(int i=0; i<size; i++){
        waitingTimes[i] = tatTimes[i] - burstTimes[i];//CADA WAITING TIME SERA O TAT TIME(TEMPO QUE LEVOU ATE SER CONCLUIDO) - SEU BURST
        responseTimes[i] = tatTimes[i] - burstTimes[i];//TEMPO DESDE Q INICIALIZOU O PROCESSO ATE PRIMEIRO CONTATO COM A CPU
    }

	printExec(names, burstTimes, size);
	printMetric(names, tatTimes, waitingTimes, responseTimes, size);
}















