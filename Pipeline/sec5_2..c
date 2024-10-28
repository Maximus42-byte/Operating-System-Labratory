//9427993
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<signal.h>
#define maxchild 5
int fd[maxchild][2];
char buffer[256];
void child_work(int id){
	srand(time(NULL));
	int r;
	while(1){ 
		r=rand()%5;
		sprintf(buffer,"%d",r);
		write(fd[id][1],buffer,strlen(buffer));
		sleep(1);
	}
}


int main(){
	int total=0;
	int max=20;
	int i;
	int j;
	int k;
	pid_t pid[maxchild];
	for (i=0;i<maxchild;i++){
		pipe(fd[i]);
		pid[i]=fork();
		if(pid[i]==0){
			child_work(i);
		}
		else{
			char buffer2[256];
			while(total<max){
			for(j=0;j<maxchild;j++){
				read(fd[i][0],buffer2,255);
				total=total+atoi(buffer2);
				printf("%d\n",total);
				if(total>max){
					break;
					}
			}
				
			}
			for(k=0;k<maxchild;k++){
			kill(pid[k],SIGKILL);
			}
		}

	}
}
