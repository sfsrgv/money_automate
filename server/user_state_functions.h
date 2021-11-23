#ifndef MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
#define MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H

#include <stdio.h>
#include <string.h>

#include "char_reading.h"
#include "admin_state_functions.h"

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

struct state {
    void (*enter)();
    void (*process)();
    void (*exit)();
};

// Converting from index in user state table to text
char *print_user_state_name(int i);

// Main function of working with user state table
void work_with_user();

// Waiting for card to be entered
void enter_waiting_for_card_state();
void process_waiting_for_card_event();
void exit_waiting_for_card_state();

// Checking if database has entered card
void process_card_entered_event();
void exit_card_entered_state();

// Getting password and checking it
void enter_getting_password_state();
void process_getting_password_event();
void exit_getting_password_state();

// Showing list of commands and getting index of command
void enter_waiting_for_commands_state();
void process_waiting_for_commands_event();
void exit_waiting_for_commands_state();

// Printing amount of money on entered card
void process_show_budget_event();
void exit_show_budget_state();

// Checks if there are enough money both on card
// and in automate. Gives them
void enter_get_cash_state();
void process_get_cash_event();
void exit_get_cash_state();

// Making a deposit
void enter_make_deposit_state();
void process_make_deposit_event();
void exit_make_deposit_state();

// Returning card to user
void process_return_card_event();
void exit_return_card_state();

// Asking language and changing it
void enter_asking_language_state();
void process_asking_language_event();
void exit_asking_language_state();

#endif //MONEY_AUTOMATE_USER_STATE_FUNCTIONS_H
