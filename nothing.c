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
		//strings[i][5] = i+1;
		strings[i][5] = '\0';
		//printf("%s\n", strings[i]);
	}
}
int main() {
    generateStrings();
    char fn[]="temp.fifo";
    int wfd;
    //mkfifo(fn, 0666);
    for(int i = 0; i<50; i+=5){
	char buffer[10][6];
	for(int j = 0; j<10; j+=2){
		for(int k = 0; k<6; k++){
			buffer[j][k] = strings[i+j][k];
		}
		sprintf(buffer[j+1], "%d", i+j/2);
		//itoa(i+j, buffer[j+1], 10);
	}
	mkfifo(fn, 0666);
    	int pid = fork();
    	if(pid==0){
    		execv("./moth", NULL);
   	 }else{
  	//printf("Parent\n");
		wfd= open(fn, O_WRONLY);
		write(wfd, buffer, 10*6);
	//	write(wfd, strings[i], strlen(strings[i])+1);
		//write(wfd, strings[1], strlen(strings[0])+1);
		//printf("String 1\n");
		//write(wfd, strings[0], strlen(strings[1])+1);
		//printf("String 2\n");
		close(wfd);
		wait(NULL);
		//printf("%s\n", buffer[9]);
		//printf("%d %d %d %d %d\n", i, i+1, i+2, i+3, i+4);
		unlink(fn);
    	}
   }
    printf("%s\n", strings[48]);
    printf("%s\n", strings[49]);
	//unlink(fn);
  return 0;
}
