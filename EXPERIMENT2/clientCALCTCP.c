#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include<unistd.h>
#include<string.h> 
#include<strings.h>
#include<arpa/inet.h>

#define buffsize 150

void main()
{
int c_socket; int socket_length; int n;
int operation; char buffer[buffsize];
int op1,op2,result;

c_socket = socket(AF_INET, SOCK_STREAM,0);
struct sockaddr_in ADDRESS_OF_SERVER;

if(c_socket == -1)
{
	printf("Socket creation has failed\n");
	exit(EXIT_FAILURE);
}

ADDRESS_OF_SERVER.sin_family=AF_INET;
ADDRESS_OF_SERVER.sin_addr.s_addr=INADDR_ANY;
ADDRESS_OF_SERVER.sin_port=htons(9009);

socket_length = sizeof(struct sockaddr_in);

if(connect(c_socket,(struct sockaddr *) &ADDRESS_OF_SERVER, socket_length) == 0)
{ 
	printf("Connect Succesfull\n");
}

memset(&buffer,0,sizeof(buffer));
n = recv(c_socket,buffer,buffsize,0);
printf("Server - %s\n",buffer);
scanf("%d",&op1);
send(c_socket, &op1, sizeof(int),0);

memset(&buffer,0,sizeof(buffer));
n = recv(c_socket,buffer,buffsize,0);
printf("Server - %s\n",buffer);
scanf("%d",&op2);
send(c_socket, &op2, sizeof(int),0);

memset(&buffer,0,sizeof(buffer));
n = recv(c_socket,buffer,buffsize,0);
printf("Server - %s\n",buffer);
scanf("%d",&operation);
send(c_socket, &operation, sizeof(int),0);

recv(c_socket, &result, sizeof(int),0);

printf("Final result from server = %d\n",result);  

close(c_socket);
}
