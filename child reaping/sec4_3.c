#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <time.h> 
#include <fcntl.h>
 
int main(int argc,char ** argv) 
{ 
  struct timeval start,stop; 
char s1[256];
char s2[256];
bzero(s1,256);
bzero(s2,256);
int fp;
time_t t1;
time(&t1);
struct tm * timeinfo = localtime(&t1);
fp = open("log.txt",O_CREAT|O_WRONLY|O_APPEND,00777);
while(1)
{
scanf("%s",s1);
  gettimeofday(&start,NULL); 
 system(s1);
  //sleep(3); 
 
  gettimeofday(&stop,NULL); 
 
  long sec=stop.tv_sec-start.tv_sec; 
  float m1=start.tv_usec; 
  float m2=stop.tv_usec; 
long elapsed = sec*1000+(m2-m1)/1000;
sprintf(s2,"Date:%d-%d-%d\t Time:%ld msecs path:%s\n",
timeinfo->tm_year + 1900,timeinfo->tm_mon ,
 timeinfo->tm_mday,elapsed,s1);
write(fp , s2 , strlen(s2));	
bzero(s1,256);
bzero(s2,256);

} 
   

 
  return 0; 
} 
