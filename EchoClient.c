//5-2
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 10000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100

int main(){
	int c_socket; 
	struct sockaddr_in c_addr;
	int n;
	char rcvBuffer[BUFSIZE];


	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);


	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1){
 
		printf("Cannot Connect\n");
		close(c_socket);
		return -1;
	}
	while(1){

		fputs("메세지를 입력: ", stdout);
		fgets(rcvBuffer, sizeof(rcvBuffer),stdin);
	
		write(c_socket, rcvBuffer, strlen(rcvBuffer));

		if(strncasecmp(rcvBuffer, "quit", 4) == 0 || strncasecmp(rcvBuffer, "kill server", 11) == 0) 
			break;

		n = read(c_socket, rcvBuffer, sizeof(rcvBuffer)); 

		if (n < 0){  
			printf("Read Failed\n");
			return -1;
		}
		rcvBuffer[n] = '\0';
		printf("received data: %s\n", rcvBuffer); 
	}
	close(c_socket);
	return 0;	
}
