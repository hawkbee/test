#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ECHO_PORT (8889)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void usage(char *argv[], int stat)
{
	printf("Usage: %s ip\n", argv[0]);
	exit(stat);
}

void requestData(FILE *fp, int sock)
{
	int maxfdp1;
	fd_set fdset;
	char buf[256];

	FD_ZERO(&fdset);
	while(1) {
		FD_SET(fileno(fp), &fdset);
		FD_SET(sock, &fdset);
		maxfdp1 = MAX(sock, fileno(fp)) + 1;
		select(maxfdp1, &fdset, NULL, NULL, NULL);
		if (FD_ISSET(fileno(fp), &fdset)) {
			char *s = fgets(buf, sizeof(buf), fp);
			if (s == NULL)
				break;
			write(sock, buf, strlen(buf));
		}
		if (FD_ISSET(sock, &fdset)) {
			if (read(sock, buf, sizeof(buf)) == 0) {
				syslog(LOG_ERR, "Server terminated prematurely");
				break;
			}
			printf("%s", buf);
		}
	}
	close(sock);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in serv;

	int sock, rv;

	if (argc < 2) {
		usage(argv, 1);
	}
	memset(&serv, 0, sizeof(serv));

	rv = inet_pton(AF_INET, argv[1], &serv.sin_addr);
	if (rv < 0) {
		syslog(LOG_ERR, "inet_pton fail: %s\n", strerror(errno));
		exit(1);
	} else if (rv == 0) {
		usage(argv, 1);
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		syslog(LOG_ERR, "Open socket fail: %s\n", strerror(errno));
		exit(1);
	}

	serv.sin_family = AF_INET;
	serv.sin_port   = htons(ECHO_PORT);

	rv = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
	if (rv < 0) {
		syslog(LOG_ERR, "Connect socket fail: %s\n", strerror(errno));
		close(sock);
		exit(1);
	}

	requestData(stdin, sock);

	return (0);
}

