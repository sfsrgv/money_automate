#include "admin_state_functions.h"

int is_working = 0;
struct card *cards;
int size_of_database;
int cash_in_automate;
int admin_state;

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
        SAFE_MALLOC(cards[i].password, char, sizeof(char) * 4);
        strncpy(cards[i].password, buffer + 17, 4);
        cards[i].budget = atoi(buffer + 22);
    }
    fclose(cards_file);
    return 0;
}

void enter_turning_off_state() {}

void process_turning_off_event() {

}

void exit_turning_off_state() {}

void enter_off_state() {}

void process_off_event() {}

void exit_off_state() {}

void enter_turning_on_state() {}

void process_turning_on_event() {
    download_database();
}

void exit_turning_on_state() {
    admin_state = ON_STATE;
}

void enter_on_state() {}

void process_on_event() {}

void exit_on_state() {}

void enter_block_state() {}

void process_block_event() {}

void exit_block_state() {}

void enter_show_money_state() {}

void process_show_money_event() {}

void exit_show_money_state() {}

void enter_check_state() {}

void process_check_event() {}

void exit_check_state() {}