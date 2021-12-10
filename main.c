#include <stdio.h>
#include "string.h"
#define Bufsize 80
int main(int argc, char * argv){
	int fd2=1;
	char * buf="Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \nenseash \% \n";
	int ret=8*(sizeof(buf)+1); // Since each character is represent by 8 bits we multiply by 8 the size of the buffer
	write( fd2 ,buf ,ret); // We print the string directly on the string
	
}

