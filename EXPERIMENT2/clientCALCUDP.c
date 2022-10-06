#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define buffsize 150

int main()
{
int c_socket; int socket_length;
char operation[3]; char op1[buffsize]; char op2[buffsize]; char result[buffsize]; char buffer[buffsize];
int n;  int finalresult;
	
struct sockaddr_in ADDRESS_OF_SERVER;
c_socket = socket(AF_INET,SOCK_DGRAM,0);

if(c_socket == -1)
{
	printf("\nSocket Creation Failure\n");
	exit(EXIT_FAILURE);
}

ADDRESS_OF_SERVER.sin_family = AF_INET;
ADDRESS_OF_SERVER.sin_port = htons(9009);
ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

socket_length = sizeof(ADDRESS_OF_SERVER);
		
sendto(c_socket,"Hello There", strlen("Hello There"),0,(struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));
	
n = recvfrom(c_socket,(char *)buffer,sizeof(buffer),0,(struct sockaddr *)&ADDRESS_OF_SERVER,&socket_length);
printf("Server - %s\n",buffer);
scanf("%s",op1); 
sendto(c_socket, (char *)op1, sizeof(op1),0,(struct sockaddr *)&ADDRESS_OF_SERVER,sizeof(ADDRESS_OF_SERVER)); 

		
n = recvfrom(c_socket,(char *)buffer,sizeof(buffer),0,(struct sockaddr *)&ADDRESS_OF_SERVER,&socket_length);
printf("Server - %s\n",buffer);
scanf("%s",op2); 
sendto(c_socket, &op2, sizeof(op2),0,(struct sockaddr *)&ADDRESS_OF_SERVER,sizeof(ADDRESS_OF_SERVER)); 

n = recvfrom(c_socket,(char *)buffer,sizeof(buffer),0,(struct sockaddr *)&ADDRESS_OF_SERVER,&socket_length);
printf("Server - %s\n",buffer);
scanf("%s",operation); 
sendto(c_socket,&operation, sizeof(operation),0,(struct sockaddr *)&ADDRESS_OF_SERVER,sizeof(ADDRESS_OF_SERVER)); 
		
n = recvfrom(c_socket,(char *)&result, sizeof(result),0,(struct sockaddr *)&ADDRESS_OF_SERVER,&socket_length);
finalresult = atoi(result);
printf("Server - Your answer is %d\n",finalresult);

close(c_socket);

	return 0;
}
