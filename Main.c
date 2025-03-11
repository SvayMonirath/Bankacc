#include <stdio.h>
#include "transaction.h"
#include "account.h"
#include "admin.h"
#include "function.h"
#include "FileOperation.h"

int main() {
    int choice, current_account, transaction_count = 0, account_count = 2;
    Transaction history[MAX_TRANSACTIONS];
    ACCOUNT account[MAX_ACCOUNT] = {
        {"Moni", 100, "Rothmony12!", 500.00},
        {"Rath", 200, "Rothmony12!", 300.00}
    };

    // Load saved account details from file
    LoadAccountDetails(account, &account_count);

    do {
        ClearSystem();
        printf("Welcome to the Banking System\n");
        printf("1. Sign Up (Create a new account)\n");
        printf("2. Log In (Existing account)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            SignUp(account, &account_count);
        } else if (choice == 2) {
            current_account = Login(account, account_count);
            if (current_account == -2) {
                AdminMenu(account, account_count, history, transaction_count);
            } else if (current_account >= 0) { // Regular user logged in
                int menu_choice;
                do {
                    DisplayMenu(account, current_account);
                    scanf("%d", &menu_choice);

                    switch (menu_choice) {
                        case 1:
                            DepositMoney(current_account, account, history, &transaction_count);
                            break;
                        case 2:
                            WithDrawMoney(current_account, account, history, &transaction_count);
                            break;
                        case 3:
                            checkBalance(current_account, account);
                            break;
                        case 4:
                            viewTransactionHistory(transaction_count, history);
                            break;
                        case 5:
                            TransferMoney(current_account, account, history, &transaction_count, account_count);
                            break;
                        case 6:
                            printf("\nLogging out...\n");
                            break;
                        default:
                            printf("Invalid option! Try again.\n");
                    }
                } while (menu_choice != 6);

                // Save account details after the user logs out
                SaveAccountDetails(account, account_count);
            } else {
                printf("Login failed. Try again.\n");
            }
        }
    } while (choice != 3);

    return 0;
}
