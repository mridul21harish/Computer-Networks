#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#define size 1024

int main()
{
	int s_socket; int socket_length;
	char buffer[size]; char m;
	s_socket = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ADDRESS_OF_SERVER; 
	struct sockaddr_in ADDRESS_OF_CLIENT;

	if(s_socket == -1)
	{
		printf("Socket Creation Failure\n");
		exit(EXIT_FAILURE);
	}

	ADDRESS_OF_SERVER.sin_family = AF_INET;
	ADDRESS_OF_SERVER.sin_port = htons(9009);
	ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

	if(bind(s_socket, (const struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER)) < 0)
	{
		printf("Binding to client failed\n");
		exit(EXIT_FAILURE);
	}

	socket_length = sizeof(ADDRESS_OF_SERVER);
	recvfrom(s_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&ADDRESS_OF_CLIENT, &socket_length);

	char filename[size];
	memset (filename, '\0', sizeof(filename));
	recvfrom(s_socket, filename, sizeof(filename), 0,(struct sockaddr *)&ADDRESS_OF_CLIENT ,&socket_length);
	printf("%s\n", filename);

	clock_t t = clock();

	FILE *fptr; 
	fptr = fopen(filename, "wb");
	if(fptr !=NULL)
	{	
		while(m != EOF)
		{	
			recvfrom(s_socket, &m, sizeof(m), 0, (struct sockaddr *)&ADDRESS_OF_CLIENT ,&socket_length);
			fputc(m, fptr);		
		}
	}

	fclose(fptr);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; //in seconds

	printf("File received successfully\n");
	printf("File received in %f seconds.\n", time_taken);
	
	close(s_socket);
	return 0;
}
