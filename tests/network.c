#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int create_sock() {
  int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1) return -1;
}

struct sockaddr_in init_server() {
  struct sockaddr_in server;
     server.sin_addr.s_addr = inet_addr("74.125.235.20");
     server.sin_family = AF_INET;
     server.sin_port = htons( 80 );
     return server;
}

int conn(struct sockaddr_in server, int socket_desc) {
          if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                return 1;
        }
	  return 0;
}

int main() {
	//Create socket
	int socket_desc = create_sock();
	if (socket_desc == -1) return 1;
		
	struct sockaddr_in server = init_server(server);
	
	//Connect to remote server	
   	return conn(server, socket_desc);
}
