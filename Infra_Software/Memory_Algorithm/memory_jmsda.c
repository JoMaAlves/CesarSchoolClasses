#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=============================[GLOBAL]==============================
int MEMORY;
//===================================================================

//=============================[STRUCT]==============================
struct memory_node
{
        char name[11];
        int start;
        int end;
        int size;
        struct memory_node * next;
        struct memory_node * previous;
};
//===================================================================

//############################ FUNCTIONS ############################
void take_command(char *command, char * name, int * qtt_choice);
void first_fit(struct memory_node * finder, int memory, char name[]);
void best_fit(struct memory_node * finder, int memory, char name[]);
void worst_fit(struct memory_node * finder, int memory, char name[]);
void release(struct memory_node * finder, char name[]);
void compact(struct memory_node * finder);
void stat_print(struct memory_node * printer);
void check_unused(struct memory_node * start);
//###################################################################

//===================================================================
//=============================[ MAIN ]==============================
//===================================================================
int main(int argc, char * argv[])
{
        //BASE VARIABLES
        char * token;
        MEMORY = atoi(argv[1]);

        //MEMORY LINKED LIST STARTER AND ENDER
        struct memory_node start = { "Start", -1, -1, -1, NULL, NULL };
        struct memory_node end = { "End", MEMORY, MEMORY, MEMORY, NULL, NULL };

        //CREATING THE MEMORY
        start.next = malloc(sizeof(struct memory_node));
        strcpy(start.next->name, "Unused");
        start.next->start = 0;
        start.next->end = MEMORY - 1;
        start.next->next = &end;
        start.next->previous = &start;
        start.next->size = MEMORY;

        //COMMAND VARIABLES
        char command[81];
        char name[11];
        int qtt_choice[2];

        while(1){
                //RESETS THE ARRAYS
                memset(command, 0, sizeof(command));
                memset(name, 0, sizeof(name));
                memset(qtt_choice, 0, sizeof(qtt_choice));
                //PRINTS THE COMMAND LINE STARTER
                printf("allocator>");
                //GETS THE FULL COMMAND
                fgets(command, 81, stdin);

                //EXIT
                if(strncmp("X",command,1) == 0){
                        break;
                }

                //COMPACT
                else if(strncmp("C",command,1) == 0){
                        compact(&start);
                }

                //STATUS
                else if(strncmp("STAT",command,4) == 0){
                        stat_print(start.next);
                }

                //REQUESTS
                else if(strncmp("RQ",command,2) == 0){
                        take_command(command, name, qtt_choice);
                        //FIRST FIT
                        if(qtt_choice[1] == 1){
                                first_fit(&start, qtt_choice[0], name);
                        }
                        //BEST FIT
                        else if(qtt_choice[1] == 2){
                                best_fit(&start, qtt_choice[0], name);
                        }
                        //WORST FIT
                        else if(qtt_choice[1] == 3){
                                worst_fit(&start, qtt_choice[0], name);
                        }
                }

                //RELEASE
                else if(strncmp("RL",command,2) == 0){
                        take_command(command, name, qtt_choice);
                        release(start.next, name);
                        //CHECKS IF THERE IS A UNUSED SPACE NEXT TO THE RELEASED ONE, JOINING THEM
                        check_unused(&start);
                }

                //UNDEFINED COMMAND
                else{
                        printf("Undefined command\n");
                }
        }

        return 0;
}
//===================================================================
//===================================================================
//===================================================================


//###################################################################
//############################ FUNCTIONS ############################

//########################## TAKE COMMAND ###########################
void take_command(char *command, char * name, int * qtt_choice){     
        char * nametoken;
        char * token = strtok(command," ");
        //RELEASE
        if(strncmp("RL",command,2) == 0){
                for(int i = 0; i < 2; i++){
                        //NAME
                        if(i == 1){
                                nametoken = strtok(token,"\n");
                                strcpy(name,nametoken);
                        }
                        token = strtok(NULL, " ");
                }
        }
        //REQUEST
        else{
                for(int i = 0; i < 4; i++){
                        //NAME
                        if(i == 1){
                                strcpy(name,token);
                        }
                        //MEMORY SIZE
                        else if(i == 2) qtt_choice[0] = atoi(token);
                        //CONVERT TO A NUMBER THE ALLOCATION APPROACHES 
                        else if(i == 3){
                                if(strncmp("F",token,1) == 0) qtt_choice[1] = 1;
                                else if(strncmp("B",token,1) == 0) qtt_choice[1] = 2;
                                else if(strncmp("W",token,1) == 0) qtt_choice[1] = 3;
                                break;
                        }
                        token = strtok(NULL, " ");
                }
        }
}
//############################### END ###############################

//############################ FIRST FIT ############################
void first_fit(struct memory_node * finder, int memory, char name[])
{
        struct memory_node * new;
        int find = 0;
        //GO THROUGH THE LIST
        while(finder->next != NULL){
                //CHECK IF IT IS UNUSED
                if(strncmp("Unused",finder->name,6) == 0){
                        //CHECK IF THE MEMORY OF THE PROCESS CAN FIT
                        if(finder->size > memory){
                                //PLACE THE PROCESS
                                new = malloc(sizeof(struct memory_node));
                                new->next = finder->next;
                                new->previous = finder;
                                strcpy(new->name,"Unused");
                                new->end = finder->end;
                                new->start = finder->start + memory;
                                new->size = finder->size - memory;

                                finder->next = new;
                                finder->end = finder->start + memory - 1;
                                finder->size = memory;
                                strcpy(finder->name, name);
                                find = 1;
                                break;
                        }
                        else if(finder->size == memory){
                                strcpy(finder->name, name);
                                find = 1;
                                break;
                        }
                }
                finder = finder->next;
        }
        if(!find) printf("The request of %s fail\n", name);
} 
//############################### END ###############################

