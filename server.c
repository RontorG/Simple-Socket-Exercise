#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[]) 
{
	struct sockaddr_in server, client;
	int serverfd, clientfd, csize, port;
	char buffer[256];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		exit(2);
	}

	port = atoi(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
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
		printf("Message received:\n\t%s\n", buffer);
		memset(buffer, 0, sizeof(buffer));
		close(clientfd);
	}

	close(serverfd);
	return 0;
}
