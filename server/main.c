// Sofa Sergeeva
//
// Make a money automate
//
// To compile program use command:
// gcc -pthread main.c user_state_functions.c char_reading.c admin_state_functions.c server_functions.c blowfish_algorithm.c string_and_uin64_functions.c

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#include "../safe_macroses.h"
#include "user_state_functions.h"
#include "admin_state_functions.h"
#include "socket_constants.h"
#include "server_functions.h"

enum USER_STATE user_state;
enum ADMIN_STATE admin_state;
enum AUTOMATE_STATE automate_state;

int buffer_socket_descriptor;

int main() {
    // Set up settings to make connection
    int server_descriptor;
    SAFE_SOCKET_CREATION(server_descriptor, AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_info;
    initialize_socket_information(&server_info);
    SAFE_BIND(server_descriptor, server_info);
    SAFE_LISTEN(server_descriptor, BACKLOG);
    SAFE_ACCEPT(buffer_socket_descriptor, server_descriptor);

    // Start states to state tables
    admin_state = ADMIN_OFF;
    automate_state = AUTOMATE_OFF;
    user_state = USER_ASKING_LANGUAGE;

    // Starting work with admin from client application
    pthread_t admin_thread;
    pthread_create(&admin_thread, NULL, work_with_admin, NULL);

    // Starting work with client
    work_with_user();

    pthread_join(admin_thread, NULL);
    close(buffer_socket_descriptor);
    close(server_descriptor);
    return 0;
}
