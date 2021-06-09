#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "mystrlib.h"

#define LINELEN (80)

int main(int argc, char *argv[])
{
	char str1[LINELEN] = {0};
	char str2[LINELEN] = {0};

	while (1)
	{
	printf("Please enter string 1:\n");
	if (mygets(str1, LINELEN) == NULL)
		break;
	printf("Please enter string 2:\n");
	if (mygets(str2, LINELEN) == NULL)
		break;
	fflush(stdout);

	int pid = fork();
	int status = 0;
	if( pid  == 0){
		fflush(stdout);
		char* params[] = {"./argsxorstr", str1, str2, NULL};
		execve(params[0], params, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		if(WIFEXITED(status)){
			printf("result is: %d\n", WEXITSTATUS(status));
			}
		else
			return -1;
	}

	}
	return 0;
}
