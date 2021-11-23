#include "client_functions.h"

void initialize_socket_information(struct sockaddr_in* information) {
    memset(information, 0, sizeof(*information));
    information->sin_family = AF_INET;
    information->sin_addr.s_addr = IP_ADDRESS;
    information->sin_port = PORT_NUMBER;
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