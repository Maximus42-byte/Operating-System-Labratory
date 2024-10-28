#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<time.h>

#define MAXCHILD 8
void child_func(){
srand(time(NULL)+getpid());
int a = rand()%5;
sleep(a);
printf("this is child with process id %d , waiting for %d ,seconds\n",getpid(),a);
exit(0);
}

int main()
{
	pid_t p1[MAXCHILD];
	int i , a,status =0;
	for (i = 0 ;i<MAXCHILD;i++){
	p1[i] = fork();
	if (p1[i] == 0){
		child_func();
		}	
	} 
	while(1)
	{
	sleep(5);
	for (i = 0 ;i<MAXCHILD;i++){
	a=waitpid(p1[i],&status,WNOHANG);
	if (a!=0){
	printf("child number %d is dead\n",i);
	p1[i] = fork();
	if (p1[i] == 0){
		child_func();
		}	
	}
	else{
	printf("child number %d is alive\n",i);
	}	
	}
	}
}
