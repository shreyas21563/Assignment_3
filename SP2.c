#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#define PORT 8090

int main(){
	char buffer[10][6];
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	int fd = connect(sock, (struct sockaddr*)&address, sizeof(address));
	//send(sock, hello, strlen(hello), 0);
	int valread = read(sock, buffer, 60);
	for(int i = 0; i<10; i+=2){
		printf("%s %s\n", buffer[i], buffer[i+1]);
	}
	send(sock, buffer[9], 6, 0);
	close(fd);
	return 0;
}














