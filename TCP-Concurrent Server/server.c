#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sock_id, bind_status, accept_status;
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

	bind_status = bind(sock_id, (struct sockaddr*)&server, sizeof(server));
	if(bind_status != -1)
		printf("Binded Successfully\n");
	else
		printf("Bind Failed\n");

	listen(sock_id, 3);

	int client_size = sizeof(client);
	do
	{
		accept_status = accept(sock_id, (struct sockaddr*)&client, &client_size);
		if(accept_status != -1)
			printf("\nClient Accepted\n");
		else
			printf("\nClient Accept Failed\n");
		if(fork()==0)
		{
			do
			{
				recv(accept_status, num, sizeof(num), 0);
				if(num[0]==100)
					break;
				printf("Received number: %d from client %d\n",num[0],num[1]);
                int n=num[0];
                num[0]=num[0]*num[0];
                printf("Square of %d is %d\n",n,num[0]);
				send(accept_status, num, sizeof(num), 0);
                printf("Sent square to client %d\n",num[1]);
				if(num[0]==100)
					break;
			}while(num[0]!=100);
		}
		printf("Client Closed\n");
	}while(num[0]!=100);
	close(sock_id);
}