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

enum DIALOG_STATUS {
    CONTINUE,
    ERROR
};

// Initialize socket information taken from file "socket_constants.h"
void initialize_socket_information(struct sockaddr_in* information);

// Sending messages
int send_message(int socket_descriptor, char* message);

// Getting messages
int get_message(int socket_descriptor);

#endif //CHAT_FUNCTIONS_H
