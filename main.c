#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h> 					//for exit()
#include <signal.h>
#include <errno.h>make
#include <time.h>
#include <math.h>
#define bufSizeMax 1024
#define bufInt 8
#define nsToS 1000000000
#define SToms 0.000001
int main(int argc, char * argv){
	int pid, status;
	char command[bufSizeMax];
	int cmp;
	int old_status=-1;
	
	char * welcomeMessage="Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \nenseash \%  ";
	int lgthWelcString=strlen(welcomeMessage);
	const char * exitMessage="Bye bye... \n "; int lgthByeString=strlen(exitMessage);
	char * shellBisPromptMessage="\nenseash ["; 
	char shellBisMessage[bufSizeMax];strncat(shellBisMessage, shellBisPromptMessage, bufSizeMax);
	
	struct timespec timeStart, timeStop;
	long timeDiff;
	
	write(STDOUT_FILENO, welcomeMessage, lgthWelcString); // We print the welcome message string directly on the screen
	
	while(1){ 					//never-ending loop that creates a child after each command excuted to execute it, and ask for a new command after its termination
		clock_gettime(CLOCK_MONOTONIC, &timeStart);// Since we want to measure the child's process time we need to start measuring the time before the fork 
		pid = fork();
		if(pid!=0){				//father's code
			wait(&status);
			clock_gettime(CLOCK_MONOTONIC, &timeStop);
			timeDiff=(timeStop.tv_nsec+timeStop.tv_sec*nsToS)-(timeStart.tv_nsec+timeStart.tv_sec*nsToS);
			timeDiff=(long) timeDiff*SToms;
			old_status=WSTOPSIG(status);
			if(WEXITSTATUS(status)==2){
				write(STDOUT_FILENO, exitMessage, lgthByeString);
				exit(EXIT_SUCCESS);
			}
		}else{					//child's code
			
			int readLength;
			int retrn;
			char errorStr[bufInt];
			
			if(old_status!=-1){
				sprintf(errorStr, "%s:%d|%ld ms", strerror(old_status), old_status,timeDiff);
				strncat(shellBisMessage, errorStr, bufSizeMax);
				strncat(shellBisMessage, "] \% ", bufSizeMax); // Here we print the next inquiry for the message
				int lgthShellBisString=strnlen(shellBisMessage, bufSizeMax);
				write(STDOUT_FILENO, shellBisMessage, lgthShellBisString);
			}
			
			readLength=read(STDIN_FILENO,command,bufSizeMax);// We wait for a command 
			*(command+readLength-1) ='\0';
			cmp = strncmp(command,"exit",bufSizeMax);
			
			if(cmp==0){ 
				exit(2);
			}else{
				retrn = execlp(command,command, (char*)NULL); // if it's not exit we can execute the command as it is
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
	
