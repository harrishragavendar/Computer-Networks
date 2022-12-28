#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
void clientChat(int sid)
{
	int check;
	char clientData[30],serverData[30];
	strcpy(clientData,"");
	strcpy(serverData,"");
 	while(1)
	{
		check = read(sid ,clientData, 30);
		printf("\nClient : %s",clientData);
		printf("\nServer : ");
		scanf("%s",serverData);
		write(sid, serverData, sizeof(serverData));
  		if(strcmp(clientData,"end")==0)
		{
			printf("\nClient Connection Terminated");
			break;
  		}
		strcpy(clientData,"");
		strcpy(serverData,"");
 	}
}
int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char inbuffer[20],outbuffer[20];
	strcpy(inbuffer,"");
	strcpy(outbuffer,"");
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
 	printf("\nSocket created");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	if(bind(server_fd,(struct sockaddr*)&address, sizeof(address)) < 0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
 	printf("\nBinded successfully");
	if(listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
 	printf("\nListening for client");
	for(int k=0;k<4;k++)
	{ 
 		printf("\nWating for Client");
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address,&addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("\nClient Connection is Accepted");
		valread = read( new_socket , inbuffer, 20);
		printf("\nClient name : %s\n",inbuffer);
		strcpy(outbuffer,"Connected");
		write(new_socket,outbuffer,sizeof(outbuffer));
		clientChat(new_socket);
		close(new_socket);
	}
 	return 0;
}