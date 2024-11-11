CC=gcc
WARNINGS_ENABLED=-Wall -Wextra -Werror
CFLAGS=-I.

all: tcp_server tcp_client udp_server udp_client

tcp_server: tcpserver.c process_options.c
	$(CC) -o tcp_server $^ $(CFLAGS)

tcp_client: tcpclient.c process_options.c
	$(CC) -o tcp_client $^ $(CFLAGS)

udp_server: udpserver.c process_options.c
	$(CC) -o udp_server $^ $(CFLAGS)

udp_client: udpclient.c process_options.c
	$(CC) -o udp_client $^ $(CFLAGS)

clean: 
	rm tcp_server tcp_client udp_server udp_client