#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

int ConnectionToServer(void);
int GetColorFromServer(int sockfd);
void SendMoveToServer(int sockfd, char from, char to);
bool ReceiveMoveFromServer(int sockfd, int *from, int *to);

#endif // NETWORK_H
