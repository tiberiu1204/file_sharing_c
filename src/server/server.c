#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

void error(const char* msg)
{
	perror(msg);
	exit(1);
}

int start_server(int port)
{
	int sockfd, newsockfd, n;
	socklen_t clilen;
	char buffer[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr, client_addr;
	if(sockfd < 0)
		error("[ERROR] could not open socket");
	bzero((char *) &server_addr, sizeof(server_addr));		
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		error("[ERROR] could not bind socket");
	listen(sockfd, 5);
	clilen = sizeof(client_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clilen);
	if(newsockfd < 0)
		error("[ERROR] could not accept connection");
	bzero(buffer, 255);
	n = read(newsockfd, buffer, 255);
	if(n < 0) error("[ERROR] error while reading from socket");
	printf("Here is the message %s", buffer);
	return 0;
}

