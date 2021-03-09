#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//=============================[GLOBAL]==============================
int NUMBER_OF_CUSTOMERS = 0;
int NUMBER_OF_RESOURCES;
//===================================================================

//===========================[FUNCTIONS]=============================
void count_customers();
int count_requests();
int request_resources(int resouces[], int request[]);
int safety(int available[], int ** need);
int lessequal(int choice, int need[], int work[]);
int check_zero(int array[]);
void print_file();
//===================================================================

//===================================================================
//=============================[ MAIN ]==============================
//===================================================================

int main(int argc, char *argv[])
{
        //BASE VARIABLES
        FILE *f;
        char c;
        char *token;
        char request[80];
        int custom = 0;
        int customer = 0;
        int numbers = 0; 
        int posi = 0;
        int command = 0;
        

        //SET THE NUMBER OF CUSTOMERS AND RESOURCES
        count_customers();
        NUMBER_OF_RESOURCES = argc - 1;

        //BANKER'S VARIABLES
        int available[NUMBER_OF_RESOURCES];
        int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
        int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
        int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
        int quant = count_requests();
        int requestcommand[quant][NUMBER_OF_RESOURCES + 2];

        //SET THE AVAILABLE RESOURCES
        for(int i = 1; i < argc; i++){
                available[i-1] = atoi(argv[i]);
        }

        //SET THE MAXIMUM AND NEED OF EACH CUSTOMER, 
        f = fopen("customer.txt", "r");
        while(fgets(request, sizeof(request), f)!= NULL){
                token = strtok(request,",");
                while(token != NULL){
                        maximum[custom][numbers] = atoi(token);
                        need[custom][numbers] = atoi(token);

                        token = strtok(NULL, ",");
                        numbers++;
                }
                custom++;
                numbers = 0; 
        }
        fclose(f);

        //SET TO ZERO THE AMOUNT OF ALLOCATED RESOURCES FOR EACH CUSTOMER
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                        allocation[i][j] = 0;
                }
        }
        
        //SETTING THE COMMANDS
        f = fopen("commands.txt", "r");
        //HERE WE SPLIT THE COMMANDS.TXT IN REQUESTCOMMAND, EACH LINE BEING A LINE OF THE TXT
        while(fgets(request, sizeof(request), f)!= NULL){
                token = strtok(request," ");
                while(token != NULL){
                        //GET RQ AND CONVERT TO 1
                        if(!strncmp("RQ",token,2)){
                                requestcommand[posi][command] = 1;
                                command++;
                        }
                        //GET RL AND CONVERT TO 2
                        else if(!strncmp("RL",token,2)){
                                requestcommand[posi][command] = 2;
                                command++;
                        }
                        //GET * AND CONVERT TO 3
                        else if(!strncmp("*",token,1)){
                                requestcommand[posi][command] = 3;
                                command++;
                        }
                        //KEEP THE NUMBERS OF THE CUSTOMER AND RESOURCES
                        else{
                                requestcommand[posi][command] = atoi(token);
                                command++;
                        }
                        token = strtok(NULL, " ");
                }
                posi++;
                command = 0;
        }
        fclose(f);

        //HERE WE EXECUTE THE COMMANDS
        f = fopen("result.txt","w");
        for(int i = 0; i < quant; i++){
                customer = requestcommand[i][1];

                //REQUEST RESOURCES
                if(requestcommand[i][0] == 1){
                        
                        //CHECK IF REQUEST <= NEED
                        if(lessequal(2, requestcommand[i], need[customer])){
                                
                                //CHECK IF REQUEST <= AVAILABLE
                                if(lessequal(2, requestcommand[i], available)){

                                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                                available[k] = available[k] - requestcommand[i][k+2];
                                                allocation[customer][k] = allocation[customer][k] + requestcommand[i][k+2];
                                                need[customer][k] = need[customer][k] - requestcommand[i][k+2];
                                        }

                                        //SAFETY ALGORITHM
                                        int result = 1;
                                        int finish[NUMBER_OF_CUSTOMERS];
                                        for(int k = 0; k < NUMBER_OF_CUSTOMERS; k++){
                                                finish[k] = 0;
                                        }

                                        int work[NUMBER_OF_RESOURCES];
                                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                                work[k] = available[k];
                                        }
                                        
                                        for(int l = 0; l < NUMBER_OF_CUSTOMERS; l++){
                                                for(int k = 0; k < NUMBER_OF_CUSTOMERS; k++){
                                                        if((finish[k] == 0) && (lessequal(1,need[k], work))){
                                                                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                                                                        work[j] = work[j] + allocation[k][j];
                                                                        finish[k] = 1;
                                                                }
                                                                
                                                        }
                                                }
                                        }
                                        //CHECK THE SAFETY, IF FULL 1s == SAFE      ELSE == UNSAFE
                                        for(int k = 0; k < NUMBER_OF_CUSTOMERS; k++){
                                                if(finish[k] == 0) result = 0;
                                        }
                                        
                                        //SAFE STATE
                                        if(result){
                                                fprintf(f, "Allocate to customer %d the resources", requestcommand[i][1]);
                                                for(int k = 2; k <= NUMBER_OF_RESOURCES + 1; k++){
                                                        fprintf(f, " %d", requestcommand[i][k]);
                                                }
                                                fprintf(f, "\n");
                                        }

                                        //UNSAFE STATE
                                        else{
                                                fprintf(f, "The customer %d request", requestcommand[i][1]);
                                                for(int k = 2; k <= NUMBER_OF_RESOURCES + 1; k++){
                                                        fprintf(f, " %d", requestcommand[i][k]);
                                                }
                                                fprintf(f, " was denied because result in an unsafe state");
                                                fprintf(f, "\n");

                                                //TURN THE VALUES BACK TO NORMAL
                                                for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                                        available[k] = requestcommand[i][k+2] + available[k];
                                                        need[customer][k] = need[customer][k] + requestcommand[i][k+2];
                                                        allocation[customer][k] = allocation[customer][k] - requestcommand[i][k+2];
                                                }
                                        }
                                }

                                //RESOURCES NOT AVAILABLE
                                else{
                                        fprintf(f, "The resources");
                                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                                fprintf(f, " %d", available[k]);
                                        }

                                        fprintf(f, " are not enough to customer %d request", requestcommand[i][1]);
                                        for(int k = 2; k <= NUMBER_OF_RESOURCES + 1; k++){
                                                fprintf(f, " %d", requestcommand[i][k]);
                                        }
                                        fprintf(f, "\n");
                                }
                        }

                        //EXCEEDED MAXIMUM ALLOCATION
                        else{
                                fprintf(f, "The customer %d request", requestcommand[i][1]);
                                for(int k = 2; k <= NUMBER_OF_RESOURCES + 1; k++){
                                        fprintf(f, " %d", requestcommand[i][k]);
                                }
                                fprintf(f, " was denied because exceed its maximum allocation");
                                fprintf(f, "\n");
                        }
                }

                //RELEASING RESOURCES
                else if(requestcommand[i][0] == 2){
                        //CHECK IF ALLOCATION IS 0
                        if(check_zero(allocation[customer])){
                                //CHECK IF THE REQUEST CAN BE DONE
                                if(lessequal(2, requestcommand[i], allocation[customer])){
                                        fprintf(f, "Release from customer %d the resources", requestcommand[i][1]);
                                        for(int k = 2; k <= NUMBER_OF_RESOURCES + 1; k++){
                                                fprintf(f, " %d", requestcommand[i][k]);
                                        }
                                        fprintf(f, "\n");

                                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                                available[k] = requestcommand[i][k+2] + available[k];
                                                need[customer][k] = need[customer][k] + requestcommand[i][k+2];
                                                allocation[customer][k] = allocation[customer][k] - requestcommand[i][k+2];
                                        }
                                }
                                //IF IT CAN'T
                                else fprintf(f, "Customer %d can't release resources that it don't possess\n", requestcommand[i][1]);
                        }
                        //IF IT IS FULL OF ZEROS
                        else fprintf(f, "Customer %d can't release resources that it don't possess\n", requestcommand[i][1]);
                }

                //PRINT TABLE
                else{
                        fprintf(f, "MAXIMUM");
                        if(NUMBER_OF_RESOURCES > 4){
                                for(int k = 0; k < NUMBER_OF_RESOURCES - 4; k++){
                                        fprintf(f, "  ");
                                }
                        }
                        fprintf(f, " |");

                        fprintf(f, " ALLOCATION");
                        if(NUMBER_OF_RESOURCES > 5){
                                for(int k = 0; k < NUMBER_OF_RESOURCES - 5; k++){
                                        fprintf(f, "  ");
                                }
                                fprintf(f, "|");
                        }
                        else{
                                fprintf(f, " |");
                        }

                        fprintf(f, " NEED\n");

                        for(int k = 0; k < NUMBER_OF_CUSTOMERS; k++){
                                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                                        fprintf(f, "%d ",maximum[k][j]);
                                }

                                if(NUMBER_OF_RESOURCES < 4){
                                        for(int j = 0; j < 4 - NUMBER_OF_RESOURCES; j++){
                                                fprintf(f, "  ");
                                        }
                                }
                                fprintf(f, "| ");

                                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                                        fprintf(f, "%d ",allocation[k][j]);
                                }

                                if(NUMBER_OF_RESOURCES < 5){
                                        for(int j = 0; j < 5 - NUMBER_OF_RESOURCES; j++){
                                                fprintf(f, "  ");
                                        }
                                }
                                fprintf(f, " | ");

                                for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                                        fprintf(f, "%d ",need[k][j]);
                                }
                                fprintf(f, "\n");
                        }
                        
                        fprintf(f, "AVAILABLE");

                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                                fprintf(f, " %d",available[k]);
                        }
                        fprintf(f, "\n");
                }
        }
        fclose(f);

        return 0;
}


