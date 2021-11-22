#ifndef MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
#define MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H

#include <stdio.h>
#include <string.h>

#include "char_reading.h"

#define NUMBER_OF_USER_STATES 9

enum AUTOMATE_STATE {
    AUTOMATE_ON,
    AUTOMATE_OFF,
    AUTOMATE_BLOCKED,
    AUTOMATE_ERROR
};

enum USER_STATE {
    USER_WAITING_FOR_CARD,
    USER_CARD_ENTERED,
    USER_GETTING_PASSWORD,
    USER_WAITING_FOR_COMMANDS,
    USER_SHOW_BUDGET,
    USER_GET_CASH,
    USER_MAKE_DEPOSIT,
    USER_RETURN_CARD,
    USER_ASKING_LANGUAGE
};

enum LANGUAGES {
    ENGLISH,
    RUSSIAN
};

struct card {
    char *number;
    char *password;
    int budget;
};

char *print_user_state_name(int i);

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

void enter_asking_language_state();

void process_asking_language_event();

void exit_asking_language_state();

#endif //MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
