#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<wait.h>
#include<time.h>
#define PORT 8090
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
int main(){
	generateStrings();
//	char buffer[1024];
	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	int opt = 1;
	int i = 0;
//	while(i<5){
	char *hello = "hello world";
		int server_fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in address;
		int addrlen = sizeof(address);
		address.sin_port = htons(PORT);
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt));
		bind(server_fd, (struct sockaddr*)&address, sizeof(address));
//	int i = 0;
	while(i<50){
		char buffer[10][6];
		for(int j = 0; j<10; j+=2){
			for(int k = 0; k<6; k++){
				buffer[j][k] = strings[i+j/2][k];
			}
			sprintf(buffer[j+1], "%d", i+j/2);
		}
		int pid = fork();
		if(pid==0){
			execv("./P2", NULL);
		}else{
			listen(server_fd, 1);
			int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
			send(new_socket, buffer[0], 60, 0);
			char moth[6];
			wait(NULL);
			read(new_socket, moth, 6);
			i = atoi(moth)+1;
		//	printf("%s\n", moth);
			close(new_socket);
			//shutdown(server_fd, SHUT_RDWR);
		}
//		i += atoi(moth)+1;
	}
	//close(new_socket);
	shutdown(server_fd, SHUT_RDWR);	
	clock_gettime(CLOCK_REALTIME, &t2);
	printf("TIME SOCKET: %f\n", (double)((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec))/(double)1000000000));
	return 0;
}
















