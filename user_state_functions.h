#ifndef MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
#define MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H

#include <stdio.h>

#include "char_reading.h"

#define NUMBER_OF_STATES 9

enum state_names {
    WAITING_FOR_CARD_STATE,
    CARD_ENTERED_STATE,
    GETTING_PASSWORD_STATE,
    WAITING_FOR_COMMANDS_STATE,
    SHOW_BUDGET_STATE,
    GET_CASH_STATE,
    MAKE_DEPOSIT_STATE,
    RETURN_CARD_STATE,
    ASKING_LANGUAGE_STATE
};

enum languages {
    ENGLISH = 0,
    RUSSIAN = 1
};


void print_user_state_name(int i);

void enter_waiting_for_card_state();

void process_waiting_for_card_event();

void exit_waiting_for_card_state();

void process_card_entered_event();

void exit_card_entered_state();

void enter_getting_password_state();

void process_getting_password_event();

void exit_getting_password_state();

void enter_waiting_for_commands_state();

void process_waiting_for_commands_event();

void exit_waiting_for_commands_state();

void process_show_budget_event();

void exit_show_budget_state();

void enter_get_cash_state();

void process_get_cash_event();

void exit_get_cash_state();

void enter_make_deposit_state();

void process_make_deposit_event();

void exit_make_deposit_state();

void process_return_card_event();

void exit_return_card_state();

void process_asking_language_event();

void exit_asking_language_state();

#endif //MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
