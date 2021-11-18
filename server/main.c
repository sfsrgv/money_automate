// Sofa Sergeeva
//
// Make a money automate
//
// To compile program use command:
// gcc main.c user_state_functions.c char_reading.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_state_functions.h"
#include "admin_state_functions.h"
#include "safe_macroses.h"



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
                enter_turning_off_state,
                process_turning_off_event,
                exit_turning_off_state
        },
        // OFF 1
        {
                enter_off_state,
                process_off_event,
                exit_off_state
        },
        // TURNING ON 2
        {
                enter_turning_on_state,
                process_turning_on_event,
                exit_turning_on_state
        },
        // ON 3
        {
                enter_on_state,
                process_on_event,
                exit_on_state
        },
        // SHOW MONEY 4
        {
                enter_show_money_state,
                process_show_money_event,
                exit_show_money_state
        },
        // CHECKING 5
        {
                enter_check_state,
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



int main() {
    user_state = ASKING_LANGUAGE_STATE;
    download_database();
    while (user_state != -1) {
        SAFE_RUN(user_state_table[user_state].enter);
        SAFE_RUN(user_state_table[user_state].process);
        SAFE_RUN(user_state_table[user_state].exit);
    }
    return 0;
}