//===================================================================
//===================================================================
//===================================================================



//###################################################################
//############################ FUNCTIONS ############################


//####################### NUMBER OF CUSTOMERS #######################
void count_customers()
{
        FILE *f = fopen("customer.txt", "r");

        for (char c = getc(f); c != EOF; c = getc(f)){
                if(c == '\n') NUMBER_OF_CUSTOMERS++;
        }
        NUMBER_OF_CUSTOMERS++;

        fclose(f);
}
//############################### END ###############################


//####################### NUMBER OF REQUESTS ########################
int count_requests()
{
        FILE *f = fopen("commands.txt", "r");
        int quant = 0;

        for (char c = getc(f); c != EOF; c = getc(f)){
                if(c == '\n') quant++;
        }
        quant++;

        fclose(f);
        return quant;
}
//############################### END ###############################


//######################## CHECK ALLOCATION #########################
int check_zero(int array[])
{
        int zero = 0;
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
                if(array[i] == 0) zero++;
        }

        if(zero < NUMBER_OF_RESOURCES) return 1;
        else return 0;
}
//############################### END ###############################


//###################### LESSEQUAL ALGORITHM ########################
int lessequal(int choice, int first[], int second[])
{
        if(choice == 1){
                for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
                        if(first[i] <= second[i]){
                                continue;
                        }
                        else{
                                return 0;
                        }
                }
                return 1;
        }
        else{
                for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
                        if(first[i+2] <= second[i]){
                                continue;
                        }
                        else{
                                return 0;
                        }
                }
                return 1;
        }
        
}
//###################################################################
//############################### END ###############################
//###################################################################