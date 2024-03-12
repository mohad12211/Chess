#include <arpa/inet.h>
#include <assert.h>
#include <poll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  int serverfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(serverfd >= 0);

  int yes = 1;
  int n = setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  assert(n == 0);

  struct sockaddr_in address = {AF_INET, htons(9876), 0};
  n = bind(serverfd, (struct sockaddr *)&address, sizeof(address));
  assert(n == 0);

  n = listen(serverfd, 10);
  assert(n == 0);

  int player1fd = accept(serverfd, 0, 0);
  assert(player1fd >= 0);

  int player2fd = accept(serverfd, 0, 0);
  assert(player2fd >= 0);

  struct pollfd fds[2] = {{player1fd, POLLIN, 0}, {player2fd, POLLIN, 0}};

  while (1) {
    n = poll(fds, 2, -1);
    assert(n >= 0);

    char buffer[2] = {0};

    if (fds[0].revents & POLLIN) {
      n = recv(player1fd, buffer, 2, 0);
      if (n != 2) {
        return 0;
      }
      send(player1fd, buffer, 2, 0);
      send(player2fd, buffer, 2, 0);
      printf("Sent.\n");
    } else if (fds[1].revents & POLLIN) {
      n = recv(player2fd, buffer, 2, 0);
      if (n != 2) {
        return 0;
      }
      send(player1fd, buffer, 2, 0);
      send(player2fd, buffer, 2, 0);
      printf("Sent.\n");
    }
  }

  return 0;
}
