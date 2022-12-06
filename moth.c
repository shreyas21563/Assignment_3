#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include<string.h>
int main() {
  char fn[]="temp.fifo";
  int rfd;
  char in[10][6];
  rfd = open(fn, O_RDONLY);
  read(rfd, in, sizeof(in));
  //sleep(2);
  //read(rfd, in[0], sizeof(in[0]));
  //sleep(2);
  //read(rfd, in[1], sizeof(in[1]));
  //printf("%s\n", in);
  //printf("In moth\n");
  for(int i = 0; i<10; i+=2){
  	printf("%s\n", in[i]);
  }
  printf("%s\n", in[9]);
 // printf("%s\n", in[5]);
  close(rfd);
  //unlink(fn);
  return 0;
}
