CFLAGS += -Wall -g -O0
all: echoserv echocli

echoserv: echoserver.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@
echocli: echoclient.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@
clean:
	$(RM) echoserv echocli
