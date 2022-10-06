#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define MAX 1024

struct message
{
    int seq;
    char buffer[MAX];
    int size;
};

int main() 
{
	int s_socket; int socket_length;
	char buffer[MAX];
	char fileName[MAX];
	struct sockaddr_in ADDRESS_OF_SERVER;
	struct sockaddr_in ADDRESS_OF_CLIENT; 
	struct timeval start; 
	struct timeval end;
	
	if ((s_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		printf("Socket could not be created.\n");
		exit(EXIT_FAILURE);
	}
	
	ADDRESS_OF_SERVER.sin_family = AF_INET;
	ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;
	ADDRESS_OF_SERVER.sin_port = htons(9009);
	
	if (bind(s_socket, (const struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER)) < 0)
	{
		printf("Could not bind with the client.\n");
		exit(EXIT_FAILURE);
	}
	
	int n;
   	socket_length = sizeof(ADDRESS_OF_CLIENT);

    	memset(fileName, '\0', sizeof(fileName));
    	recvfrom(s_socket, fileName, sizeof(fileName), 0, (struct sockaddr *)&ADDRESS_OF_CLIENT, &socket_length);
    	printf("%s\n", fileName);

    	FILE* fptr = fopen(fileName, "wb");

   	int b; int i = 0; int total = 0;
    	struct message data;
		gettimeofday(&start, NULL);
 	while(1)
 	{
		i = i+1;
		a: 
			n = recvfrom(s_socket, &data, sizeof(data), 0, (struct sockaddr *)&ADDRESS_OF_CLIENT, &socket_length);
			total = total + data.size;
		
		if(data.seq == -1) 
			break;
		if(i != data.seq)
		{
			sendto(s_socket, "y", 1, 0, (struct sockaddr *)&ADDRESS_OF_CLIENT, socket_length);
			goto a;
		}
		else 
			sendto(s_socket, "n", 1, 0, (struct sockaddr *)&ADDRESS_OF_CLIENT, socket_length);
        
        fwrite(data.buffer, 1, data.size, fptr);
    	}	
	
	gettimeofday(&end, NULL);
	double time = (double)(end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);
    
    	printf("File received..\nNumber of bytes transferred: %g MiB.\nTime taken to transfer the file: %f seconds.\n", (float)total / 1000000, time);

    	fclose(fptr);
	close(s_socket);
	return 0;
}
