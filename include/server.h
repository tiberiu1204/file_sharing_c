#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>

typedef struct service_client_args
{
	int sockfd;
	struct sockaddr_in addr;

} service_client_args;

int start_server(int port);

#endif
