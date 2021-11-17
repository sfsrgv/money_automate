#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_state_functions.h"
#include "safe_macroses.h"

#define SAFE_RUN(func)                   \
            do {                         \
                if ((func) != NULL)      \
                   func();               \
            } while (0)

struct state {
    void (*enter)();

    void (*process)();

    void (*exit)();
};

struct state state_table[NUMBER_OF_STATES] = {
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
                NULL,
                process_asking_language_event,
                exit_asking_language_state
        }
};

int state;

struct card {
    char *number;
    char *password;
    int budget;
};

int size_of_database;
struct card *cards;

int download_database() {
    FILE *cards_file;
    SAFE_OPENING_FILE(cards_file, "cards.txt", "r");
    char_auto_ptr buffer;
    size_t length = 0;
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

int main() {
    state = WAITING_FOR_CARD_STATE;
    download_database();
    while (state != -1) {
        //print_user_state_name(state);
        SAFE_RUN(state_table[state].enter);
        SAFE_RUN(state_table[state].process);
        SAFE_RUN(state_table[state].exit);
    }
    return 0;
}
