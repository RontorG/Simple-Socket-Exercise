#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(char *msg)
{
	perror(msg);
	exit(1);
}


int main() 
{
	struct sockaddr_in server, client;
	int serverfd, clientfd, csize;
	char buffer[256];

	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	server.sin_addr.s_addr = INADDR_ANY;
	
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd < 0)
		error("ERROR couldn't open socket");

	if (bind(serverfd, (struct sockaddr*) &server, sizeof(server)) < 0)
		error("ERROR couldn't bind socket to the address");

	listen(serverfd, 5);

	csize = sizeof(client);
		 	
	while (1) {
		printf("Waiting for connections...\n");
		clientfd = accept(serverfd, (struct sockaddr*) &client, &csize);
		recv(clientfd, buffer, sizeof(buffer), 0);  
		printf("\nMessage received:\n\t%s", buffer);
		close(clientfd);
	}

	close(serverfd);
	return 0;
}
