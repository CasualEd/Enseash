#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	//for exit()
#include <time.h> //for the clock
#include <wait.h>
#include <signal.h>
#define bufSizeMax 1024
#define nsToS 1000000000
#define SToms 0.000001
#define bufInt 8

//Functions

void printString(char * string){
	int lgthString=strlen(string); //we retrieve the length of the string to write it on the standard output
	write(STDOUT_FILENO, string, lgthString);
}

void getCommandEnd(char * command, char * comExec, char ** argument_list){
	//reading the whole command
	int readLength;
	readLength=read(STDIN_FILENO,command,bufSizeMax);
	*(command+readLength-1) ='\0';
	
	//parsing the command in parts
	char *token;
	token = strtok(command, " ");
	sprintf(comExec,"%s", token); //retrieving the command's name
	
	int argpos=0;
	while(token != NULL){ //retrieving and storing parameters in an array
		sprintf(argument_list[argpos],"%s", token);
		argpos++;
		token = strtok(NULL, " ");
	}
	argument_list[argpos]=NULL;	//last argument has to be a NULL pointer
	free(token);
}

void getCommand(char * command, char * comExec, char ** argument_list, int flag, int old_status, int sigOrExit, long timeDiff){
	if(flag==0){			//first command typed in
		printString("enseash % ");
	}else{ //at least one command has been entered
		printString("enseash [");
		char * strInfo = malloc(sizeof(char)*bufSizeMax);
		if(sigOrExit==0){ //the child terminated with exit 
			sprintf(strInfo, "exit:%d|%ldms", old_status, timeDiff); 
		}else{ //else, it terminated by a signal
			sprintf(strInfo, "sigfn:%d|%ldms", old_status, timeDiff);
		}
		strncat(strInfo, "] \% ", bufSizeMax);
		printString(strInfo);
		free(strInfo);
	}
	getCommandEnd(command, comExec, argument_list);
}


long timeDifferencems(struct timespec timeStart, struct timespec timeStop){
	long timeDiff=(timeStop.tv_nsec+timeStop.tv_sec*nsToS)-(timeStart.tv_nsec+timeStart.tv_sec*nsToS);
	timeDiff=(long) timeDiff*SToms;
	return timeDiff;
}

//Main

int main(int argc, char ** argv){
	char * command = malloc(sizeof(char)*bufSizeMax);
	int pid, status;
	int old_status;
	int flag=0; //to know if at least one command has been entered since the start of the shell
	int sigOrExit; //to remember if the child terminated with an exit or a signal
	struct timespec timeStart, timeStop;
	long timeDiff;
	
	printString("Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \n");
	
	while(1){ //never-ending loop that creates a child after each command executed to execute it, and ask for a new command after its termination
		//initialisation of an array of string to store the command's parameters
		//done at each turn of loop to avoid segmentation faults
		//freed below
		char ** argument_list = malloc(sizeof(char*)*bufInt);
		for(int im=0;im<bufInt;im++){
			argument_list[im]= (char*)malloc(bufSizeMax*sizeof(char));
		}
		char * comExec = malloc(sizeof(char)*bufSizeMax); //string to save the name of the command called
		
		timeDiff=timeDifferencems(timeStart,timeStop);		//getting the execution time in ms
		getCommand(command, comExec, argument_list, flag, old_status, sigOrExit, timeDiff);
		if(strncmp(command,"exit",bufSizeMax)==0){ //the program exits if exit is typed
			printString("Bye bye...\n");
			exit(EXIT_SUCCESS);
		}
		clock_gettime(CLOCK_MONOTONIC, &timeStart);
		pid = fork();
		if(pid!=0){ 	//father's code
			wait(&status);
			clock_gettime(CLOCK_MONOTONIC, &timeStop);
			if(WIFEXITED(status)){
				sigOrExit=0; //0 for exit, 1 for signal
				old_status=WEXITSTATUS(status);
			}else if(WIFSIGNALED(status)){
				sigOrExit=1;
				old_status=WTERMSIG(status);
			}
			flag=1; //to mark that one command has been executed
		}else{			//child's code
			execvp(comExec, argument_list);
			printString("Erreur d'exécution, veuillez revoir votre commande.\n");
			exit(EXIT_FAILURE);
		}
		free(argument_list);
		free(comExec);
	}	
}


