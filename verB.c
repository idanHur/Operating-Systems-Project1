#include <stdio.h>
#include <stdlib.h>
#include "mystrlib.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINELEN (80)

int main(void){

    char str1[2*(LINELEN+1)] = {0};
    char str2[LINELEN+1] = {0};
    char readbuffer[LINELEN];
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    
   
    
    
    returnstatus1 = pipe(pipefds1);
    if (returnstatus1 == -1) {
  	 printf("Unable to create pipe 1 \n");
  	 return 1;
    }
    returnstatus2 = pipe(pipefds2);
   
    if (returnstatus2 == -1) {
    	 printf("Unable to create pipe 2 \n");
   	 return 1;
    }
    
    	printf("Please enter string 1:\n");
	  if (mygets(str1, LINELEN) == NULL)
	    	return 1;
	 
	  printf("Please enter string 2:\n");
	  if (mygets(str2, LINELEN) == NULL)
	  	return 1;
	  strcat(str1,"\n");
	  strcat(str2,"\n");
	  strcat(str1,str2);
	  fflush(stdout);  
    
    pid = fork();
   
    if (pid != 0){ // Parent process 
    	
    
         close(pipefds1[0]); // Close the unwanted pipe1 read side
         close(pipefds2[1]); // Close the unwanted pipe2 write side
         

         write(pipefds1[1], str1, sizeof(str1));
         read(pipefds2[0], readbuffer, sizeof(readbuffer));
         printf("\nthe result is: %s\n\n",readbuffer);
         memset(readbuffer,0,sizeof(readbuffer));
         return 1;
         
         
    } else { //child process
    	 dup2(pipefds1[0],fileno(stdin));
    	 close(pipefds1[1]);// Close the unwanted pipe1 write side
    	 dup2(pipefds2[1],fileno(stdout));
         close(pipefds1[0]); 
         close(pipefds2[0]); // Close the unwanted pipe2 read side
      	 close(pipefds2[1]);
         
         char* params[] = {"./xorstr", NULL};
         execve(params[0], params, NULL);
     
   }
   return 0;
}
	    
