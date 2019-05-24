#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 256
#define SERV_PORT 12345

int
main (int argc, char **argv)

{
	char sendline[MAXLINE];
	char buffer[MAXLINE];
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2){
		printf ("uso: %s <IPaddress>\n", argv[0]);
		exit (0);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	int c = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (c < 0){
		fprintf (stderr, "Erro conectando-se ao servidor\n");
		exit (0);
	}

	
	int n;
	bzero(buffer,256);
       	while (n =  read (sockfd, buffer, sizeof(buffer)) > 0 ) {
		fprintf (stdout, "%s\n", buffer);
	}

	if (n < 0){
		fprintf (stderr, "Erro lendo do socket\n");
	}
	exit(0);

}
