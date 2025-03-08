#include <stdio.h>

#include "transaction.h"
#include "account.h"
#include "admin.h"
#include "function.h"

int main() {
    int choice, current_account, transaction_count = 0, account_count = 2;
    Transaction history[MAX_TRANSACTIONS];
    ACCOUNT account[MAX_ACCOUNT] = {
        {"Moni", 100, "Rothmony12!", 500.00},
        {"Rath", 200, "Rothmony12!", 300.00}
    };

    do {
        ClearSystem();
        printf("Welcome to the Banking System\n");
        printf("1. Sign In (Create a new account)\n");
        printf("2. Login (Existing account)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            SignIn(account, &account_count);
        } else if (choice == 2) {
            current_account = Login(account, account_count);
            if (current_account == -2) {
                AdminMenu(account, account_count, history, transaction_count);
            }
        }
    } while (choice != 3);

    return 0;
}
