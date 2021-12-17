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
	const char * shellMessage="\nenseash \% "; 	
	int lgthWelcString=strlen(welcomeMessage); // Since each character is represent by 8 bits we multiply by 8 the size of buffer
	int lgthShellString=strlen(shellMessage);
	write(STDOUT_FILENO, welcomeMessage, lgthWelcString); // We print the welcome message string directly on the screen
	write(STDOUT_FILENO, shellMessage, lgthShellString);
	
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
	


