#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
int c_socket; char buff[512]; char message[512]; int n;

c_socket = socket(AF_INET, SOCK_DGRAM,0);
struct sockaddr_in ADDRESS_OF_SERVER;

if(c_socket == -1)
{
	printf("Socket creation has failed\n");
	exit(EXIT_FAILURE);
}

socklen_t len = sizeof(ADDRESS_OF_SERVER);

memset(&ADDRESS_OF_SERVER, 0, sizeof(ADDRESS_OF_SERVER));

ADDRESS_OF_SERVER.sin_family = AF_INET;
ADDRESS_OF_SERVER.sin_port = htons(9009);
ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

s:printf("Client: ");
  fgets(message, sizeof(message), stdin);
  sendto(c_socket, (const char *)message, sizeof(message),0,(struct sockaddr *) &ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER));

n = recvfrom(c_socket, (char *)buff, sizeof(buff), 0, (struct sockaddr *) &ADDRESS_OF_SERVER, &len);
buff[n] = '\0';
printf("Message from Client: %s\n", buff);
goto s;

close(c_socket);
return 0;
}

