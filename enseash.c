#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	//for exit()
#include <wait.h>
#define bufSizeMax 1024

//Functions

void printString(char * string){
	int lgthString=strlen(string); //we retrieve the length of the string to write it on the standard output
	write(STDOUT_FILENO, string, lgthString);
}

void getCommand(char * command){
	printString("enseash % ");
	int readLength;
	readLength=read(STDIN_FILENO,command,bufSizeMax);
	*(command+readLength-1) ='\0';
}

//Main

int main(int argc, char ** argv){
	char * command = malloc(sizeof(char)*bufSizeMax);
	int pid, status;
	
	printString("Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \n");
	
	while(1){ //never-ending loop that creates a child after each command excuted to execute it, and ask for a new command after its termination
		getCommand(command);
		pid = fork();
		if(pid!=0){ 	//father's code
			wait(&status); //the father waits for the child's termination
		}else{			//child's code
			execlp(command,command, (char  *) NULL); // execution of the command
			printString("Erreur d'exécution, veuillez revoir votre commande.\n");
			exit(EXIT_FAILURE);
		}
	}	
}

