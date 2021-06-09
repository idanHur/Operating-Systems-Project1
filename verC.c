#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>
#include "mystrlib.h"
#define PAGESIZE 4096
#define LINELEN (80)

void whenToUnpause()
  {
  }

int main(int argc, char **argv)
{
	char str1[LINELEN+1] = {0};
    	char str2[LINELEN+1] = {0};
	char* sharde_memory_res;
	pid_t pId;
	int status = 0;
	sharde_memory_res =mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(sharde_memory_res == MAP_FAILED)
	{
		perror("MEMORY ERROR\n");
		return -1;
	}
	pId = fork();
	if (pId == -1)
	{
		perror("ERROR IN CHILD\n");
		return -1;
	}
	if (pId == 0)
	{
		signal(SIGCONT, whenToUnpause);
		pause();
		char str1Mem[LINELEN+1] = {0};
		char str2Mem[LINELEN+1] = {0};
		sscanf((char*)sharde_memory_res,"%s %s",str1Mem,str2Mem);
		int temp = mystrxor(str1Mem,str2Mem);
		sprintf(sharde_memory_res,"%d",temp);
	}
	else
	{
		
		
			printf("Please enter string 1:\n");
			if (mygets(str1, LINELEN) == NULL)
				return -1;
			printf("Please enter string 2:\n");
			if (mygets(str2, LINELEN) == NULL)
				return -1;
			fflush(stdout);
			strcat(str1,"\n");
			strcat(str2,"\n");
			sprintf((char*)sharde_memory_res,"%s %s",str1,str2);
			kill(pId,SIGCONT);
			wait(NULL);
			int res;
			sscanf((char*)sharde_memory_res,"%d",&res);
			printf("The result is: %d\n", res);
			fflush(stdin);
		
		status = 1;
	}

	return status;
}

