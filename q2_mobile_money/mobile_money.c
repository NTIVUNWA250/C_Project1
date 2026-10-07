#include <stdio.h>

#define LOG_FILE "transactions.log"

/* This is to record every transaction attempt in the log file */
void log_transaction(const char *message, long amount, long balance)
{
    FILE *log = fopen(LOG_FILE, "a");
    if (log == NULL) {
        return; /* to avoid logging errors from stopping the program to continue its work */
    }
    fprintf(log, "%s amount=%ld balance=%ld\n", message, amount, balance);
    fclose(log);
}

/* After the input line fails, clear the input buffer */
void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/*Displays the menu to the user*/
void show_menu(void)
{
    printf("\n===== MOBILE MONEY TRANSACTION SYSTEM =====\n\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Check Balance\n");
    printf("4. Transaction Summary\n");
    printf("5. Exit\n\n");
}

/*main function that controls the program flow*/
int main(void)
{
    long balance = 0;      /* Whole numbers are enough here, as RWF has no cents */
    long amount = 0;
    int deposits = 0;
    int withdrawals = 0;
    int choice = 0;
    int running = 1;

    show_menu();

    while (running) {
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_input();
            printf("Invalid input. Please enter a number from 1 to 5.\n\n");
            continue; /* brings the user back to the menu when the input is invalid */
        }

        switch (choice) {
        case 1:
            printf("Enter deposit amount: ");
            if (scanf("%ld", &amount) != 1) {
                clear_input();
                printf("Invalid amount. Please enter a whole number.\n\n");
                continue;
            }
            if (amount <= 0) {
                printf("Transaction rejected: Amount must be positive.\n\n");
                log_transaction("DEPOSIT REJECTED", amount, balance);
                break;
            }
            balance += amount;
            deposits++;
            printf("Deposit successful.\n");
            printf("Current balance: %ld RWF\n\n", balance);
            log_transaction("DEPOSIT OK", amount, balance);
            break;

        case 2:
            printf("Enter withdrawal amount: ");
            if (scanf("%ld", &amount) != 1) {
                clear_input();
                printf("Invalid amount. Please enter a whole number.\n\n");
                continue;
            }
            if (amount <= 0) {
                printf("Transaction rejected: Amount must be positive.\n\n");
                log_transaction("WITHDRAW REJECTED", amount, balance);
                break;
            }
            if (amount > balance) {
                printf("Transaction rejected: Insufficient balance.\n\n");
                log_transaction("WITHDRAW REJECTED", amount, balance);
                break;
            }
            balance -= amount;
            withdrawals++;
            printf("Withdrawal successful.\n");
            printf("Current balance: %ld RWF\n\n", balance);
            log_transaction("WITHDRAW OK", amount, balance);
            break;

        case 3:
            printf("Current balance: %ld RWF\n\n", balance);
            break;

        case 4:
            printf("Successful deposits: %d\n", deposits);
            printf("Successful withdrawals: %d\n", withdrawals);
            printf("Current balance: %ld RWF\n\n", balance);
            break;

        case 5:
            printf("System terminated.\n");
            running = 0; /* this ends the loop */
            break;

        default:
            printf("Invalid choice. Please enter a number from 1 to 5.\n\n");
            continue;
        }
    }

    return 0;
}