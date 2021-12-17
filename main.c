#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h> 					//for exit()
#include <signal.h>
#include <errno.h>

#define bufSizeMax 1024
#define bufInt 8
int main(int argc, char * argv){
	int pid, status;
	char command[bufSizeMax];
	int cmp;
	int old_status=-1;
	
	char * welcomeMessage="Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \nenseash \%  ";
	int lgthWelcString=strlen(welcomeMessage); // Since each character is represent by 8 bits we multiply by 8 the size of buffer
	const char * exitMessage="Bye bye... \n ";
	int lgthByeString=strlen(exitMessage);
	char * shellBisPromptMessage="\nenseash ["; 
	char shellBisMessage[bufSizeMax]; 
	strncat(shellBisMessage, shellBisPromptMessage, bufSizeMax);

	write(STDOUT_FILENO, welcomeMessage, lgthWelcString); // We print the welcome message string directly on the screen
	
	while(1){ 					//never-ending loop that creates a child after each command excuted to execute it, and ask for a new command after its termination
		pid = fork();
		if(pid!=0){				//father's code
			//if(cmp==0){exit(EXIT_SUCCESS);}
			
			wait(&status);
			old_status=WSTOPSIG(status);
			if(WEXITSTATUS(status)==2){
				write(STDOUT_FILENO, exitMessage, lgthByeString);
				exit(EXIT_SUCCESS);
			}
		}else{					//child's code
			
			int readLength;
			int retrn;
			char errorStr[bufInt];
			
			//int writeLength;	
			
			//printf("Avant le if %d \n", old_status);
			//fflush(stdout);
			
			if(old_status!=-1){
				sprintf(errorStr, "%s:%d", strerror(old_status), old_status);
				strncat(shellBisMessage, errorStr, bufSizeMax);
				strncat(shellBisMessage, "] \% ", bufSizeMax);
				int lgthShellBisString=strnlen(shellBisMessage, bufSizeMax);
				write(STDOUT_FILENO, shellBisMessage, lgthShellBisString);
			}
			
			readLength=read(STDIN_FILENO,command,bufSizeMax);
			*(command+readLength-1) ='\0';
			cmp = strncmp(command,"exit",bufSizeMax);
			
			if(cmp==0){
				exit(2);
			}else{
				retrn = execlp(command,command, (char  *) NULL);
				printf("%d",retrn); //prints -1 if there is an execution error
				exit(retrn);
			}
		}
	}
	
}

//Printf avec flush (le buffer n'est vidé qu'à la fin)
	//printf("%d", old_status);
	//fflush(stdout);

//ShellMess
	//const char * shellMessage="\nenseash \%"; 	
	//char command[bufSizeMax];

//Test d'affichage de char 
	//char *b = malloc(sizeof(char));
	//*b= *(command+readLength-2);
	//writeLength=write(STDOUT_FILENO,b,4);
	//printf(b);


// Affichage du résultat de strncmp
	//int cmp;
	//cmp = strncmp(command,"exit",bufSizeMax);
	//printf("%d",cmp);
	
 //We indicate the EOS
	
	//int cmp = strncmp(command,"exit",bufSizeMax);
	//printf("%d",cmp);
	
