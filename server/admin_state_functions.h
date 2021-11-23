#ifndef SERVER_ADMIN_STATE_FUNCTIONS_H
#define SERVER_ADMIN_STATE_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "../safe_macroses.h"
#include "char_reading.h"
#include "server_functions.h"
#include "asprintf.h"
#include "user_state_functions.h"
#include "blowfish_algorithm.h"

#define NUMBER_OF_ADMIN_STATES 7

enum ADMIN_STATE {
    ADMIN_TURNING_OFF,
    ADMIN_OFF,
    ADMIN_TURNING_ON,
    ADMIN_ON,
    ADMIN_SHOW_MONEY,
    ADMIN_CHECK,
    ADMIN_BLOCK
};

// Main function of working with admin state table
void *work_with_admin(void *args);

// Fills array of card with information parsed from database_text_format
int parse_database();

// Returns database in text format
char* database_to_string();

// Converting DB to string, coding it and printing to file.
void process_turning_off_event();
void exit_turning_off_state();

// Waiting for "ON" command
void process_off_event();
void exit_off_state();

// Reading DB from file, decoding it and parsing
void process_turning_on_event();
void exit_turning_on_state();

// Printing list of commands and waiting for index of command
void process_on_event();
void exit_on_state();

// Change state of automate to "BLOCK" and waiting for "UNBLOCK" command
void enter_block_state();
void process_block_event();
void exit_block_state();

// Printing amount of cash in automate
void process_show_money_event();
void exit_show_money_state();

// Printing current user_state
void process_check_event();
void exit_check_state();

#endif //SERVER_ADMIN_STATE_FUNCTIONS_H
