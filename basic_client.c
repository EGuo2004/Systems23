#include "pipe_networking.h"


int main(int argc, char *argv[]) {

  int sd;

  sd = client_handshake();
  
  char line[100];
  while(1) {
    printf("What do you want?\n");
    fgets(line, BUFFER_SIZE, stdin);
    write(sd, line, BUFFER_SIZE);
		read(sd,line,BUFFER_SIZE);
		printf("Here:%s\n", line);

  }
}
