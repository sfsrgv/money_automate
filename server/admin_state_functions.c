#include "admin_state_functions.h"

extern int admin_state;
extern int buffer_socket_descriptor;
extern int user_state;
extern int previous_state;
extern int automate_state;

struct card *cards;
int size_of_database;
int cash_in_automate;
int admin_command_index;
char* database_text_format;

struct state admin_state_table[NUMBER_OF_ADMIN_STATES] = {
        // TURNING AUTOMATE_OFF 0
        {
                NULL,
                process_turning_off_event,
                exit_turning_off_state
        },
        // AUTOMATE_OFF 1
        {
                NULL,
                process_off_event,
                exit_off_state
        },
        // TURNING AUTOMATE_ON 2
        {
                NULL,
                process_turning_on_event,
                exit_turning_on_state
        },
        // AUTOMATE_ON 3
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

void *work_with_admin(void *args) {
    while (automate_state != AUTOMATE_ERROR) {
        SAFE_RUN(admin_state_table[admin_state].enter);
        SAFE_RUN(admin_state_table[admin_state].process);
        SAFE_RUN(admin_state_table[admin_state].exit);
    }
    return NULL;
}

int parse_database() {
    // Getting amount of cash
    char_auto_ptr buffer;
    SAFE_MALLOC(buffer, char, sizeof(char) * 10);
    STRNCPY_WITH_END_SYMBOL(buffer, database_text_format, 10);
    int current_index = 11;
    cash_in_automate = atoi(buffer);
    free(buffer);

    // Getting size of DB
    SAFE_MALLOC(buffer, char, sizeof(char) * 10);
    STRNCPY_WITH_END_SYMBOL(buffer, database_text_format + current_index, 10);
    size_of_database = atoi(buffer);
    current_index += 11;

    // Getting cards info
    SAFE_MALLOC(cards, struct card, sizeof(struct card) * size_of_database);
    for (int i = 0; i < size_of_database; ++i) {
        free(buffer);
        SAFE_MALLOC(buffer, char, sizeof(char) * 26);
        STRNCPY_WITH_END_SYMBOL(buffer, database_text_format + current_index, 26);
        current_index += 27;

        // Card number
        SAFE_MALLOC(cards[i].number, char, sizeof(char) * 16);
        STRNCPY_WITH_END_SYMBOL(cards[i].number, buffer, 16);

        // Password
        SAFE_MALLOC(cards[i].password, char, sizeof(char) * 4);
        STRNCPY_WITH_END_SYMBOL(cards[i].password, buffer + 17, 4);

        // Budget
        cards[i].budget = atoi(buffer + 22);
    }
    free(database_text_format);
    return 0;
}

char* database_to_string() {
    char* response = "";
    asprintf(&response, "%010d\n%010d\n", cash_in_automate, size_of_database);
    for (int i = 0; i < size_of_database; ++i)
        asprintf(&response, "%s%s %s %04d\n", response, cards[i].number, cards[i].password, cards[i].budget);
    return response;
}

void process_turning_off_event() {
    database_text_format = database_to_string();
    blowfish_for_database(CODE);
    send_message(buffer_socket_descriptor, "AUTOMATE TURNED OFF");
}

void exit_turning_off_state() {
    admin_state = ADMIN_OFF;
    automate_state = AUTOMATE_OFF;
}

void process_off_event() {
    char_auto_ptr client_message = get_message(buffer_socket_descriptor);
    while (strncmp(client_message, "ON", 2) != 0) {
        send_message(buffer_socket_descriptor, "AUTOMATE IS OFF");
        client_message = get_message(buffer_socket_descriptor);
    }
}

void exit_off_state() {
    admin_state = ADMIN_TURNING_ON;
}

void process_turning_on_event() {
    blowfish_for_database(DECODE);
    if (parse_database() == 1) {
        automate_state = AUTOMATE_ERROR;
        return;
    }
    automate_state = AUTOMATE_ON;
}

void exit_turning_on_state() {
    admin_state = ADMIN_ON;
}

void process_on_event() {
    send_message(buffer_socket_descriptor,
                 "CHOOSE COMMAND:\n1 - BLOCK\n2 - SHOW MONEY\n3 - CHECK AUTOMATE STATE\n4 - TURN OFF");
    char_auto_ptr client_message = get_message(buffer_socket_descriptor);
    while (atoi(client_message) < 0 || atoi(client_message) > 4) {
        send_message(buffer_socket_descriptor, "INCORRECT COMMAND. TRY AGAIN");
        client_message = get_message(buffer_socket_descriptor);
    }
    admin_command_index = atoi(client_message);
}

void exit_on_state() {
    switch (admin_command_index) {
        case 1: {
            admin_state = ADMIN_BLOCK;
            break;
        }
        case 2: {
            admin_state = ADMIN_SHOW_MONEY;
            break;
        }
        case 3: {
            admin_state = ADMIN_CHECK;
            break;
        }
        case 4: {
            admin_state = ADMIN_TURNING_OFF;
            break;
        }
        default:
            admin_state = ADMIN_ON;
    }
}

void enter_block_state() {
    automate_state = AUTOMATE_BLOCKED;
}

void process_block_event() {
    char_auto_ptr client_message;
    do {
        send_message(buffer_socket_descriptor, "AUTOMATE IS BLOCKED");
        client_message = get_message(buffer_socket_descriptor);
    } while (strncmp(client_message, "UNBLOCK", 7) != 0);
}

void exit_block_state() {
    automate_state = AUTOMATE_ON;
    admin_state = ADMIN_ON;
}

void process_show_money_event() {
    char_auto_ptr message = "AUTOMATE HAS ";
    asprintf(&message, "%s%d$. PRESS ENTER TO CONTINUE.", message, cash_in_automate);
    send_message(buffer_socket_descriptor, message);
    get_message(buffer_socket_descriptor);
}

void exit_show_money_state() {
    admin_state = ADMIN_ON;
}

void process_check_event() {
    char_auto_ptr message = "USER STATE IS ";
    asprintf(&message, "%s%s. PRESS ENTER TO CONTINUE", message, print_user_state_name(user_state));
    send_message(buffer_socket_descriptor, message);
    get_message(buffer_socket_descriptor);
}

void exit_check_state() {
    admin_state = ADMIN_ON;
}