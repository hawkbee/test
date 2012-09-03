#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
//#include <netinet/sctp.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

union val {
	int i_val;
	long l_val;
	struct linger linger_val;
	struct timeval timeval_val;
} val;
static char* sock_str_flag(union val *val, int len);
static char* sock_str_int(union val *val, int len);
static char* sock_str_timeval(union val *val, int len);
static char* sock_str_linger(union val *val, int len);
struct sock_opts {
	const char *opt_str;
	int opt_level;
	int opt_name;
	char *(*opt_val_str)(union val *, int);
} sock_opts[] = {
	{ "SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag },
	{ "SO_DEBUG",     SOL_SOCKET, SO_DEBUG,     sock_str_flag },
	{ "SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag },
	{ "SO_ERROR",     SOL_SOCKET, SO_ERROR,     sock_str_int  },
	{ "SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag },
	{ "SO_LINGER",    SOL_SOCKET, SO_LINGER,    sock_str_linger },
	{ "SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag },
	{ "SO_RCVBUF",    SOL_SOCKET, SO_RCVBUF,    sock_str_int  },
	{ "SO_SNDBUF",    SOL_SOCKET, SO_SNDBUF,    sock_str_int  },
	{ "SO_RCVLOWAT",  SOL_SOCKET, SO_RCVLOWAT,  sock_str_int  },
	{ "SO_SNDLOWAT",  SOL_SOCKET, SO_SNDLOWAT,  sock_str_int  },
	{ "SO_RCVTIMEO",  SOL_SOCKET, SO_RCVTIMEO,  sock_str_timeval },
	{ "SO_SNDTIMEO",  SOL_SOCKET, SO_SNDTIMEO,  sock_str_timeval },
	{ "SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag },
//	{ "SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, sock_str_flag },
	{ "SO_TYPE",      SOL_SOCKET, SO_TYPE,      sock_str_int  },
//	{ "SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, sock_str_flag },
	{ "IP_TOS",     IPPROTO_IP, IP_TOS,  sock_str_int },
	{ "IP_TTL",     IPPROTO_IP, IP_TTL,  sock_str_int },
//	{ "IPV6_DONTFRAG",     IPPROTO_IPV6, IPV6_DONTFRAG, sock_str_flag },
	{ "IPV6_UNICAST_HOPS", IPPROTO_IPV6, IPV6_UNICAST_HOPS, sock_str_int },
	{ "IPV6_V6ONLY",       IPPROTO_IPV6, IPV6_V6ONLY, sock_str_flag },
	{ "TCP_MAXSEG",     IPPROTO_TCP, TCP_MAXSEG, sock_str_int },
	{ "TCP_NODELAY",    IPPROTO_TCP, TCP_NODELAY, sock_str_flag },
#if 0
	{ "SCTP_AUTOCLOSE", IPPROTO_SCTP, SCTP_AUTOCLOSE, sock_str_int },
	{ "SCTP_MAXBURST",  IPPROTO_SCTP, SCTP_MAXBURST, sock_str_int },
	{ "SCTP_MAXSEG",    IPPROTO_SCTP, SCTP_MAXSEG, sock_str_int },
	{ "SCTP_NODELAY",   IPPROTO_SCTP, SCTP_NODELAY, sock_str_flag },
#endif
	{ NULL, 0, 0, NULL },
};

static char strres[128];

static char* sock_str_flag(union val *val, int len)
{
	if (len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%s", val->i_val == 0 ? "off" : "on");
	return (strres);
}

static char* sock_str_int(union val *val, int len)
{
	if (len != sizeof(long))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%ld", val->l_val);
	return (strres);
}

static char* sock_str_timeval(union val *val, int len)
{
	if (len != sizeof(struct timeval))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct timeval)", len);
	else
		snprintf(strres, sizeof(strres), "%ld sec %ld usec", val->timeval_val.tv_sec, val->timeval_val.tv_usec);
	return (strres);
}

static char* sock_str_linger(union val *val, int len)
{
	if (len != sizeof(struct linger))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct linger)", len);
	else
		snprintf(strres, sizeof(strres), "l_onoff = %d l_linger = %d", val->linger_val.l_onoff, val->linger_val.l_linger);
	return (strres);
}

int main(int argc, char *argv[])
{
	int fd;
	socklen_t len;
	struct sock_opts *opt;

	for (opt = sock_opts; opt->opt_str; ++opt) {
		printf("%s: ", opt->opt_str);
		if (opt->opt_val_str == NULL)
			printf("undefined\n");
		else {
			switch(opt->opt_level) {
				default:
					break;
				case SOL_SOCKET:
				case IPPROTO_TCP:
				case IPPROTO_IP:
					fd = socket(AF_INET, SOCK_STREAM, 0);
					if (fd < 0) {
						fprintf(stderr, "Creat socket fail: %s\n", strerror(errno));
						exit(1);
					}
					break;
				case IPPROTO_IPV6:
					fd = socket(AF_INET6, SOCK_STREAM, 0);
					if (fd < 0) {
						fprintf(stderr, "Creat socket fail: %s\n", strerror(errno));
						exit(1);
					}
					break;
#if 0
				case IPPROTO_SCTP:
					fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
					if (fd < 0) {
						fprintf(stderr, "Creat socket fail: %s\n", strerror(errno));
						exit(1);
					}
					break;
#endif
			}

			len = sizeof(val);

			if (getsockopt(fd, opt->opt_level, opt->opt_name, &val, &len) == -1) {
				fprintf(stderr, "Getsockopt fail: %s\n", strerror(errno));
			} else {
				printf("default = %s\n", (*opt->opt_val_str)(&val, len));
			}
			close(fd);
		}
	}
	return (0);
}





					
