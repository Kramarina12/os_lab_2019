CC = gcc
CFLAGS = -I. -lpthread
SRCS = client.c server.c modulo.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I.

all: client server

client: client.c libmodulo.so
	$(CC) -o $@ client.c -L. -lmodulo $(CFLAGS) 

server: server.c libmodulo.so
	$(CC) -o $@ server.c -L. -lmodulo $(CFLAGS)

libmodulo.so: modulo.o
	$(CC) -shared -o $@ $^ $(CFLAGS)

modulo.o: modulo.c
	$(CC) -o $@ -c $^ -fPIC $(CFLAGS)

clean:
	rm -f $(OBJS)
	rm client server

.PHONY: clean
