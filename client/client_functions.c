#include "client_functions.h"

void initialize_sockaddr_in(struct sockaddr_in* server_info) {
    memset(server_info, 0, sizeof(*server_info));
    server_info->sin_family = AF_INET;
    server_info->sin_addr.s_addr = IP_ADDRESS;
    server_info->sin_port = PORT_NUMBER;
}

int send_message(int socket_descriptor, char *message) {
    if (send(socket_descriptor, message, MAX_MESSAGE_LENGTH, 0) == -1) {
        printf("ERROR WHILE SENDING\n");
        return ERROR;
    }
    return CONTINUE;
}

int get_message(int socket_descriptor) {
    char_auto_ptr server_message = (char *) malloc(MAX_MESSAGE_LENGTH * sizeof(char));
    ssize_t length = recv(socket_descriptor, server_message, MAX_MESSAGE_LENGTH, 0);
    if (length == -1) {
        printf("ERROR IN GETTING\n");
        return ERROR;
    }
    server_message[length] = '\0';
    printf("%s\n", server_message);
    return CONTINUE;
}