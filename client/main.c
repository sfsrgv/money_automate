#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "socket_constants.h"
#include "char_reading.h"
#include "char_reading.h"
#include "chat_functions.h"

int main() {
    // Creating client socket
    int client_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (client_descriptor == -1) {
        printf("Error while creating socket\n");
        return 1;
    }

    // Getting all socket info from "socket_constants.h"
    struct sockaddr_in client_info;
    memset(&client_info, 0, sizeof(client_info));
    client_info.sin_family = AF_INET;
    client_info.sin_addr.s_addr = IP_ADDRESS;
    client_info.sin_port = PORT_NUMBER;

    // Trying to connect to server
    if (connect(client_descriptor, (struct sockaddr *) &client_info, sizeof(client_info)) == -1) {
        printf("Error while connecting\n ");
        return 1;
    }

    while(1) {
        char_auto_ptr command;
        READ_LINE(command);
        if (command == NULL) {
            printf("ERROR WHILE READING COMMAND\n");
            break;
        }
        if (send_message(client_descriptor, command) == ERROR)
            break;
        if (get_message(client_descriptor) == ERROR)
            break;
    }
    close(client_descriptor);
    return 0;
}