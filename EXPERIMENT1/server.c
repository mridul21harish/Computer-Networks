#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main()
{	
int s_socket; char buff[512]; char message[512]; int n;
s_socket = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in ADDRESS_OF_SERVER; 
struct sockaddr_in ADDRESS_OF_CLIENT;

if(s_socket == -1)
{
	printf("Socket creation has failed\n");
	exit(EXIT_FAILURE);
}

ADDRESS_OF_SERVER.sin_family = AF_INET;
ADDRESS_OF_SERVER.sin_port = htons(9009);
ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

if ( bind(s_socket, (const struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER)) < 0 )
{
	printf("Binding with the client failed\n");	
	exit(EXIT_FAILURE);
}
	
socklen_t len = sizeof(ADDRESS_OF_SERVER);
   
printf("Awaiting the the message from the client......\n\n");

s: n = recvfrom(s_socket, (char *)buff, sizeof(buff), 0, (struct sockaddr *) &ADDRESS_OF_CLIENT, &len);
buff[n] = '\0';
printf("Message from Client: %s\n", buff);
printf("Server: ");
fgets(message, sizeof(message), stdin);
sendto(s_socket, (char *)message, sizeof(message), 0, (struct sockaddr *) &ADDRESS_OF_CLIENT, sizeof(ADDRESS_OF_CLIENT));
goto s;

close(s_socket);
return 0;
}



