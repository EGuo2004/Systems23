#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  char line[BUFFER_SIZE];
  while(1) {
	  from_client = server_setup();
	  int f = fork();
	  if(f) {
		  //parent(server)
		  remove(WKP);
	  } else { 
		  //child(subserver)
		  to_client=server_connect(from_client);
		  while(1) {
		  if((read(from_client,line,BUFFER_SIZE)) == 0) {
			  break;
		  }
		  int counter;
		  for(counter = 0; counter < strlen(line); counter++) {
			  line[counter] = toupper(line[counter]);
		  }
		  write(to_client, line, BUFFER_SIZE);
  	      }
      }
   }
}