#include "pipe_networking.h"


int main() {
	int sd = server_setup();
    char line[BUFFER_SIZE];
    while(1) {
	  int returnthing = server_connect(sd);
	  int f = fork();
	  if(f) {
		  //parent(server)
		  remove(WKP);
	  } else { 
		  //child(subserver)
		  while(1) {
		  if((read(returnthing,line,BUFFER_SIZE)) == 0) {
			  break;
		  }
		  int counter;
		  for(counter = 0; counter < strlen(line); counter++) {
			  line[counter] = toupper(line[counter]);
		  }
		  write(returnthing, line, BUFFER_SIZE);
  	      }
      }
   }
}