//############################# BEST FIT ############################
void best_fit(struct memory_node * finder, int memory, char name[])
{
        int find = 0;
        struct memory_node * marker = NULL;
        struct memory_node * new;
        //GO THROUGH THE LIST LOOKING FOR THE SMALLEST UNUSED SPACE
        while(finder->next != NULL){
                if(strncmp("Unused",finder->name,6) == 0){
                        if(finder->size >= memory){
                                if(marker == NULL){
                                        marker = finder;
                                        find = 1;
                                }
                                else if(finder->size < marker->size){
                                        marker = finder;
                                }
                        }
                }
                finder = finder->next;
        }

        if(!find) printf("The request of %s fail\n", name);
        else{
                //PLACE THE PROCESS
                if(marker->size > memory){
                        new = malloc(sizeof(struct memory_node));
                        new->next = marker->next;
                        new->previous = marker;
                        strcpy(new->name,"Unused");
                        new->end = marker->end;
                        new->start = marker->start + memory;
                        new->size = marker->size - memory;

                        marker->next = new;
                        marker->end = marker->start + memory - 1;
                        marker->size = memory;
                        strcpy(marker->name, name);
                }
                else if(marker->size == memory){
                        strcpy(marker->name, name);
                }
        }

}
//############################### END ###############################

//############################ WORST FIT ############################
void worst_fit(struct memory_node * finder, int memory, char name[])
{
        int find = 0;
        struct memory_node * marker = NULL;
        struct memory_node * new;
        //GO THROUGH THE LIST LOOKING FOR THE BIGGEST UNUSED SPACE
        while(finder->next != NULL){
                if(strncmp("Unused",finder->name,6) == 0){
                        if(finder->size >= memory){
                                if(marker == NULL){
                                        marker = finder;
                                        find = 1;
                                }
                                else if(finder->size > marker->size){
                                        marker = finder;
                                }
                        }
                }
                finder = finder->next;
        }

        if(!find) printf("The request of %s fail\n", name);
        else{
                //PLACE THE PROCESS
                if(marker->size > memory){
                        new = malloc(sizeof(struct memory_node));
                        new->next = marker->next;
                        new->previous = marker;
                        strcpy(new->name,"Unused");
                        new->end = marker->end;
                        new->start = marker->start + memory;
                        new->size = marker->size - memory;

                        marker->next = new;
                        marker->end = marker->start + memory - 1;
                        marker->size = memory;
                        strcpy(marker->name, name);
                }
                else if(marker->size == memory){
                        strcpy(marker->name, name);
                }
        }
}
//############################### END ###############################

//############################# RELEASE #############################
void release(struct memory_node * finder, char name[])
{
        int find = 0;
        struct memory_node * join;
        while(finder->next != NULL){
                if(strcmp(finder->name, name) == 0){
                        strcpy(finder->name,"Unused");
                        find++;
                        break;
                }
                finder = finder->next;
        }
        if(!find) printf("Fail to release %s\n", name);
}
//############################### END ###############################

//############################# COMPACT #############################
void compact(struct memory_node * start)
{
        int free_space = 0;
        struct memory_node * finder = start;
        struct memory_node * last = NULL;
        struct memory_node * helper;
        while(finder->next != NULL){
                if(strncmp("Unused",finder->name,6) == 0){
                        free_space = free_space + finder->size; 
                        last = finder;
                }
                finder = finder->next;
        }
        if(last != NULL){
                finder = start;
                while(finder->next != NULL){
                        if(strncmp("Unused",finder->name,6) == 0){
                                if(finder != last){
                                        helper = finder->next;
                                        finder = finder->previous;
                                        helper->previous = finder;
                                        free(finder->next);
                                        finder->next = helper;
                                }
                                else{
                                        finder->size = free_space;
                                }
                        }
                        finder = finder->next;
                }
                finder = start->next;
                while(finder->next != NULL){
                        finder->start = finder->previous->end + 1;
                        finder->end = finder->start + finder->size - 1;
                        finder = finder->next;
                }
        }
}
//############################### END ###############################

//########################### STATUS PRINT ##########################
void stat_print(struct memory_node * printer)
{
        while(printer->next != NULL){
                printf("Addresses [%d:%d] ", printer->start,printer->end);
                if(strcmp(printer->name, "Unused") != 0) printf("Process %s\n", printer->name);
                else printf("Unused\n");
                printer = printer->next;
        }
}
//############################### END ###############################

//########################### CHECK UNUSED ##########################
void check_unused(struct memory_node * start){
        //CHECKS IF THERE IS A UNUSED SPACE NEXT TO THE RELEASED ONE, JOINING THEM
        struct memory_node * point;
        struct memory_node * join;
        for(int i = 0; i < 2; i++){
                point = start;
                while(point->next != NULL){
                        if((strcmp(point->next->name, "Unused") == 0) && (strcmp(point->name, "Unused") == 0)){
                                join = point->next;
                                join->next->previous = point;
                                point->end = join->end;
                                point->next = join->next;
                                point->size = point->size + join->size;
                                free(join);
                                continue;
                        }
                        point = point->next;
                }
        }
}
//############################### END ###############################
//###################################################################