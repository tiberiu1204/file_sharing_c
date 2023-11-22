#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char* msg)
{
	perror(msg);
	exit(1);
}

int start_client(const char* host_name, int port) 
{
	int sockfd, n;
	struct sockaddr_in server_addr;
	struct hostent *server;
	char buffer[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("[ERROR] could not open socket (client)");
	server = gethostbyname(host_name);
	if(server == NULL)
	{
		fprintf(stderr, "[ERROR] no such host");
		exit(0);
	}
	memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	memcpy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port = htons(port);
	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		error("[ERROR] could not connect to host");
	printf("Please enter the message: \n");
	memset(buffer, 0, 255);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if(n < 0)
		error("[ERROR] writing to socket");
	memset(buffer, 0, 255);
	n = read(sockfd, buffer, 255);
	if(n < 0)
		error("[ERROR] reading from socket (client)");
	printf("%s", buffer);
	return 0;
}
