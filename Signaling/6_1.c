#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <signal.h> 

#define max_try 5
int counter = 0;

void handler1(int signo) 
{ 
  switch(signo) 
  { 
  case SIGINT: 
	counter++;
    printf("Interrupt Signal received \n"); 
     if (counter == max_try){
	exit(0);
		break;
		}
  } 
} 
int main() 
{ 
  //initializing sigaction structure 
  struct sigaction action1; 
  action1.sa_handler = handler1; 
  action1.sa_mask =(sigset_t){0}; 
  action1.sa_flags = 0; 
  sigaction(SIGINT,(struct sigaction *) &action1,NULL); 
  //runnign forever, while process is sensitive to SIGINT 
  while(1); 
  return 0; 
}
