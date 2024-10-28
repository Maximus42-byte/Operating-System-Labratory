#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#define MAXCHILD 5
int fd[2];
int fd2[2];
int lock = 0;
void handler1(int signo)
{
	int id , pid , pid2;
	switch(signo)
	{
		case SIGUSR1:
			printf("Interrupt Signal SIGUSR1\n");
			pid2 = getpid();
			write(fd[1],&pid2,sizeof(int));
			kill(getppid(),SIGUSR2);
			sleep(1);
			//counter++;
			break;
		case SIGUSR2:
			printf("Interrupt Signal SIGUSR2\n");
    	read(fd[0],&pid,sizeof(int));
			read(fd2[0],&id,sizeof(int));
			printf("child with id : %d has process id %d\n",id,pid);
			break;
	}
}
int main()
{
	struct sigaction action1;
	struct sigaction action2;
	sigset_t set1;
	//define signal set named "set1"
	sigemptyset(&set1);
	//making set1 empty
	sigaddset(&set1, SIGUSR2);//adding SIGUSR2 to set1
	action1.sa_handler = handler1;
	action1.sa_mask = set1;
	//set1 includes SIGUSR2, it means if during handling action1
	//SIGUSR2 will be blocked on delivery.
	action1.sa_flags = 0;
	action2.sa_handler = handler1;
	action2.sa_mask = (sigset_t){0};	//no signal has been blocked for action2
	action2.sa_flags = 0;
	//int inchild=0;
	//initializng parent process before fork()
	sigaction(SIGUSR1,(struct sigaction *) &action1,NULL);
	sigaction(SIGUSR2,(struct sigaction *) &action2,NULL);
	pid_t pid[MAXCHILD];
	pipe(fd);
	pipe(fd2);
	int inchild = 0;
 	int i;
	for(i=0;i<MAXCHILD;i++)
	{
		pid[i]=fork();
		if(pid[i]==0)
		{
			inchild = 1;
			write(fd2[1],&i,sizeof(int));
			break;
		}
		else
		{
			kill(pid[i],SIGUSR1);
			sleep(1);
		}
	}
//while (inchild == 0);

	return 0;
}
