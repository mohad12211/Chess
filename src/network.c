#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <windows.h>
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <assert.h>
#include <stdbool.h>

#include "move.h"
#include "network.h"

int ConnectionToServer(void) {

#ifdef _WIN32
  WSADATA wsaData;
  int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  assert(result == 0);
#else
#endif

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);

#ifdef _WIN32
  const char yes = 1;
  int n = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
#else
  int yes = 1;
  int n = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
#endif
  assert(n == 0);

#ifdef _WIN32
  DWORD timeout = 1;
#else
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 1;
#endif
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof timeout);

  struct sockaddr_in server_address = {0};
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("159.223.17.149");
  server_address.sin_port = htons(9876);

  n = connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
  assert(n == 0);

  return sockfd;
}

void SendMoveToServer(int sockfd, Move move) {
  char buf[2] = {move.start, move.end};
  int n = send(sockfd, buf, 2, 0);
  assert(n == 2);
}

Move ReceiveMoveFromServer(int sockfd) {

  char buffer[2] = {0};
  int n = recv(sockfd, buffer, 2, 0);
  if (n != 2)
    return (Move){0, 0};

  return (Move){63 - buffer[0], 63 - buffer[1]};
}

int GetColorFromServer(int sockfd) {
  char buffer = 0;
  int n = 0;
  do {
    n = recv(sockfd, &buffer, 1, 0);
  } while (n != 1);

  return buffer;
}
