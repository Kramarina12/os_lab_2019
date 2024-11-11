#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <utils.h>

#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd, nread;

  struct ClientInfo current_info;

  if (process_options_client(argc, argv, &current_info) != 0)
    exit(EXIT_FAILURE);

  char buf[current_info.buff_size];
  struct sockaddr_in servaddr;

  if (argc < 3) {
    printf("Too few arguments \n");
    exit(1);
  }

  if (inet_pton(AF_INET, current_info.server_address, &servaddr.sin_addr) <= 0) {
    perror("inet_pton problem");
    exit(1);
  }
  
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(current_info.server_port);

  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }

  write(1, "Input message to send\n", 22);
  while ((nread = read(0, buf, current_info.buff_size)) > 0) {
    if (write(fd, buf, nread) < 0) {
      perror("write problem");
      exit(1);
    }
  }

  close(fd);
  exit(0);
}
