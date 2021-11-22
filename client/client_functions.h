#ifndef CHAT_FUNCTIONS_H
#define CHAT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>

#include "socket_constants.h"
#include "char_reading.h"

#define MAX_MESSAGE_LENGTH 10000
#define SIZE_OF_TIME_LINE 20

enum DIALOG_STATUS {
    CONTINUE,
    ERROR
};

void initialize_sockaddr_in(struct sockaddr_in* server_info);

// Sending messages
int send_message(int socket_descriptor, char* message);

// Getting messages
int get_message(int socket_descriptor);

#endif //CHAT_FUNCTIONS_H