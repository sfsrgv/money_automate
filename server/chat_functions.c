#include "chat_functions.h"

int send_message(int socket_descriptor, char *message) {
    if (send(socket_descriptor, message, MAX_MESSAGE_LENGTH, 0) == -1) {
        printf("ERROR WHILE SENDING\n");
        return ERROR;
    }
    return CONTINUE;
}

char* get_message(int socket_descriptor) {
    char* client_message = (char *) malloc(MAX_MESSAGE_LENGTH * sizeof(char));
    ssize_t length = recv(socket_descriptor, client_message, MAX_MESSAGE_LENGTH, 0);
    if (length == -1) {
        printf("ERROR IN GETTING\n");
        return "ERROR";
    }
    client_message[length] = '\0';
    printf("%s\n", client_message);
    return client_message;
}