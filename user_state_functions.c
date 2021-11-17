#include "user_state_functions.h"

struct card {
    char *number;
    char *password;
    int budget;
};


extern int size_of_database;
extern struct card *cards;
extern int state;

int language = ENGLISH;
int previous_state = 0;
char *card_number;
int index_of_current_card;
int command_index;

char *messages[10][2] = {
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
        },
        {
                "Sorry, this card is not from our bank",
                "К сожалению, это карта не из нашего банка"
        },
        {
                "Take your card",
                "Заберите карту"
        },
        {
                "Incorrect password. Number of remaining attempts: ",
                "Неверный пароль. Осталось попыток: "
        },
        {
                "Unknown command. Please, try again",
                "Неизвестная комманда. Пожалуйста, попробуйте снова"
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
    size_t length = 0;
    getline(&(card_number), &length, stdin);
    if (strncmp((card_number), "\n", 1) == 0)
        getline(&(card_number), &length, stdin);
    (card_number)[strlen(card_number) - 1] = 0;
}

void exit_waiting_for_card_state() {
    if (strncmp(card_number, "LANGUAGE", 8) == 0) {
        previous_state = WAITING_FOR_CARD_STATE;
        state = ASKING_LANGUAGE_STATE;
    } else
        state = CARD_ENTERED_STATE;
}

void process_card_entered_event() {
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
        state = RETURN_CARD_STATE;
    else
        state = GETTING_PASSWORD_STATE;
}

void enter_getting_password_state() {
    printf("%s\n", messages[1][language]);
}

void process_getting_password_event() {
    char_auto_ptr user_password;
    for (int i = 3; i > 0; --i) {
        size_t length = 0;
        getline(&(user_password), &length, stdin);
        if (strncmp((user_password), "\n", 1) == 0)
            getline(&(user_password), &length, stdin);
        (user_password)[strlen(user_password) - 1] = 0;
        if (strncmp(user_password, cards[index_of_current_card].password, 4) == 0)
            return;
        else
            printf("%s%d\n", messages[8][language], i - 1);
    }
    index_of_current_card = -1;
}

void exit_getting_password_state() {
    if (index_of_current_card == -1)
        state = RETURN_CARD_STATE;
    else
        state = WAITING_FOR_COMMANDS_STATE;
}

void enter_waiting_for_commands_state() {
    printf("%s\n", messages[2][language]);
}

void process_waiting_for_commands_event() {
    char buffer;
    scanf("%d%c", &command_index, &buffer);
}

void exit_waiting_for_commands_state() {
    switch (command_index) {
        case 1: {
            state = SHOW_BUDGET_STATE;
            break;
        }
        case 2: {
            state = GET_CASH_STATE;
            break;
        }
        case 3: {
            state = MAKE_DEPOSIT_STATE;
            break;
        }
        case 4: {
            state = RETURN_CARD_STATE;
            break;
        }
        case 5: {
            previous_state = WAITING_FOR_COMMANDS_STATE;
            state = ASKING_LANGUAGE_STATE;
            break;
        }
        default: {
            printf("%s\n", messages[9][language]);
            state = WAITING_FOR_COMMANDS_STATE;
            break;
        }
    }
}

void process_show_budget_event() {}

void exit_show_budget_state() {}

void enter_get_cash_state() {}

void process_get_cash_event() {}

void exit_get_cash_state() {}

void enter_make_deposit_state() {}

void process_make_deposit_event() {}

void exit_make_deposit_state() {}

void process_return_card_event() {
    printf("%s\n", messages[7][language]);
}

void exit_return_card_state() {
    state = WAITING_FOR_CARD_STATE;
}

void process_asking_language_event() {
    printf("%s\n", messages[5][language]);
    int user_response;
    char buffer;
    scanf("%d%c", &user_response, &buffer);
    language = user_response - 1;
}

void exit_asking_language_state() {
    state = previous_state;
}
