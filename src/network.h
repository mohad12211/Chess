#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "move.h"

int ConnectionToServer(void);
int GetColorFromServer(int sockfd);
void SendMoveToServer(int sockfd, char from, char to);
Move ReceiveMoveFromServer(int sockfd);

#endif // NETWORK_H
