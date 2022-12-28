#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id, bind_status, connect_status;
	struct sockaddr_in server, client;
	int num[4];

	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id != -1)
		printf("Socket Created\n");
	else
		printf("Socket Creation Failed\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(8081);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	connect_status = connect(sock_id, (struct sockaddr*)&server, sizeof(server));
	if(connect_status != -1)
		printf("Connected Successfully\n");
	else
		printf("Connection Failed\n");

	do
	{
		printf("Enter a number: ");
		scanf("%d", &num[0]);
		num[1]=1;
		send(sock_id, num, sizeof(num), 0);
		if(num[0]==100)
			break;
		recv(sock_id, num, sizeof(num), 0);
		printf("Square of the number is: %d\n",num[0]);
		if(num[0]==100)
			break;
	}while(num[0]!=100);
	close(sock_id);
}