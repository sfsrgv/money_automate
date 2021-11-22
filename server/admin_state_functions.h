#ifndef SERVER_ADMIN_STATE_FUNCTIONS_H
#define SERVER_ADMIN_STATE_FUNCTIONS_H

#include "../safe_macroses.h"
#include "char_reading.h"
#include "server_functions.h"
#include "asprintf.h"
#include "user_state_functions.h"

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_ADMIN_STATES 7

enum admin_state_names {
    TURNING_OFF_STATE,
    OFF_STATE,
    TURNING_ON_STATE,
    ON_STATE,
    SHOW_MONEY_STATE,
    CHECK_STATE,
    BLOCK_STATE
};

struct card {
    char *number;
    char *password;
    int budget;
};

int download_database();

int save_database();

void process_turning_off_event();

void exit_turning_off_state();

void process_off_event();

void exit_off_state();

void process_turning_on_event();

void exit_turning_on_state();

void process_on_event();

void exit_on_state();

void enter_block_state();

void process_block_event();

void exit_block_state();

void process_show_money_event();

void exit_show_money_state();

void process_check_event();

void exit_check_state();

#endif //SERVER_ADMIN_STATE_FUNCTIONS_H
