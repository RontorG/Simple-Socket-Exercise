#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BSIZE 256


void error(char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[])
{
	int clientfd;
	char buffer[BSIZE];
	char *hostname, *port;
	struct addrinfo *serv_addr;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s [host] [port]\n", argv[0]);
		exit(2);
	}

	hostname = argv[1];
	port = argv[2];

	/* create client socket */
	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	if (clientfd < 0)
		error("ERROR couldn't open socket");

	if (getaddrinfo(hostname, port, 0, &serv_addr)) {
		fprintf(stderr, "ERROR host not found\n");
		exit(0);
	}
	
	if (connect(clientfd, serv_addr->ai_addr, serv_addr->ai_addrlen) < 0)
		error("ERROR couldn't connect");

	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, BSIZE, stdin); 
	if (send(clientfd, buffer, strlen(buffer), 0) < 0)
		error("Error sending message");

	return 0;
}
