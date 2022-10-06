#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<libgen.h>

#define MAX 1024

int main()
{
	int c_socket; int socket_length; int m;
	char buffer[MAX]; char filepath[MAX];

	c_socket = socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in ADDRESS_OF_CLIENT;

	if(c_socket == -1)
	{
		printf("Socket creation has failed\n");
		exit(EXIT_FAILURE);
	}

	ADDRESS_OF_CLIENT.sin_family=AF_INET;
	ADDRESS_OF_CLIENT.sin_addr.s_addr=INADDR_ANY;
	ADDRESS_OF_CLIENT.sin_port=htons(9009);
	
	socket_length = sizeof(struct sockaddr_in);
	
	if(connect(c_socket,(struct sockaddr *) &ADDRESS_OF_CLIENT, socket_length) == 0)
	{ 
		printf("Connect Succesful\n");
	}
	
	printf("Enter the path of the file to be transferred\n");
	scanf("%s", filepath);

	char *filename = basename(filepath);
	
	send(c_socket, filename, strlen(filename), 0);
	
	FILE *fptr;
	fptr = fopen(filepath, "rb");
	
	if(fptr == NULL)
	{
		printf("File does not exist\n");
		exit(EXIT_FAILURE);
	}
	

	while(m = fread(buffer, 1, sizeof(buffer), fptr) > 0)
	{
		send(c_socket, buffer, m, 0);
	}
	
	printf("File transferred successfully\n");
	
	fclose(fptr);
	close(c_socket);	
	return 0;
}

