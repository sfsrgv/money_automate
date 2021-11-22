// Sofa Sergeeva
//
// Make a money automate
//
// To compile program use command:
// gcc -pthread main.c user_state_functions.c char_reading.c admin_state_functions.c server_functions.c

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

struct state {
    void (*enter)();
    void (*process)();
    void (*exit)();
};

struct state user_state_table[NUMBER_OF_USER_STATES] = {
        // WAITING FOR CARD 0
        {
                enter_waiting_for_card_state,
                process_waiting_for_card_event,
                exit_waiting_for_card_state
        },
        // CARD ENTERED 1
        {
                NULL,
                process_card_entered_event,
                exit_card_entered_state
        },
        // GETTING PASSWORD 2
        {
                enter_getting_password_state,
                process_getting_password_event,
                exit_getting_password_state
        },
        // WAITING FOR COMMANDS 3
        {
                enter_waiting_for_commands_state,
                process_waiting_for_commands_event,
                exit_waiting_for_commands_state
        },
        // SHOW BUDGET 4
        {
                NULL,
                process_show_budget_event,
                exit_show_budget_state
        },
        // GET CASH 5
        {
                enter_get_cash_state,
                process_get_cash_event,
                exit_get_cash_state
        },
        // MAKE DEPOSIT 6
        {
                enter_make_deposit_state,
                process_make_deposit_event,
                exit_make_deposit_state
        },
        // RETURN CARD 7
        {
                NULL,
                process_return_card_event,
                exit_return_card_state
        },
        // ASKING LANGUAGE 8
        {
                enter_asking_language_state,
                process_asking_language_event,
                exit_asking_language_state
        }
};

struct state admin_state_table[NUMBER_OF_ADMIN_STATES] = {
        // TURNING OFF 0
        {
                NULL,
                process_turning_off_event,
                exit_turning_off_state
        },
        // OFF 1
        {
                NULL,
                process_off_event,
                exit_off_state
        },
        // TURNING ON 2
        {
                NULL,
                process_turning_on_event,
                exit_turning_on_state
        },
        // ON 3
        {
                NULL,
                process_on_event,
                exit_on_state
        },
        // SHOW MONEY 4
        {
                NULL,
                process_show_money_event,
                exit_show_money_state
        },
        // CHECKING 5
        {
                NULL,
                process_check_event,
                exit_check_state
        },
        // BLOCK 6
        {
                enter_block_state,
                process_block_event,
                exit_block_state
        }
};

int user_state;
int admin_state;
int buffer_socket_descriptor;
int is_working = 0;
int is_blocked = 0;

void *work_with_admin(void* args) {
    while (user_state != -1) {
        SAFE_RUN(admin_state_table[admin_state].enter);
        SAFE_RUN(admin_state_table[admin_state].process);
        SAFE_RUN(admin_state_table[admin_state].exit);
    }
    return NULL;
}

int main() {
    /*user_state = ASKING_LANGUAGE_STATE;
    download_database();
    while (user_state != -1) {
        SAFE_RUN(user_state_table[user_state].enter);
        SAFE_RUN(user_state_table[user_state].process);
        SAFE_RUN(user_state_table[user_state].exit);
    }*/

    int server_descriptor;
    SAFE_SOCKET_CREATION(server_descriptor, AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_info;
    initialize_sockaddr_in(&server_info);
    SAFE_BIND(server_descriptor, server_info);
    SAFE_LISTEN(server_descriptor, BACKLOG);
    SAFE_ACCEPT(buffer_socket_descriptor, server_descriptor);

    admin_state = OFF_STATE;
    user_state = WAITING_FOR_CARD_STATE;

    pthread_t admin_thread;
    pthread_create(&admin_thread, NULL, work_with_admin, NULL);
    pthread_join(admin_thread, NULL);

    close(buffer_socket_descriptor);
    close(server_descriptor);
    return 0;
}
