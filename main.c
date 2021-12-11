#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#define BUFSIZE 120
int main(int argc, char * argv){
	int screen=1;
	int rea;
	char cha;
	int flag=0;                      
	char * buf="Welcome to ENSEA Tiny Shell. \nPour quitter, tapez 'exit'. \nenseash \% ";
	char * exit="exit";
	char command[BUFSIZE];
	char * cop;
	char * test;
	int ret=strlen(buf); // Since each character is represent by 8 bits we multiply by 8 the size of buffer
	write(STDOUT_FILENO,buf ,ret); // We print the string directly on the screen
	ret=1; 
	//while(flag==0){
		//cha=fgetc(stdin); // We wait till the user presses a key 
		//if(cha==0x0A){
			//flag=1;
		//}
		//else{
			//write(screen ,cha,ret);
			//command+=1;
			//*(command)=cha;
		//}
		
	//}
	cop=malloc(20);
	rea=read(STDIN_FILENO,command,BUFSIZE);
	sprintf(cop,"%d",rea);
	
	write(screen,cop,rea);
	*(command+rea)='\0';

	
	
	
	
	
	if(strncmp(command,"exit",strlen(command))==0){
		write(screen,"Yori",8);
	}
	

			
	
	
}// EXIT_SUCCESS

