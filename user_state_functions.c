#include "user_state_functions.h"

void print_user_state_name(int i) {
    switch (i) {
        case 0: {
            printf("WAITING FOR CARD\n");
            break;
        }
        case 1: {
            printf("CARD ENTERED\n");
            break;
        }
        case 2: {
            printf("GETTING PASSWORD\n");
            break;
        }
        case 3: {
            printf("WAITING FOR COMMANDS\n");
            break;
        }
        case 4: {
            printf("SHOW BUDGET\n");
            break;
        }
        case 5: {
            printf("GET CASH\n");
            break;
        }
        case 6: {
            printf("MAKE DEPOSIT\n");
            break;
        }
        case 7: {
            printf("RETURN CARD\n");
            break;
        }
        case 8: {
            printf("ASKING LANGUAGE\n");
            break;
        }
        case -1: {
            printf("ERROR\n");
            break;
        }
        default:
            printf("UNKNOWN STATE\n");
    }
}

void process_waiting_for_card_event() {}

void exit_waiting_for_card_state() {}

void process_card_entered_event() {}

void exit_card_entered_state() {}

void enter_getting_password_state() {}

void process_getting_password_event() {}

void exit_getting_password_state() {}

void enter_waiting_for_commands_state() {}

void process_waiting_for_commands_event() {}

void exit_waiting_for_commands_state() {}

void process_show_budget_event() {}

void exit_show_budget_state() {}

void enter_get_cash_state() {}

void process_get_cash_event() {}

void exit_get_cash_state() {}

void enter_make_deposit_state() {}

void process_make_deposit_event() {}

void exit_make_deposit_state() {}

void process_return_card_event() {}

void exit_return_card_state() {}

void process_asking_language_event() {}

void exit_asking_language_state() {}
