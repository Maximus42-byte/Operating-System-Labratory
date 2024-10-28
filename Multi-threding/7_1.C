#include <stdio.h> 
#include <string.h> 
#include <pthread.h> 
#include <semaphore.h>
#define THREADS 4 
sem_t sem1; 
int a[8] = {1,2,3,4,5,6,7,8};
int b[8] = {1,1,1,1,1,1,1,1};
int product = 0;
void *routine1(int x) 
{ 
int i , sum = 0;
    //printf("threadIdx = %d\n",x);    
for (int i=(int)x; i<8; i+=THREADS) 	
	{ 
sum+= a[i]*b[i];
}
printf("threadIdx = %d and the sum is == %d  \n",x , sum);  
sem_wait(&sem1);
product += sum;
sem_post(&sem1);
    //pthread_exit((void *)x); 
} 
int main() 
{ 
sem_init(&sem1,0,1);
  pthread_t threads[THREADS]; 
  for ( int i=0;i<THREADS;i++) 
    pthread_create(&threads[i], NULL, routine1, (void *)i );
  //int retval; 
  for (int i=0; i<THREADS; i++) 	
	{ 
          pthread_join(threads[i],NULL); 
          printf("threadIdx %d finished \n",i); 
  	} 
printf("the product is = %d  \n", product);
  return 0; 
}
