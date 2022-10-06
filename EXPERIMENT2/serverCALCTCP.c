#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include<unistd.h>
#include<string.h> 
#include<arpa/inet.h>

#define buffsize 150

void main()
{
int s_socket; int c_socket; int socket_length; int n; 
int operation; char buffer[buffsize];
int op1; int op2; int result;

s_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in ADDRESS_OF_SERVER; 
struct sockaddr_in ADDRESS_OF_CLIENT;

if(s_socket == -1)
{
	printf("Socket creation has failed\n");
	exit(EXIT_FAILURE);
}

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
	
n = send(c_socket, "Enter first operand: ", strlen("Enter first operand: "),0);
recv(c_socket, &op1, sizeof(int),0);


n = send(c_socket, "Enter second operand: ", strlen("Enter second operand: "),0);
recv(c_socket, &op2, sizeof(int),0);


n = send(c_socket, "Enter the operation: 1 for +, 2 for -, 3 for * and 4 for /", strlen("Enter the operation: 1 for +, 2 for -, 3 for * and 4 for /"),0);
recv(c_socket, &operation, sizeof(int), 0);


switch(operation) 
{
	case 1: 
	{	
        	result=op1 + op2;
		printf("Result is: %d + %d = %d\n",op1, op2, result);
         	break;
	}
	case 2:
	{
		result=op1 - op2;
        	printf("Result is: %d - %d = %d\n",op1, op2, result);
        	break;
        }
	case 3:
	{
		result=op1 * op2;
		printf("Result is: %d * %d = %d\n",op1, op2, result);
		break;
	}
        case 4:
        {
        	result=op1 / op2;
		printf("Result is: %d / %d = %d\n",op1, op2, result);
		break;
	}
        default: 
                printf("ERROR: Unsupported Operation");
    }
    
send(c_socket, &result, sizeof(result),0);
  
close(c_socket);
close(s_socket);
}
