#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define IP "172.217.171.228" /* google.com */
#define PORT 80

int main(void)
{
    int s;
    struct sockaddr_in sock;
    char buf[512];
    char *data = "HEAD / HTTP/1.0\n\n";
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
    	printf("socket() error\n");
    	return -1;
    }

    sock.sin_addr.s_addr = inet_addr(IP);
    sock.sin_port = htons(PORT);
	sock.sin_family = AF_INET;

	if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0)
	{
		printf("connect() error\n");
		close(s);

		return -1;
	}

	write(s, data, strlen(data));
	read(s, buf, 511);
	close(s);
	
	printf("\n%s\n\n", buf);

	return 0;
}
