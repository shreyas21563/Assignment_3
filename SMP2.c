#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main(){
	int shmid;
	char *addr;
	shmid = shmget(2009, 30, 0666);
	addr = shmat(shmid, NULL, 0);
	printf("%s", addr);
	char *token = strtok(addr, " ");
	char *previous;
	while(token!=NULL){
		previous = token;
		token = strtok(NULL, " ");
	}
	*addr = '\0';
	sprintf(addr, "%s%s", addr, previous);
	shmdt(addr);
	return 0;
}

























