#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define MAX 1024

int main()
{
	int c_socket = 0; int b; 
	struct sockaddr_in ADDRESS_OF_CLIENT; //this is for defining the address of the client
	c_socket = socket(AF_INET, SOCK_STREAM, 0); //this is for the reation of the client socket
	
	memset(&ADDRESS_OF_CLIENT, 0, sizeof(ADDRESS_OF_CLIENT)); //this is for filling the client address with 0s
	ADDRESS_OF_CLIENT.sin_family = AF_INET;
    	ADDRESS_OF_CLIENT.sin_port = htons(8080);
    	ADDRESS_OF_CLIENT.sin_addr.s_addr = INADDR_ANY;

    	b = connect(c_socket, (struct sockaddr *)&ADDRESS_OF_CLIENT, sizeof(ADDRESS_OF_CLIENT));
    	if (b == -1)
    	{
        	printf("Could not connect to the server.\n");
        	exit(EXIT_FAILURE);
    	} //this is for checking if the client has successfully connected with the server or not
    	
    	int exitloop = 0; 
    	while(exitloop == 0)
    	{
    		int window = 0;
    		printf("\nEnter the window size: \n");
        	scanf("%d", &window); //sliding window protocol uses a window of bytes, this is for defining the size of that window
    		
    		char message[MAX] = {0};
    		printf("Enter message to be sent : ");
    		scanf("%s", message);
    	
    		char ack[2];
    		ack[0] = '1';
    		ack[1] = '\0';
    	
    		char buffer[2]; 
    		buffer[0] = '1';
    		buffer[1] = '\0';
    		   		
    		char exit[2];
    		exit[0] = '0';
    		exit[1] = '\0'; 	
		//this is the simulation of the packet sending process with each byte equivalent to 1 packet
		
		int index = 0;
		while(index < strlen(message))
		{
			send(c_socket, exit, sizeof(exit), 0);
			for(int i = 0; i < window; i = i+1)
			{
				printf("Sending byte : %c\n", message[index + i]); 
				buffer[0] = message[index + i];
				send(c_socket, buffer, sizeof(buffer), 0); //this is sending of message byte by byte
			}
			int check = -1;
			for(int i = 0; i < window; i = i+1)
			{
				recv(c_socket, ack, sizeof(ack), 0); //this is recieving acknowledgment from the server
				printf("Acknowledgment : %s\n", ack);
				if(ack[0] == '0')
				{
					check = i;
					i = window; //this is for if a certain packet in a frame is lost(ack = 0), then the next fram will start from that point only
				}
			}
			if(check == -1)
			{
				index = index + window; //this is when acknowledgment is not given, it resends from that packet onwards in a frame
			}
			else
			{
				index = index + check;
			}
		}
		exit[0] = '1';
		send(c_socket, exit, sizeof(exit), 0);
		
		close(c_socket); //close the client socket
	
		printf("\n0 - Continue\n1- Exit\n");
    		scanf("%d", &exitloop);
    	}
    	return 0;
}	
				
			
