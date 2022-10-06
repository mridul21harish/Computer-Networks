#include<stdio.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define MAX 1024

int main()
{
	int s_socket; int c_socket; int socket_length;
	s_socket = socket(AF_INET, SOCK_STREAM, 0); //this is for the creation of the server socket
	
	struct sockaddr_in ADDRESS_OF_SERVER; //this is for defining the address of the server
    	struct sockaddr_in ADDRESS_OF_CLIENT; //this is for defining the address of the client
    	
    	memset(&ADDRESS_OF_SERVER, 0, sizeof(ADDRESS_OF_SERVER)); //this is for filling the server address with 0s
    	memset(&ADDRESS_OF_CLIENT, 0, sizeof(ADDRESS_OF_CLIENT)); //this is for filling the client address with 0s
    	
    	ADDRESS_OF_SERVER.sin_family = AF_INET;
    	ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;
    	ADDRESS_OF_SERVER.sin_port = htons(8080);
    	
    	if(bind(s_socket, (struct sockaddr*)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER)) == -1)
    	{
        	printf("Could not bind the server..\n");
        	return 1;
    	} 
    	else
    	{
        	printf("\nServer Running...\n");
        	listen(s_socket,5);
    	} //this is for checking if server has succesfully binded or not
    	
    	socket_length = sizeof(ADDRESS_OF_CLIENT);
    	c_socket = accept(s_socket, (struct sockaddr*)&ADDRESS_OF_CLIENT, &socket_length);
    	
    	if (c_socket == -1)
    		return 1;
    	else
   	{
        	printf("\nConnection Accepted\n");
    	} //this is for checking if the server has accepted the connection or not
    	
    	int exitloop = 0;
    	while(exitloop == 0)
    	{
    		int window = 0;
    		printf("\nEnter the window size: \n");
    		scanf("%d", &window); //sliding window protocol uses a window of bytes, this is for defining the size of that window
    		
    		printf("\nServer Is Waiting...\n");
    		
    		char message[MAX];
    		int index = 0;
    		
    		char ack[2];
    		ack[0] = '1';
    		ack[1] = '\0';
    	
    		char temp[2]; //this is the temporary acknowledgment variable for easier debugging
    		char buffer[2];
    		char exit[2];
    		
    		int loop = 0;
    		while(loop == 0)
    		{
    			recv(c_socket, exit, sizeof(exit), 0);
    			if(exit[0] == '1')
    			{
    				loop = 1;
    			}
    			else
    			{
    				for(int i = 0; i < window; i = i+1)
    				{
    					recv(c_socket, buffer, sizeof(buffer), 0); //recieve the message from the client
    					printf("Packet : %c\n", buffer[0]); //print the message byte by byte 
    					message[index] = buffer[0]; 
    					index = index + 1; //increment the index of the message
    				}
    				for(int i = 0; i < window; i = i+1)
    				{
    					printf("Enter acknowledgment : "); //enter the acknowledgment for the packet 
    					scanf("%s", temp);
    					ack[0] = temp[0];
    					send(c_socket, ack, sizeof(ack), 0); //send acknowledgment back to the client
    					
    					if(ack[0] == '0')
    					{
    						index = index - window + i;
    						i = window;
    					} //if the acknowledgment is 0, roll back the window untill the last succesfully sent bit and send from here 
    				}
    			}
    		}
    		printf("Message : %s\n", message); //print the recieved message
    		
    		close(c_socket); //close the client socket
    		close(s_socket); //close the server socket
    	
    		printf("\n0 - Continue\n1- Exit\n");
    		scanf("%d", &exitloop);
    	}
    	return 0;
}
 
