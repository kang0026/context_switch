/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett

 Modified for CMPT-300, to include 2 way communication
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
    int     fdP[2]; //Pipe child uses to contact parent

	int 	fdC[2]; //Pipe parent uses to contact child

	int nbytes;
    pid_t   childpid;
    char returnString[1];
    char readbuffer[10];
	char inputBuffer[10];


    pipe(fdP); // Child >> Parent
	pipe(fdC); // Parent >> Child 
        
	//printf("Please send a message\n");

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                
	        close(fdC[0]); // The Child closes the output side of its pipe

			close(fdP[1]); // The Child also closes the parents input side
				
			bzero((char *) &readbuffer, sizeof(readbuffer)); //Clear buffer

			nbytes = read(fdP[0], readbuffer, sizeof(readbuffer)); // Child blocks on read
			
			returnString[0] = 'x';
			//printf("returnString: %s\n", returnString);
			write(fdC[1], returnString, (strlen(returnString))); // Send an ACK
			
	
            exit(0);
        }
        else
        {
                
	        close(fdC[1]);
			close(fdP[0]);		
			
			bzero((char *) &inputBuffer, sizeof(inputBuffer));			
			
			inputBuffer[0] = 'x';
			//printf("inputBuffer: %s\n", inputBuffer);			
			
			write(fdP[1], inputBuffer, (strlen(inputBuffer)));

			nbytes = read(fdC[0], readbuffer, sizeof(readbuffer));

	        //printf("Child Sends: %s\n", readbuffer);			
	        
			wait(NULL);
        } 
        return(0);
}
