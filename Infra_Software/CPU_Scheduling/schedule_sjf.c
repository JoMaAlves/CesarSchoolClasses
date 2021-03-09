#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

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
	int *tatTimes = malloc(sizeof(int)*size);
    int *burstTimes = malloc(sizeof(int)*size);
    int *waitingTimes = malloc(sizeof(int)*size);
    int *responseTimes = malloc(sizeof(int)*size);

    struct node *aux = head;
	struct node *aux_2 = head;

    int i = 0;
    //COMECO A RODAR A LINKED LIST
    while(aux_2!=NULL){
        //UMA AUX VAI PERCORRENDO E COMPARANDO A PRIORIDADE COM A DA AUX_2, SE FOR MENOR, AUX_2 ASSUME ESSA POSIÇÃO
        if(aux->task->burst < aux_2->task->burst) aux_2 = aux;
        
        aux = aux->next;
        //TERMINOU DE PERCORRER AUX FICA NULL E AUX_2 FINALMENTE É USADA
        if(aux == NULL){
            //printf("%s\n", aux_2->task->name);
            tatTimes[i] = 0;
            burstTimes[i] = aux_2->task->burst; //SALVO CADA BURST TIME NO ARRAY EM ORDEM
            names[i] = aux_2->task->name;//SALVO CADA NOME DE PROCESSO NO ARRAY EM ORDEM

            for(int j = 0; j <= i; j++) tatTimes[i] += burstTimes[j]; //CADA TAT TIME VAI SER A SOMA DOS ANTERIORES SOMADO COM SEU PROPRIO BURST TIME
            
            i++;
            run(aux_2->task, aux_2->task->burst);
            if (&aux_2 == &head){
                head = head->next;
                aux = head;
                aux_2 = head;
                continue;
            } 
            delete(&head, aux_2->task); //DELETO A TASK QUE JA FOI USADA, PRA NÃO USAR DE NOVO
            aux = head;
            aux_2 = head;
        }
    }

    for(int i=0; i<size; i++){
        waitingTimes[i] = tatTimes[i] - burstTimes[i];//CADA WAITING TIME SERA O TAT TIME(TEMPO QUE LEVOU ATE SER CONCLUIDO) - SEU BURST
        responseTimes[i] = tatTimes[i] - burstTimes[i];//TEMPO DESDE Q INICIALIZOU O PROCESSO ATE PRIMEIRO CONTATO COM A CPU
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

  for(int i = 0; i < n; i++){
    matrix[i] = (char*)malloc(2*sizeof(char));
  }

  return matrix;
}
//=============TERMINA AQUI===================



//=====================================================
//=====FUNCAO QUE PRINTA PARTE DE CIMA DO ARQUIVO======
//=====================================================

void printExec(char **progs, int *timevalue, int quant){
    FILE *f = fopen("sjf.txt", "w");

    fprintf(f, "EXECUTION BY SJF\n\n");

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
    FILE *f = fopen("sjf.txt", "a");
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