#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char* msg)
{
	perror(msg);
	exit(1);
}

int start_client(char* host_name, int port) 
{
	int sockfd, n;
	struct sockaddr_in server_addr;
	struct hostent *server;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("[ERROR] could not open socket (client)");
	server = gethostbyname(host_name);
	if(server == NULL)
	{
		fprintf(stderr, "[ERROR] no such host");
		exit(0);
	}
}
