#include <stdio.h>
#include <string.h>

#include "admin.h"

#define ADMIN_PASSWORD "admin123"

int isAdmin(int id_input, char *password_input) {
    printf("Enter admin password: ");
    scanf("%s", password_input);  

    return (id_input == ADMIN_ID && strcmp(password_input, ADMIN_PASSWORD) == 0);
}

void AdminMenu(ACCOUNT *account, int account_count, Transaction history[], int transaction_count) {
    int choice;
    do {
        ClearSystem();
        printf("\nAdmin Menu:\n");
        printf("1. View All Accounts\n");
        printf("2. Delete an Account\n");
        printf("3. View All Transactions\n");
        printf("4. Exit Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            ViewAllAccounts(account, account_count);
            break;
        case 2:
            DeleteAccount(account, &account_count);
            break;
        case 3:
            ViewAllTransactions(history, transaction_count);
            break;
        case 4:
            ClearSystem();
            printf("Exiting Admin Menu...\n");
            PauseSystem();
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

void ViewAllAccounts(ACCOUNT *account, int account_count) {
    ClearSystem();
    if (account_count == 0) {
        printf("\nNo accounts available.\n");
    } else {
        printf("\nAll User Accounts:\n");
        for (int i = 0; i < account_count; i++) {
            printf("Account ID: %d, Name: %s, Balance: %.2f USD\n", 
                   account[i].ID, account[i].name, account[i].balance);
        }
    }
    PauseSystem();
}

void DeleteAccount(ACCOUNT *account, int *account_count) {
    int id_to_delete;
    ClearSystem();
    printf("\nEnter the Account ID to delete: ");
    scanf("%d", &id_to_delete);

    int found = 0;
    for (int i = 0; i < *account_count; i++) {
        if (account[i].ID == id_to_delete) {
            for (int j = i; j < *account_count - 1; j++) {
                account[j] = account[j + 1];
            }
            (*account_count)--;
            printf("Account with ID %d has been deleted successfully.\n", id_to_delete);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Account with ID %d not found.\n", id_to_delete);
    }
    PauseSystem();
}

void ViewAllTransactions(Transaction history[], int transaction_count) {
    ClearSystem();
    if (transaction_count == 0) {
        printf("\nNo transactions available.\n");
    } else {
        printf("\nAll Transaction History:\n");
        for (int i = 0; i < transaction_count; i++) {
            printf("Transaction Type: %s, Amount: %.2f USD, Balance after: %.2f USD\n", 
                   history[i].type, history[i].amount, history[i].balance);
        }
    }
    PauseSystem();
}
