#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<wait.h>
#include<stdlib.h>
#include<time.h>
char strings[50][6];
void generateStrings(){
	char a[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 0; i<50; i++){
		for(int j = 0; j<5; j++){
			strings[i][j] = a[rand()%strlen(a)];
		}
		strings[i][5] = '\0';
	}
}
int main() {
    generateStrings();
    struct timespec t1, t2;
    char fn[]="temp.fifo";
    int wfd;
    int i = 0;
    clock_gettime(CLOCK_REALTIME, &t1);
    while(i<50){
	char buffer[10][6];
	for(int j = 0; j<10; j+=2){
		for(int k = 0; k<6; k++){
			buffer[j][k] = strings[i+j/2][k];
		}
		sprintf(buffer[j+1], "%d", i+j/2);
	}
	mkfifo(fn, 0666);
    	int pid = fork();
    	if(pid==0){
    		execv("./moth", NULL);
   	 }else{
		wfd= open(fn, O_WRONLY);
		write(wfd, buffer, 10*6);
		close(wfd);
		char next[6];
		wfd = open(fn, O_RDONLY);
		read(wfd, next, sizeof(next));
		close(wfd);
		int n = atoi(next);
		i = n+1;
	//	unlink(fn);
    	}
   }
    clock_gettime(CLOCK_REALTIME, &t2);
    printf("TIME FIFO: %f\n", (double)((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec))/(double)1000000000L));
    unlink(fn);
  return 0;
}
