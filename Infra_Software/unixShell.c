#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#define MAX_LINE 80 


int take_input(char* comando){
	char p;
	int num = 0;

	while (((p = getchar()) != '\n') && (num < MAX_LINE)) {
		comando[num++] = p;
	}

	if (num == MAX_LINE && p != '\n') {
		printf("Comando excede o numero permitido");
		num = -1;
	} 
	else {
		comando[num] = 0;
	}
	return num;

}

int save_history(char *comando, int tamanho_input, char* historia[], int num_comando){
	historia[num_comando] = (char*)malloc(tamanho_input*sizeof(char));
	strcpy(historia[num_comando], comando);
	//printf("%s\n", historia[0]);
	return 0;
}

char** split_command(char *comando, int *tamanho_splited, int *background, int *maiorQue, int *menorQue, int *pipe){
	char **comandoSplited = (char**)malloc(15*sizeof(char*));;
	int i = 0;
	char sep[2] = " ";

	char *token = strtok(comando, sep);

	while(token != NULL){
		if (strcmp(token, "&") == 0){
			comandoSplited[++i] = NULL;
			*background = 1;
			break;
		}

		else if (strcmp(token, ">") == 0){
			token = strtok(NULL, sep);
			comandoSplited[i] = (char*)malloc(sizeof(strlen(token)));
			strcpy(comandoSplited[i], token);
			*maiorQue = 1;
			*tamanho_splited = *tamanho_splited + 1;
			token = strtok(NULL, sep);
		}

		else if (strcmp(token, "<") == 0){
			token = strtok(NULL, sep);
			comandoSplited[i] = (char*)malloc(sizeof(strlen(token)));
			strcpy(comandoSplited[i], token);
			*menorQue = 1;
			*tamanho_splited = *tamanho_splited + 1;
			token = strtok(NULL, sep);
		}

		else if (strcmp(token, "|") == 0){
			token = strtok(NULL, sep);
			comandoSplited[i] = (char*)malloc(sizeof(strlen(token)));
			strcpy(comandoSplited[i], token);
			*pipe = 1;
			*tamanho_splited = *tamanho_splited + 1;
			break;
		}
		
//comandoSpliteed = ["ls", "-l", "arquivo.txt"]
		else{
			comandoSplited[i] = (char*)malloc(sizeof(strlen(token)));//ALOCA ESPACO DE CADA PALAVRA
			strcpy(comandoSplited[i++], token);//SALVA PALAVRA NO ESPACO ALOCADO
			token = strtok(NULL, sep);
			*tamanho_splited = *tamanho_splited + 1;
		}
		
	}

	/*
	for(i=0; i<3; i++){
		printf("%s\n", comandoSplited[i]);
	}
	*/

	return comandoSplited;

}
    
