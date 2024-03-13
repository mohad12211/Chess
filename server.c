#include <arpa/inet.h>
#include <assert.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  int serverfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(serverfd >= 0);

  int yes = 1;
  int n = setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  assert(n == 0);

  struct sockaddr_in address = {0};
  address.sin_family = AF_INET;
  address.sin_port = htons(9876);
  n = bind(serverfd, (struct sockaddr *)&address, sizeof(address));
  assert(n == 0);

  n = listen(serverfd, 10);
  assert(n == 0);

  int player1fd = accept(serverfd, 0, 0);
  assert(player1fd >= 0);
  char white = 8;
  n = send(player1fd, &white, 1, 0);
  assert(n == 1);

  int player2fd = accept(serverfd, 0, 0);
  assert(player2fd >= 0);
  char black = 16;
  n = send(player2fd, &black, 1, 0);
  assert(n == 1);

  struct pollfd fds[2] = {{player1fd, POLLIN, 0}, {player2fd, POLLIN, 0}};

  while (1) {
    n = poll(fds, 2, -1);
    assert(n >= 0);

    char buffer[2] = {0};

    if (fds[0].revents & POLLIN) {
      n = recv(fds[0].fd, buffer, 2, 0);
      if (n != 2) {
        return 0;
      }
      send(fds[1].fd, buffer, 2, 0);
    } else if (fds[1].revents & POLLIN) {
      n = recv(fds[1].fd, buffer, 2, 0);
      if (n != 2) {
        return 0;
      }
      send(fds[0].fd, buffer, 2, 0);
    }
  }

  return 0;
}
