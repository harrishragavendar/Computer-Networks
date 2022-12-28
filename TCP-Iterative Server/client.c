#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080
void serverChat(int sid)
{
	int check;
	char clientData[30],serverData[30];
	strcpy(clientData,"");
	strcpy(serverData,"");
 	while(1)
	{
		printf("\nClient : ");
		scanf("%s",clientData);
		write(sid, clientData, sizeof(clientData));
		check = read( sid , serverData, 30);
		printf("\nServer : %s",serverData);
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
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char hello[10];
	strcpy(hello,"Client 1");
	char buffer[30];
 	strcpy(buffer,"");
 	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket Creation Failed\n");
		return -1;
	}
 	printf("\nSocket Created");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 	if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	printf("\nConnection to Server Created");
	write(sock , hello , sizeof(hello));
	printf("\nClient Request Sent\n");
	read(sock,buffer,30);
	printf("\nResponse From Server : %s",buffer);
	serverChat(sock);
	close(sock);
 	return 0;
}