int main(void){

	int should_run = 1; 
	int tamanho_input = 0;
	int num_comando = 0;
	char comando[MAX_LINE +1];//COMANDO QUE VAI SER EXECUTADO NO MOMENTO E SER SALVO NO ARGS
	char **comando_splitado;

	char *historico_comandos[MAX_LINE/2 + 1];//ARRAY DE STRINGS QUE VAI GUARDAR OS COMANDOS
	historico_comandos[1] = NULL;

	while (should_run){
		printf("osh>");
		fflush(stdout);
		memset(comando, 0, sizeof(comando));//RESETA O ARRAY PARA PEGAR PROXIMO COMANDO
		int paralelo = 0;
		int maiorQue = 0;
		int menorQue = 0;
		int tamanho_splited = 0;
		int usou_pipe = 0;

		tamanho_input = take_input(comando);//PEGA QUAL COMANDO O USUARIO QUER E SALVA NA VARIAVEL COMANDO


		if (tamanho_input == -1 || strcmp(comando, "exit") == 0)//CHECA SE O USUARIO QUER TERMINAR O PROGRAMA
			return 1;
		
		if (strcmp(comando, "!!") == 0 && historico_comandos[1] != NULL){//SE O USUARIO DIGITOU !! E JA HOUVER COMANDO NO HISTORICO
			strcpy(comando, historico_comandos[num_comando]);//O COMANDO VIRA O ULTIMO COMANDO DO HISTORICO
		}
		else if (strcmp(comando, "!!") == 0 && historico_comandos[1] == NULL){//SE O USUARIO DIGITAR !! MAS NAO HOUVER COMANDO NO HISTORICO
			printf("No commands in history\n");
			continue;
		}

		save_history(comando, tamanho_input, historico_comandos, ++num_comando);//SALVA COMANDO NO HISTORY
		comando_splitado = split_command(comando, &tamanho_splited, &paralelo, &maiorQue, &menorQue, &usou_pipe);//PEGO O COMANDO SPLITADO POR " "

		
		if(comando_splitado == NULL)
			continue;

		pid_t pid = fork();

		if (pid < 0){//CASO RETORNE < 0 EH PQ DEU ERRO
			printf("Process child ERROR\n");
			return 1;
		}

		int processo;

		if (pid == 0){// SE O PID == 0 SIGNIFICA Q ESTE EH O PROCESSO FILHO E O COMANDO VAI SER EXECUTADO NELE
			if(maiorQue){//COMANDO Q VAI SER RODADO QUANDO O USUARIO UTILIZAR O >
				//processo -> comando_splitado[0]
				//nome do arquivo -> comando_splitado[1]
			
				//comando_splitado = ["comando", "parametro", "nome_do_arquivo"]
				int file = open(comando_splitado[tamanho_splited-1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				comando_splitado[tamanho_splited-1] = NULL;

				dup2(file, 1);//FICA ESPERANDO UM OUTPUT NO TERMINAL PARA GRAVAR NO ARQUIVO

				processo = execvp(comando_splitado[0], comando_splitado);

			}

			else if(menorQue){//COMANDO QUE VAI SER RODADO QUANDO O USUARIO UTILIZAR <
				int file = open(comando_splitado[tamanho_splited-1], O_RDONLY);
				
				dup2(file, STDIN_FILENO);//FICA ESPERANDO UM COMANDO NO TERMINAL PARA EXECUTAR NO ARQUIVO
				close(file);

				comando_splitado[tamanho_splited-1] = NULL;

				processo = execvp(comando_splitado[0], comando_splitado);

			}

			else if(usou_pipe){
				//IMPLEMENTAR PIPE AQUI
				//comando_splitado = ["comando1", "parametro", "comando2"]
				//exemplo -> ["ls", "-l", "less"]

				int pipefd[2];
				pipe(pipefd);

				//CRIA UM PROCESSO FILHO PARA EXECUTAR O COMANDO1
				pid_t pid2 = fork();

				if (pid2 == 0){
					//TRATAMENTO DO ARRAY PARA COMANDO 1
					comando_splitado[tamanho_splited-1] = NULL;
					//AGORA comando_splitado = ["comando1", "parametro", NULL];

					dup2(pipefd[1], 1);//SAIDA DO COMANDO VAI SER SALVO NO PIPEFD[1]
					close(pipefd[0]);//FECHA OUTRO PIPE QUE NAO VAI SER USADO

					execvp(comando_splitado[0], comando_splitado);
					return 0;
				}
				else{
					//CRIA OUTRO ARRAY PARA COMANDO 2
					char **comando2 = (char**)malloc(2*sizeof(char*));
					comando2[0] = malloc(strlen(comando_splitado[tamanho_splited-1])*sizeof(char));
					strcpy(comando2[0], comando_splitado[tamanho_splited-1]);
					comando2[1] = NULL;

					//AGORA comando2 = ["comando2", NULL];

					dup2(pipefd[0], 0);//O Q TIVER DENTRO DO pipefd[0] VAI SER USADO DE PARAMETRO
					close(pipefd[1]);

					processo = execvp(comando2[0], comando2);
					return 0;
				}


			}

			else{//COMANDO QUE VAI RODAR NORMALMENTE
				processo = execvp(comando_splitado[0], comando_splitado);//EXECUTA COMANDO NO PROCESSO FILHO NO TERMINAL
				should_run = 0;
			}

		}
		else{//CASO N SEJA NENHUM DOS DOIS SIGNIFICA Q EH O PROCESSO PAI
			if(paralelo == 1){
				printf("Processo filho rodando no background\n");//ESTE PRINT EH EXECUTADO NO PROCESSO PAI
			}
			else{
				wait(&processo);//ESPERA O PROCESSO FILHO TERMINAR PARA CONTINUAR O PROCESSO PAI
			}
		}

		//execvp(comando_splitado[0], comando_splitado);//EXECUTA COMANDO NO TERMINAL

		if (strcmp(comando, "history") == 0){
			for(int i =1; i<num_comando; i++)
				printf("%s\n", historico_comandos[i]);
		}

       }
return 0;
}