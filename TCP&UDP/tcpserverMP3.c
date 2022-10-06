#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<libgen.h>

#define MAX 1024

int main()
{
	int s_socket; int c_socket; int socket_length; int m;
	char buffer[MAX]; char filename[MAX];
	
	s_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ADDRESS_OF_SERVER; 
	struct sockaddr_in ADDRESS_OF_CLIENT;
	
	if(s_socket == -1)
	{
		printf("Socket creation has failed\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&ADDRESS_OF_SERVER, 0, sizeof(ADDRESS_OF_SERVER));
	memset(buffer, 0, sizeof(buffer));
	
	ADDRESS_OF_SERVER.sin_family=AF_INET;
	ADDRESS_OF_SERVER.sin_addr.s_addr=INADDR_ANY;
	ADDRESS_OF_SERVER.sin_port=htons(9009);
	
	if((bind(s_socket, (const struct sockaddr *)&ADDRESS_OF_SERVER,sizeof(ADDRESS_OF_SERVER))) < 0)
	{
		printf("Binding with the client failed\n");	
		exit(EXIT_FAILURE);
	}

	if((listen(s_socket,10)) == 0) 
		printf("listen sucessful\n");	
		
	socket_length = sizeof(struct sockaddr_in);	
	
	if((c_socket=accept(s_socket,(struct sockaddr *)&ADDRESS_OF_CLIENT,&socket_length)) > 0)
		printf("accept sucessful\n");	
	
	memset(filename, 0, sizeof(filename));
	recv(c_socket, filename, sizeof(filename), 0);
	printf("%s\n", filename);

	FILE *fptr;
	fptr = fopen(filename, "wb");
	
	if(fptr == NULL)
	{
		printf("File does not exist\n");
		exit(EXIT_FAILURE);
	}
	
	while(m = recv(c_socket, buffer, sizeof(buffer), 0) > 0)
	{
		fwrite(buffer, 1, m, fptr);
	}
	
	printf("File recieved succesfully\n");
	
	fclose(fptr);
	close(c_socket);
	close(s_socket);
	return 0;
}

