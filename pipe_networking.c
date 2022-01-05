#include "pipe_networking.h"

/*=========================
  server_setup
  args:
  creates the WKP (upstream) and opens it, waiting for a
  connection.
  removes the WKP once a connection has been made
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  printf("Creating WKP\n");
  int check = mkfifo(WKP,0644);
  if(check == -1) {
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  printf("Opening WKP\n");
  int from_client = open(WKP,O_RDONLY);
  if(from_client == -1) {
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  printf("Removing WKP\n");
  remove(WKP);

  return from_client;

}

/*=========================
  server_connect
  args: int from_client
  handles the subserver portion of the 3 way handshake
  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {

  // printf("Creating and Reading Into Secret Name\n");
  // char* secret = calloc(HANDSHAKE_BUFFER_SIZE, sizeof(char));
  // read(from_client, secret, HANDSHAKE_BUFFER_SIZE);

  // printf("Opening Secret\n");
  // int to_client = open(secret,O_WRONLY);

  // printf("Writing to ACK\n");
  // write(to_client,ACK,sizeof(ACK));

  // printf("Recieving Response\n");
  // char* returnval = calloc(HANDSHAKE_BUFFER_SIZE, sizeof(char));;
  // read(from_client, returnval, HANDSHAKE_BUFFER_SIZE);
  // printf("Response:%s\n",returnval);

  // return to_client;

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_UNPSEC;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  if((getaddrinfo(NULL, 9845, hints, &results)) == -1) {
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  bind(sd, results->ai_addr, results->ai_addrlen);
  listen(sd, 10);
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

  free(hints)
  freeaddrinfo(results);
}

/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  // printf("Creating FIFO\n");
  // char *secret = calloc(HANDSHAKE_BUFFER_SIZE, sizeof(char));;
  // sprintf(secret, "%d", getpid());
  // mkfifo(secret, 0644);

  // printf("Opening WKP\n");
  // *to_server = open(WKP,O_WRONLY);

  // printf("Writing to Secret\n");
  // write(*to_server,secret,HANDSHAKE_BUFFER_SIZE);

  // printf("Opening Secret\n");
  // int from_server = open(secret, O_RDONLY);

  // printf("Reading Secret\n");
  // char *ack = calloc(HANDSHAKE_BUFFER_SIZE, sizeof(char));
  // read(from_server, ack, HANDSHAKE_BUFFER_SIZE);

  // printf("Recieved Secret Name:%s\n", ack);

  // printf("Removing Secret\n");
  // remove(secret);

  // if (!strcmp(ack, ACK)) {
  //     write(*to_server, "Complete", strlen("Complete"));
  // }

  // return from_server;

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_UNPSEC;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  if((getaddrinfo(NULL, 9845, hints, &results)) == -1) {
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);
}