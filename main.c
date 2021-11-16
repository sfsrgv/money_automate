#include <stdio.h>
#include "user_state_functions.h"

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
                NULL,
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

int main() {
    state = ASKING_LANGUAGE_STATE;
    while (state != -1) {
        print_user_state_name(state);
        SAFE_RUN(state_table[state].enter);
        SAFE_RUN(state_table[state].process);
        SAFE_RUN(state_table[state].exit);
    }
    return 0;
}
