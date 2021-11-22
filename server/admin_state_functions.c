#include "admin_state_functions.h"

struct card *cards;
int size_of_database;
int cash_in_automate;
int admin_command_index;

extern int admin_state;
extern int buffer_socket_descriptor;
extern int user_state;
extern int previous_state;
extern int automate_state;

int download_database() {
    FILE *cards_file;
    SAFE_OPENING_FILE(cards_file, "cards.txt", "r");
    char_auto_ptr buffer;
    size_t length = 0;
    getline(&buffer, &length, cards_file);
    cash_in_automate = atoi(buffer);
    getline(&buffer, &length, cards_file);
    size_of_database = atoi(buffer);
    SAFE_MALLOC(cards, struct card, sizeof(struct card) * size_of_database);
    for (int i = 0; i < size_of_database; ++i) {
        getline(&buffer, &length, cards_file);
        SAFE_MALLOC(cards[i].number, char, sizeof(char) * 16);
        strncpy(cards[i].number, buffer, 16);
        cards[i].number[16] = '\0';
        SAFE_MALLOC(cards[i].password, char, sizeof(char) * 4);
        strncpy(cards[i].password, buffer + 17, 4);
        cards[i].password[4] = '\0';
        cards[i].budget = atoi(buffer + 22);
    }
    fclose(cards_file);
    return 0;
}

int save_database() {
    FILE *cards_file;
    SAFE_OPENING_FILE(cards_file, "cards.txt", "w");
    fprintf(cards_file, "%d\n%d\n", cash_in_automate, size_of_database);
    for (int i = 0; i < size_of_database; ++i)
        fprintf(cards_file, "%s %s %d\n", cards[i].number, cards[i].password, cards[i].budget);
    fclose(cards_file);
    return 0;
}

void process_turning_off_event() {
    if (save_database() == 1) {
        automate_state = AUTOMATE_ERROR;
        return;
    }
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
    if (download_database() == 1) {
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
    asprintf(&message, "%s%d", message, cash_in_automate);
    send_message(buffer_socket_descriptor, message);
    get_message(buffer_socket_descriptor);
}

void exit_show_money_state() {
    admin_state = ADMIN_ON;
}

void process_check_event() {
    char_auto_ptr message = "USER STATE IS ";
    asprintf(&message, "%s%s", message, print_user_state_name(user_state));
    send_message(buffer_socket_descriptor, message);
    get_message(buffer_socket_descriptor);
}

void exit_check_state() {
    admin_state = ADMIN_ON;
}