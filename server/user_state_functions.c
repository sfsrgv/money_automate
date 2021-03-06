#include "user_state_functions.h"

extern struct card *cards;
extern int size_of_database;
extern int user_state;
extern int cash_in_automate;
extern int automate_state;

enum LANGUAGES language = ENGLISH;
int previous_state = USER_WAITING_FOR_CARD;
int index_of_current_card = 0;
int user_command_index = 0;
int card_in_automate = 0;
char *card_number;

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

char *messages[17][2] = {
        {
                "-----------------\nEnter card:",
                "-----------------\n???????????????? ??????????:"
        },
        {
                "Enter password:",
                "?????????????? ????????????:"
        },
        {
                "\nChoose command:\n1 - Show budget\n2 - Get cash\n3 - Make a deposit\n4 - Return card\n5 - Change language",
                "\n???????????????? ????????????????:\n1 - ???????????????????? ??????????????\n2 - ???????????? ????????????????\n3 - ???????????????? ???? ????????\n4 - ?????????????? ??????????\n5 - ???????????????? ????????"
        },
        {
                "Enter sum to get:",
                "?????????????? ?????????? ????????????:"
        },
        {
                "Enter sum of deposit:",
                "?????????????? ?????????? ?????? ???????????????????? ???? ????????:"
        },
        {
                "-----------------\nChoose language:\n1 - English\n2 - Russian",
                "-----------------\n???????????????? ????????:\n1 - ????????????????????\n2 - ??????????????"
        },
        {
                "Sorry, this card is not from our bank",
                "?? ??????????????????, ?????? ?????????? ???? ???? ???????????? ??????????"
        },
        {
                "Take your card",
                "???????????????? ??????????"
        },
        {
                "Incorrect password. Number of remaining attempts: ",
                "???????????????? ????????????. ???????????????? ??????????????: "
        },
        {
                "Unknown command. Please, try again",
                "?????????????????????? ????????????????. ????????????????????, ???????????????????? ??????????"
        },
        {
                "You have ",
                "???? ?????????? ?????????? "
        },
        {
                "Not enough  cash in automate",
                "?? ???????????????? ???????????????????????? ????????????????"
        },
        {
                "Not enough money on your card",
                "???????????????????????? ?????????????? ???? ??????????"
        },
        {
                "Take your cash",
                "???????????????? ????????????"
        },
        {
                "Operation made",
                "???????????????? ??????????????????"
        },
        {
                "Automate if turned off",
                "???????????????? ????????????????"
        },
        {
                "Automate was blocked by administrator",
                "???????????????? ?????? ???????????????????????? ??????????????????????????????"
        }
};

char *print_user_state_name(int i) {
    switch (i) {
        case 0:
            return "WAITING FOR CARD";
        case 1:
            return "CARD ENTERED";
        case 2:
            return "GETTING PASSWORD";
        case 3:
            return "WAITING FOR COMMANDS";
        case 4:
            return "SHOW BUDGET";
        case 5:
            return "GET CASH";
        case 6:
            return "MAKE DEPOSIT";
        case 7:
            return "RETURN CARD";
        case 8:
            return "ASKING LANGUAGE";
        case -1:
            return "AUTOMATE_ERROR";
        default:
            return "UNKNOWN STATE";
    }
}

void work_with_user() {
    while (automate_state != AUTOMATE_ERROR) {
        if (automate_state == AUTOMATE_ON) {
            SAFE_RUN(user_state_table[user_state].enter);
            SAFE_RUN(user_state_table[user_state].process);
            SAFE_RUN(user_state_table[user_state].exit);
        } else {
            if (automate_state == AUTOMATE_BLOCKED)
                printf("%s\n", messages[16][language]);
            else {
                printf("%s\n", messages[15][language]);
                if (card_in_automate) {
                    process_return_card_event();
                    exit_return_card_state();
                }
            }
            sleep(3);
        }
    }
}

void enter_waiting_for_card_state() {
    printf("%s\n", messages[0][language]);
}

void process_waiting_for_card_event() {
    size_t length = 0;
    getline(&card_number, &length, stdin);
    card_number[strlen(card_number) - 1] = 0;
}

