#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main() {
  char fn[]="temp.fifo";
  int rfd;
  char in[10][6];
  rfd = open(fn, O_RDONLY);
  read(rfd, in, sizeof(in));
  close(rfd);
  for(int i = 0; i<10; i+=2){
  	printf("%s %d\n", in[i], atoi(in[i+1]));
  }
  rfd = open(fn, O_WRONLY);
  write(rfd, in[9], 6);
  close(rfd);
  return 0;
}
