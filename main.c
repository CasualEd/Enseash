#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h> 					//for exit()
#define bufSizeMax 1024
int main(int argc, char * argv){
	int pid, status;
	char command[bufSizeMax];
	int cmp;
	
	char * welcomeMessage="Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. ";
	const char * shellMessage="\nenseash \% \n "; 	
	int lgthWelcString=strlen(welcomeMessage); // Since each character is represent by 8 bits we multiply by 8 the size of buffer
	int lgthShellString=strlen(shellMessage);
	const char * exitMessage="Bye bye... \n ";
	int lgthByeString=strlen(exitMessage);
	
	write(STDOUT_FILENO, welcomeMessage, lgthWelcString); // We print the welcome message string directly on the screen
	
	while(1){ 					//never-ending loop that creates a child after each command excuted to execute it, and ask for a new command after its termination
		pid = fork();
		if(pid!=0){				//father's code
			//if(cmp==0){exit(EXIT_SUCCESS);}
			wait(&status);
			if(WEXITSTATUS(status)==2){
				write(STDOUT_FILENO, exitMessage, lgthShellString);
				exit(EXIT_SUCCESS);
			}
		}else{					//child's code
			
			int readLength;
			int retrn;
			//int writeLength;	
			
			write(STDOUT_FILENO, shellMessage, lgthShellString);
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
	


