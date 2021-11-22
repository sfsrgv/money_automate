#include "server_functions.h"


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

char* get_message(int socket_descriptor) {
    char* client_message = (char *) malloc(MAX_MESSAGE_LENGTH * sizeof(char));
    ssize_t length = recv(socket_descriptor, client_message, MAX_MESSAGE_LENGTH, 0);
    if (length == -1) {
        printf("ERROR IN GETTING\n");
        return "ERROR";
    }
    client_message[length] = '\0';
    printf("[%s]\n", client_message);
    return client_message;
}