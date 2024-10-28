#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <math.h> 

#define size 7
#define THREADS 4 

sem_t sem1; 
 
int a[7] = {1,2,3,0,4,5,-9};

int stride = ceil(size / 2.0);
void *routine1(void * x) 
{ 
int i = (int)x;

    printf("threadIdx = %d\n",x);    

sem_wait(&sem1);
 if (a[i]>a[i+stride]){
a[i] = a[i+stride];
}
sem_post(&sem1);
   // pthread_exit((void *)x); 
} 
int main() 
{ 
sem_init(&sem1,0,1);
while(1){
if (stride == 0){
break;
}
  pthread_t threads[stride]; 
  for ( int i=0;i<stride;i++) 
    pthread_create(&threads[i], NULL, routine1, (void *)i );
 
  for (int i=0; i<THREADS; i++) 	
	{ 
          pthread_join(threads[i],NULL); 
          printf("threadIdx %d finished \n",i); 
  	} 
stride = (stride/2);
}
printf("the minimum is = %d  \n", a[0]);
  return 0; 
}
