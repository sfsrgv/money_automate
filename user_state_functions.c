#include "user_state_functions.h"

int language = ENGLISH;
int previous_state = 0;
extern int state;

char *card_number;

char *messages[6][2] = {
        {
                "Enter card:",
                "Вставьте карту:"
        },
        {
                "Enter password:",
                "Введите пароль:"
        },
        {
                "Choose command:\n1 - Show budget\n2 - Get cash\n3 - Make a deposit\n4 - Return card\n5 - Change language",
                "Выберите комманду:\n1 - Посмотреть остаток\n2 - Выдача наличных\n3 - Положить на счет\n4 - Вернуть карту\n5 - Изменить язык"
        },
        {
                "Enter sum to get:",
                "Введите сумму выдачи:"
        },
        {
                "Enter sum of deposit:",
                "Введите сумму для зачисления на счет:"
        },
        {
                "Choose language:\n1 - English\n2 - Russian",
                "Выберите язык:\n1 - Английский\n2 - Русский"
        }
};

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

void enter_waiting_for_card_state() {
    printf("%s\n", messages[0][language]);
}

void process_waiting_for_card_event() {
    free(card_number);
    size_t length = 0;
    getline(&(card_number), &length, stdin);
    if (strncmp(card_number, "\n", 1) == 0)
        getline(&(card_number), &length, stdin);
    (card_number)[strlen(card_number) - 1] = 0;
}

void exit_waiting_for_card_state() {
    printf("card number: %s\n", card_number);
    if (strncmp(card_number, "LANGUAGE", 8) == 0) {
        previous_state = WAITING_FOR_CARD_STATE;
        state = ASKING_LANGUAGE_STATE;
    } else
        state = CARD_ENTERED_STATE;
}

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

void process_asking_language_event() {
    printf("%s\n", messages[5][language]);
    int user_response;
    scanf("%d", &user_response);
    language = user_response - 1;
}

void exit_asking_language_state() {
    state = previous_state;
}
