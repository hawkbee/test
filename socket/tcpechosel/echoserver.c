#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define ECHO_PORT (8889)
#define BACKLOG   (5)

void processRequest(int sock)
{
	int count;
	char buf[256];

	while (1) {
		count = read(sock, buf, sizeof buf);
		if ((count < 0) && (errno == EINTR))
			continue;
		else if (count <= 0)
			break;

		write(sock, buf, count);
	}

	close(sock);
}

void sigchld(int signo)
{
	pid_t pid;
	int stat;
	do {
		pid = waitpid(-1, &stat, WNOHANG);
	} while (pid > 0);

	return;
}
int main(int argc, char *argv[])
{
	struct sockaddr_in serv;
	int sock, rv;

	signal(SIGCHLD, sigchld);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		syslog(LOG_ERR, "Open socket fail: %s\n", strerror(errno));
		exit(1);
	}

	memset(&serv, 0, sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(ECHO_PORT);

	rv = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
	if (rv < 0) {
		syslog(LOG_ERR, "Bind socket fail: %s\n", strerror(errno));
		close(sock);
		exit(1);
	}

	rv = listen(sock, BACKLOG);
	if (rv < 0) {
		syslog(LOG_ERR, "Listen socket fail: %s\n", strerror(errno));
		close(sock);
		exit(1);
	}

	while (1) {
		struct sockaddr_in cli;
		int child;
		int clilen = sizeof(cli);
		int clisock = accept(sock, (struct sockaddr *)&cli, (socklen_t *)&clilen);

		if (clisock < 0) {
			syslog(LOG_ERR, "Accept socket fail: %s\n", strerror(errno));
			continue;
		}

		child = fork();
		if (child == 0) {
			close(sock);
			processRequest(clisock);
			exit(0);
		}
		close(clisock);
	}
}
