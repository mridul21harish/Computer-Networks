#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define buffsize 250

int main()
{
int s_socket; int socket_length;
char operation[3]; char op1[buffsize]; char op2[buffsize]; char result[buffsize]; char buffer[buffsize];
int n; int a; int b; int choice; int finalresult;

struct sockaddr_in ADDRESS_OF_SERVER;
struct sockaddr_in ADDRESS_OF_CLIENT;
s_socket = socket(AF_INET,SOCK_DGRAM,0);

if(s_socket == -1)
{
	printf("\nSocket Creation Failure\n");
	exit(EXIT_FAILURE);
}

ADDRESS_OF_SERVER.sin_family = AF_INET;
ADDRESS_OF_SERVER.sin_port = htons(9009);
ADDRESS_OF_SERVER.sin_addr.s_addr = INADDR_ANY;

if( bind(s_socket, (const struct sockaddr *)&ADDRESS_OF_SERVER, sizeof(ADDRESS_OF_SERVER)) > 0)
{
	printf("Binding succesfull\n");
}

socket_length = sizeof(ADDRESS_OF_SERVER);
		
n = recvfrom(s_socket,(char *)buffer,sizeof(buffer),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,&socket_length);
		
sendto(s_socket,"Enter the first operand: ", strlen("Enter the first operand: "),0,(struct sockaddr *)&ADDRESS_OF_CLIENT, sizeof(ADDRESS_OF_CLIENT));
n = recvfrom(s_socket, (char *)op1, sizeof(op1),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,&socket_length); 	
a = atoi(op1);
printf("Client - Operand 1 is: %d \n", a);

sendto(s_socket,"Enter the second operand: ", strlen("Enter the second operand: "),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,sizeof(ADDRESS_OF_CLIENT));
n = recvfrom(s_socket, (char *)op2, sizeof(op2),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,&socket_length); 
b = atoi(op2);
printf("Client - Operand 2 is: %d \n", b);

sendto(s_socket,"\nEnter the operation: 1 for +, 2 for -, 3 for * and 4 for /\n", strlen("\nEnter the operation: 1 for +, 2 for -, 3 for * and 4 for /\n"),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,sizeof(ADDRESS_OF_CLIENT));
n = recvfrom(s_socket, (char *)operation,sizeof(operation),0,(struct sockaddr *)&ADDRESS_OF_CLIENT,&socket_length); 
choice = atoi(operation);
printf("Client - Choosen operation is %d\n",choice);

switch(choice)
{
	case 1: finalresult = a + b;
		break;
	case 2: finalresult = a - b;
		break;
	case 3: finalresult = a * b;
		break;
	case 4: finalresult = a / b;
		break;
}

sprintf(result, "%d" ,finalresult);
sendto(s_socket, (char *)result, sizeof(result),0,(struct sockaddr *)&ADDRESS_OF_CLIENT, sizeof(ADDRESS_OF_CLIENT));
				
close(s_socket);

	return 0;
}
