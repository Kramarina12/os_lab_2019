#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <utils.h>

#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd, nread;

  struct ClientInfo current_info;

  if (process_options_client(argc, argv, &current_info) != 0)
    exit(EXIT_FAILURE);

  char sendline[current_info.buff_size], recvline[current_info.buff_size + 1];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(current_info.server_port);

  if (argc < 2) {
    printf("Too few arguments \n");
    exit(1);
  }

  if (inet_pton(AF_INET, current_info.server_address, &servaddr.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
  }

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  write(1, "Input message to send\n", 13);
  while ((nread = read(0, sendline, current_info.buff_size)) > 0) {
    if (sendto(fd, sendline, nread, 0, (SADDR *)&servaddr, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }

    if (recvfrom(fd, recvline, current_info.buff_size, 0, NULL, NULL) == -1) {
      perror("recvfrom problem");
      exit(1);
    }

    printf("REPLY FROM SERVER= %s\n", recvline);
  }
  close(fd);
}