void exit_waiting_for_card_state() {
    user_state = USER_CARD_ENTERED;
}

void process_card_entered_event() {
    card_in_automate = 1;
    for (int i = 0; i < size_of_database; ++i)
        if (strcmp(card_number, cards[i].number) == 0) {
            index_of_current_card = i;
            return;
        }
    index_of_current_card = -1;
    printf("%s\n", messages[6][language]);
}

void exit_card_entered_state() {
    if (index_of_current_card == -1)
        user_state = USER_RETURN_CARD;
    else
        user_state = USER_GETTING_PASSWORD;
}

void enter_getting_password_state() {
    printf("%s\n", messages[1][language]);
}

void process_getting_password_event() {
    char_auto_ptr user_password;
    for (int i = 3; i > 0; --i) {
        size_t length = 0;
        getline(&user_password, &length, stdin);
        user_password[strlen(user_password) - 1] = 0;
        if (strncmp(user_password, cards[index_of_current_card].password, 4) == 0)
            return;
        else
            printf("%s%d\n", messages[8][language], i - 1);
    }
    index_of_current_card = -1;
}

void exit_getting_password_state() {
    if (index_of_current_card == -1)
        user_state = USER_RETURN_CARD;
    else
        user_state = USER_WAITING_FOR_COMMANDS;
}

void enter_waiting_for_commands_state() {
    printf("%s\n", messages[2][language]);
}

void process_waiting_for_commands_event() {
    READ_INT(user_command_index);
}

void exit_waiting_for_commands_state() {
    switch (user_command_index) {
        case 1: {
            user_state = USER_SHOW_BUDGET;
            break;
        }
        case 2: {
            user_state = USER_GET_CASH;
            break;
        }
        case 3: {
            user_state = USER_MAKE_DEPOSIT;
            break;
        }
        case 4: {
            user_state = USER_RETURN_CARD;
            break;
        }
        case 5: {
            previous_state = USER_WAITING_FOR_COMMANDS;
            user_state = USER_ASKING_LANGUAGE;
            break;
        }
        default: {
            printf("%s\n", messages[9][language]);
            user_state = USER_WAITING_FOR_COMMANDS;
            break;
        }
    }
}

void process_show_budget_event() {
    printf("%s%d$\n", messages[10][language], cards[index_of_current_card].budget);
}

void exit_show_budget_state() {
    user_state = USER_WAITING_FOR_COMMANDS;
}

void enter_get_cash_state() {
    printf("%s\n", messages[3][language]);
}

void process_get_cash_event() {
    int user_request;
    READ_INT(user_request);
    if (user_request > cards[index_of_current_card].budget) {
        printf("%s\n", messages[12][language]);
        return;
    }
    if (user_request > cash_in_automate) {
        printf("%s\n", messages[11][language]);
        return;
    }
    printf("%s\n", messages[13][language]);
    cash_in_automate -= user_request;
    cards[index_of_current_card].budget -= user_request;
}

void exit_get_cash_state() {
    user_state = USER_WAITING_FOR_COMMANDS;
}

void enter_make_deposit_state() {
    printf("%s\n", messages[4][language]);
}

void process_make_deposit_event() {
    int user_request;
    READ_INT(user_request);
    printf("%s\n", messages[14][language]);
    cash_in_automate += user_request;
    cards[index_of_current_card].budget += user_request;
}

void exit_make_deposit_state() {
    user_state = USER_WAITING_FOR_COMMANDS;
}

void process_return_card_event() {
    card_in_automate = 0;
    printf("%s\n", messages[7][language]);
}

void exit_return_card_state() {
    user_state = USER_ASKING_LANGUAGE;
    previous_state = USER_WAITING_FOR_CARD;
}

void enter_asking_language_state() {
    printf("%s\n", messages[5][language]);
}

void process_asking_language_event() {
    int user_response = 0;
    READ_INT(user_response);
    while (user_response <= 0 || user_response >= 3) {
        printf("%s\n", messages[9][language]);
        READ_INT(user_response);
    }
    language = user_response - 1;
}

void exit_asking_language_state() {
    user_state = previous_state;
}
