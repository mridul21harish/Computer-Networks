#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<libgen.h>
#include<time.h>

#define size 1024

int main()
{
	int c_socket; int socket_length;
	char filepath[size]; char n;
	
	c_socket = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ADDRESS_OF_SERVER;
	
	if(c_socket == -1)
	{
		printf("Socket Creation Failure\n");
		exit(EXIT_FAILURE);
	}

	ADDRESS_OF_SERVER.sin_family = AF_INET;
	ADDRESS_OF_SERVER.sin_port = htons(9009);
	ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

	socket_length = sizeof(ADDRESS_OF_SERVER);

	sendto(c_socket,"Hello server", strlen("Hello server"), 0, (struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));

	printf("Enter the path of the MP3 file you wish to send : ");
	scanf("%s",filepath);
	char *filename = basename(filepath); 
	printf("%s\n", filename);

	sendto(c_socket, filename, strlen(filename), 0,(struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));

	FILE *fptr;
	fptr = fopen(filepath,"rb");
	if (fptr == NULL)
	{
		printf("File does not exist\n");
		exit(EXIT_FAILURE);
	}

	clock_t t = clock();

	while((n = fgetc(fptr)) != EOF)
	{	
		sendto(c_socket, &n, sizeof(n), 0,(struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));
		sleep(0);
	}

	sendto(c_socket, &n, sizeof(n), 0, (struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));

	fclose(fptr);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; 

	printf("File sent successfully\n");
	printf("File transfer took %f seconds to execute.\n", time_taken);

	close(c_socket);
	return 0;
}
