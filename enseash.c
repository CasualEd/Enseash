#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	//for exit()
#include <wait.h>
#include <signal.h>
#define bufSizeMax 1024

//Functions

void printString(char * string){
	int lgthString=strlen(string); //we retrieve the length of the string to write it on the standard output
	write(STDOUT_FILENO, string, lgthString);
}

void getCommand(char * command, int flag, int old_status, int sigOrExit){
	if(flag==0){			//first command typed in
		printString("enseash % ");
	}else{ //at least one command has been entered
		printString("enseash [");
		char * strInfo = malloc(sizeof(char)*bufSizeMax);
		if(sigOrExit==0){ //the child terminated with exit 
			sprintf(strInfo, "exit:%d", old_status);
		}else{ //else, it terminated by a signal
			sprintf(strInfo, "sign:%d", old_status);
		}
		strncat(strInfo, "] \% ", bufSizeMax);
		printString(strInfo);
		free(strInfo);
	}
	int readLength;
	readLength=read(STDIN_FILENO,command,bufSizeMax);
	*(command+readLength-1) ='\0';
}


//Main

int main(int argc, char ** argv){
	char * command = malloc(sizeof(char)*bufSizeMax);
	int pid, status;
	int old_status;
	int flag=0; //to know if at least one command has been entered since the start of the shell
	int sigOrExit; //to remember if the child terminated with an exit or a signal
	
	printString("Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \n");
	
	while(1){ //never-ending loop that creates a child after each command executed to execute it, and ask for a new command after its termination
		getCommand(command, flag, old_status, sigOrExit);
		if(strncmp(command,"exit",bufSizeMax)==0){ //the program exits if exit is typed
			printString("Bye bye...\n");
			exit(EXIT_SUCCESS);
		}
		pid = fork();
		if(pid!=0){ 	//father's code
			wait(&status);
			if(WIFEXITED(status)){
				sigOrExit=0; //0 for exit, 1 for signal
				old_status=WEXITSTATUS(status);
			}else if(WIFSIGNALED(status)){
				sigOrExit=1;
				old_status=WTERMSIG(status);
			}
			flag=1; //to mark that one command has been executed
		}else{			//child's code
			execlp(command,command, (char  *) NULL);
			printString("Erreur d'exécution, veuillez revoir votre commande.\n");
			exit(EXIT_FAILURE);
		}
	}	
}
