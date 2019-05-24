#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {
	char buffer[1024] = {};
	char *hello = "Hello from server";
	int sockid = socket(AF_INET, SOCK_STREAM, 0);

	if (sockid == -1) {
		printf("Erro ao abrir o socket\n");
		return -1;
	} else {
		printf("Socket aberto\n");
		struct sockaddr_in addr;
		addr.sin_family = AF_INET; 
	    	addr.sin_addr.s_addr = htonl(INADDR_ANY); 
		addr.sin_port = htons(12345); 

		int status_bind = bind(sockid, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

		if (status_bind != -1) {
			printf("Bind criado\n");
			int status_listen = listen(sockid, 5);
			int new_socket = accept(sockid, (struct sockaddr *) &addr, (socklen_t*)sizeof(addr));
			if (new_socket < 0) {
				perror("Error no accept");
				exit(1);
			}
			int valread = read(new_socket, buffer, 1024);
			printf("%s\n", buffer);
			send(new_socket, hello, strlen(hello), 0);
			printf("Hello message sent\n");
			return 0;
		}
	}
	printf("Fim\n");
}
