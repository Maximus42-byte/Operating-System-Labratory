#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <signal.h> 
#define MAXCHILD 5
#define maximum 8
int counter = 0;

void handler1(int signo) 
{ 
  switch(signo) 
  { 
  case SIGUSR1: 
	counter++;
    printf("SIGUSR1 Signal received \n"); 
    printf("COUNTER IS = %d   \n" , counter); 
	if (counter >= maximum){
	exit(0);
}
  break;  
  } 
} 

int main() 
{ 
int t =1;
int i;
  pid_t pid[MAXCHILD]; 
 struct sigaction action1; 
  action1.sa_handler = handler1; 
  action1.sa_mask =(sigset_t){0}; 
  action1.sa_flags = 0; 
  sigaction(SIGUSR1,(struct sigaction *) &action1,NULL); 
 pid_t parent_pid = getpid();		
  for (i=0;i<MAXCHILD;i++) 
  { 
    pid[i]=fork(); 
   
  } 
while(1){
  for (i=0;i<MAXCHILD;i++) 
  { 
    if (pid[i]== 0 ){
 //printf("this is Child\n"); 
    sleep(t); 
kill(parent_pid,SIGUSR1);
	}
}
  } 
    
  return 0; 
}
