#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
int main()
{
	pid_t p1;
	while(1)
	{

		p1 = fork();
		if ( p1 == 0)
		{
			printf("process ID is %d \n",getpid());
			break;
			
		}
		sleep(2);
	}

}
