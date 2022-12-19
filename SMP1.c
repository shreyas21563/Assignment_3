#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
char strings[50][5];
void generateStrings(){
	char a[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST";
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 0; i<50; i++){
		for(int j = 0; j<5; j++){
			strings[i][j] = a[rand()%strlen(a)];
		}
	}
}
int main(){
	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	generateStrings();
//	struct timespec t1, t2;
	int shmid;
	char *shm[5];
	char *addr;
	//clock_gettime(CLOCK_REALTIME, &t1);
	shmid = shmget(2009, 30, 0666|IPC_CREAT);
	addr = (char*) shmat(shmid, NULL, 0);
	int k = 0;
	while(k<50){
		*addr = '\0';
		for(int i = k; i<k+5; i++){
			for(int j = 0; j<5; j++){
				sprintf(addr, "%s%c", addr, strings[i][j]);
			}
			sprintf(addr, "%s %d\n", addr, i);
		}
		int pid = fork();
		if(pid==0){
			execv("./P2", NULL);
		}else{
			wait(NULL);
			k = 1 + atoi(addr);
		//	printf("%d\n", x);
			//shmdt(addr);
			//shmctl(shmid, IPC_RMID, NULL);
		}
	}	
	shmdt(addr);
	shmctl(shmid, IPC_RMID, NULL);
	clock_gettime(CLOCK_REALTIME, &t2);
	printf("Shared Memory Time: %f\n", (double)((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec))/(double)1000000000L));
	return 0;

}
















