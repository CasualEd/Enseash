#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	//for exit()
#define bufSizeMax 1024

//Functions

void printString(char * string){
	int lgthString=strlen(string); //we retrieve the length of the string to write it on the standard output
	write(STDOUT_FILENO, string, lgthString);
}

//Main

int main(int argc, char ** argv){
	printString("Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \n");
	printString("enseash % ");
	exit(EXIT_SUCCESS);
}
