#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

void error(const char* msg)
{
	perror(msg);
	exit(1);
}

void *service_client(void *args)
{
	service_client_args *arguments = (service_client_args *) args;
	int sockfd = arguments->sockfd;
	struct sockaddr_in client_addr = arguments->addr;
	char buffer[256];
	memset(buffer, 0, 255);
	int n = read(sockfd, buffer, 255);
	const char client_ip[INET_ADDRSTRLEN];
	unsigned short port = ntohs(client_addr.sin_port);
	inet_ntop(AF_INET, &client_addr.sin_addr, (char *) client_ip, INET_ADDRSTRLEN);
	if(n < 0)
	{
		fprintf(stderr, "[ERROR] could not read from socket with address %s\n", (char *) client_ip);
		return NULL;
	}
	printf("[%s:%hu] %s\n", (char *) client_ip, port, (char *) buffer);
	close(sockfd);
	return NULL;
}

int start_server(int port)
{
	int sockfd, newsockfd;
	socklen_t clilen;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr, client_addr;
	if(sockfd < 0)
		error("[ERROR] could not open socket\n");
	memset((char *) &server_addr, 0, sizeof(server_addr));		
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		error("[ERROR] could not bind socket\n");
	listen(sockfd, 5);
	clilen = sizeof(client_addr);
	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clilen);
		if(newsockfd < 0)
		{
			perror("[ERROR] could not accept connection\n");
			continue;
		}
		service_client_args args;
		memset(&args, 0, sizeof(args));
		args.sockfd = newsockfd;
		args.addr = client_addr;
		pthread_t thread_id;
		pthread_create(&thread_id, NULL, service_client, (void *) &args);
	}
	close(sockfd);
	return 0;
}

