#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "../safe_macroses.h"
#include "char_reading.h"
#include "client_functions.h"

int main() {
    // Set up settings to make connection
    int client_descriptor;
    SAFE_SOCKET_CREATION(client_descriptor, AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_info;
    initialize_socket_information(&client_info);
    SAFE_CONNECT(client_descriptor, client_info);

    // Sending commands to server
    while(1) {
        char_auto_ptr command;
        READ_LINE(command);
        if (send_message(client_descriptor, command) == ERROR)
            break;
        if (get_message(client_descriptor) == ERROR)
            break;
    }
    close(client_descriptor);
    return 0;
}