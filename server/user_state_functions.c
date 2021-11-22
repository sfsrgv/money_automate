#include "user_state_functions.h"

struct card {
    char *number;
    char *password;
    int budget;
};

extern struct card *cards;
extern int size_of_database;
extern int user_state;
extern int cash_in_automate;
extern int card_in_automate;

int language = ENGLISH;
int previous_state = WAITING_FOR_CARD_STATE;
int index_of_current_card;
int user_command_index;
char *card_number;

char *messages[17][2] = {
        {
                "-----------------\nEnter card:",
                "-----------------\nВставьте карту:"
        },
        {
                "Enter password:",
                "Введите пароль:"
        },
        {
                "\nChoose command:\n1 - Show budget\n2 - Get cash\n3 - Make a deposit\n4 - Return card\n5 - Change language",
                "\nВыберите комманду:\n1 - Посмотреть остаток\n2 - Выдача наличных\n3 - Положить на счет\n4 - Вернуть карту\n5 - Изменить язык"
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
                "-----------------\nChoose language:\n1 - English\n2 - Russian",
                "-----------------\nВыберите язык:\n1 - Английский\n2 - Русский"
        },
        {
                "Sorry, this card is not from our bank",
                "К сожалению, эта карта не из нашего банка"
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
        },
        {
                "You have ",
                "На вашем счету "
        },
        {
                "Not enough  cash in automate",
                "В автомате недостаточно наличных"
        },
        {
                "Not enough money on your card",
                "Недостаточно средств на счете"
        },
        {
                "Take your cash",
                "Возьмите деньги"
        },
        {
                "Operation made",
                "Операция проведена"
        },
        {
            "Automate if turned off",
            "Банкомат выключен"
        },
        {
            "Automate was blocked by administrator",
            "Банкомат был заблокирован администратором"
        }
};

char *print_user_state_name(int i) {
    switch (i) {
        case 0:
            return "WAITING FOR CARD\n";
        case 1:
            return "CARD ENTERED\n";
        case 2:
            return "GETTING PASSWORD\n";
        case 3:
            return "WAITING FOR COMMANDS\n";
        case 4:
            return "SHOW BUDGET\n";
        case 5:
            return "GET CASH\n";
        case 6:
            return "MAKE DEPOSIT\n";
        case 7:
            return "RETURN CARD\n";
        case 8:
            return "ASKING LANGUAGE\n";
        case -1:
            return "ERROR\n";
        default:
            return "UNKNOWN STATE\n";
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
    user_state = CARD_ENTERED_STATE;
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
        user_state = RETURN_CARD_STATE;
    else
        user_state = GETTING_PASSWORD_STATE;
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
        user_state = RETURN_CARD_STATE;
    else
        user_state = WAITING_FOR_COMMANDS_STATE;
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
            user_state = SHOW_BUDGET_STATE;
            break;
        }
        case 2: {
            user_state = GET_CASH_STATE;
            break;
        }
        case 3: {
            user_state = MAKE_DEPOSIT_STATE;
            break;
        }
        case 4: {
            user_state = RETURN_CARD_STATE;
            break;
        }
        case 5: {
            previous_state = WAITING_FOR_COMMANDS_STATE;
            user_state = ASKING_LANGUAGE_STATE;
            break;
        }
        default: {
            printf("%s\n", messages[9][language]);
            user_state = WAITING_FOR_COMMANDS_STATE;
            break;
        }
    }
}

void process_show_budget_event() {
    printf("%s%d$\n", messages[10][language], cards[index_of_current_card].budget);
}

void exit_show_budget_state() {
    user_state = WAITING_FOR_COMMANDS_STATE;
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
    user_state = WAITING_FOR_COMMANDS_STATE;
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
    user_state = WAITING_FOR_COMMANDS_STATE;
}

void process_return_card_event() {
    card_in_automate = 0;
    printf("%s\n", messages[7][language]);
}

void exit_return_card_state() {
    user_state = ASKING_LANGUAGE_STATE;
    previous_state = WAITING_FOR_CARD_STATE;
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
