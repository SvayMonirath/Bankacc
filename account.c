#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#include "account.h"
#include "function.h"

// Validate password complexity
int isValidPassword(const char *password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    if (strlen(password) < Min_Pass_length) {
        return 0;
    }

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (islower(password[i])) hasLower = 1;
        if (isdigit(password[i])) hasDigit = 1;
        if (strchr("@#$%^&*!", password[i])) hasSpecial = 1;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Function implementations for SignIn, Login, DepositMoney, WithdrawMoney, etc.

// Function to display the menu
void DisplayMenu(ACCOUNT *account, int current_account) {
    ClearSystem();
    printf("\nMenu:\n");
    printf("Account Holder: %s (ID: %d)\n", account[current_account].name, account[current_account].ID);
    printf("1. Credit\n");
    printf("2. Withdraw\n");
    printf("3. Check Balance\n");
    printf("4. View Transaction History\n");
    printf("5. Send Money\n");
    printf("6. Exit\n");
}

//Function to transfer money 
void TransferMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count, int account_count) {
    ClearSystem();
    float transfer;
    int other_account_id, receive_account = -1;

    // Enter ID of the receiving account
    printf("Enter ID of the recipient account: ");
    scanf("%d", &other_account_id);

    // Find the recipient account
    for (int i = 0; i < account_count; i++) {
        if (account[i].ID == other_account_id) {
            receive_account = i;
            break;
        }
    }

    // Check if recipient exists
    if (receive_account == -1) {
        printf("Account ID not found! Transfer canceled.\n");
        PauseSystem();
        return;
    }

    // Prevent self-transfer
    if (receive_account == current_account) {
        printf("You cannot transfer money to yourself!\n");
        PauseSystem();
        return;
    }

    // Get transfer amount
    do {
        printf("\nEnter amount to transfer: ");
        scanf("%f", &transfer);

        if (transfer <= 0) {
            printf("Invalid amount! Please enter a positive value.\n");
        } else if (transfer > account[current_account].balance) {
            printf("Insufficient funds! Your balance is %.2f USD.\n", account[current_account].balance);
        }
    } while (transfer <= 0 || transfer > account[current_account].balance);

    // Perform transfer
    account[current_account].balance -= transfer;
    account[receive_account].balance += transfer;

    // Store transaction in history (sender)
    if (*transaction_count < MAX_TRANSACTIONS) {
        snprintf(history[*transaction_count].type, sizeof(history[*transaction_count].type), "Transfer to ID %d", other_account_id);
        history[*transaction_count].amount = transfer;
        history[*transaction_count].balance = account[current_account].balance;
        (*transaction_count)++;
    }

    // Store transaction in history (receiver)
    if (*transaction_count < MAX_TRANSACTIONS) {
        snprintf(history[*transaction_count].type, sizeof(history[*transaction_count].type), "Received from ID %d", account[current_account].ID);
        history[*transaction_count].amount = transfer;
        history[*transaction_count].balance = account[receive_account].balance;
        (*transaction_count)++;
    }

    printf("\n%.2f USD transferred successfully to account ID %d.\n", transfer, other_account_id);

    PauseSystem();
}


// Function to deposit money
void DepositMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count) {
    ClearSystem();
    float deposit;
    // Deposit money
    do {
        printf("\nEnter amount to deposit: ");
        scanf("%f", &deposit);
        
        if (deposit < 0) {
            printf("Invalid amount! Please enter a positive value.\n");
        }
    } while (deposit < 0);

    account[current_account].balance += deposit;

    // Store transaction in history
    if (*transaction_count < MAX_TRANSACTIONS) {
        snprintf(history[*transaction_count].type, sizeof(history[*transaction_count].type), "Deposit");
        history[*transaction_count].amount = deposit;
        history[*transaction_count].balance = account[current_account].balance;
        (*transaction_count)++;
    }

    printf("\n%.2f USD deposited successfully.\n", deposit);

    PauseSystem();
}

// Function to withdraw money
void WithDrawMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count) {
    ClearSystem();
    float withdraw;
    // Withdraw money
    do {
        printf("\nEnter amount to withdraw: ");
        scanf("%f", &withdraw);

        if (withdraw < 0) {
            printf("Invalid amount! Please enter a positive value.\n");
        } else if (withdraw > account[current_account].balance) {
            printf("Insufficient funds! Your balance is %.2f USD.\n", account[current_account].balance);
        }
    } while (withdraw < 0 || withdraw > account[current_account].balance);

    account[current_account].balance -= withdraw;

    // Store transaction
    if (*transaction_count < MAX_TRANSACTIONS) {
        snprintf(history[*transaction_count].type, sizeof(history[*transaction_count].type), "Withdraw");
        history[*transaction_count].amount = withdraw;
        history[*transaction_count].balance = account[current_account].balance;
        (*transaction_count)++;
    }

    printf("\n%.2f USD withdrawn successfully.\n", withdraw);

    PauseSystem();
}

// Function to check balance
void checkBalance(int current_account, ACCOUNT account[]) {
    ClearSystem();
    printf("\nAccount balance: %.2f USD\n", account[current_account].balance);

    PauseSystem();
}

//sign in function 

void SignIn(ACCOUNT *account, int *account_count) {

    ClearSystem();
    if (*account_count >= MAX_ACCOUNT) {
        printf("\nAccount limit reached!\n");
        return;
    }


    printf("\nCreating new account...\n");
    printf("Enter name: ");
    scanf("%s", account[*account_count].name);
    printf("Enter account ID: ");
    scanf("%d", &account[*account_count].ID);

    // Password creation with validation
    do {
        printf("Enter password: ");
        scanf("%s", account[*account_count].password);

        if (!isValidPassword(account[*account_count].password)) {
            printf("Weak password! Please try again.\n\n");
        }
    } while (!isValidPassword(account[*account_count].password));

    account[*account_count].balance = 20.00;  // Initial balance
    (*account_count)++;

    ClearSystem();
    printf("Account created successfully!\n");

    PauseSystem();
}

// Login function with improved admin check
int Login(ACCOUNT *account, int account_count) {
    int id_input;
    char password_input[20];  // Password input buffer
    int valid_login = 0;

    ClearSystem();
    printf("\nLogin to your account\n");
    printf("Enter account ID: ");
    scanf("%d", &id_input);

    // Check if the user is an admin first
    if (id_input == ADMIN_ID) {
        printf("Enter admin password: ");
        scanf("%s", password_input);

        if (strcmp(password_input, ADMIN_PASSWORD) == 0) {
            printf("Admin login successful! Welcome, Admin.\n");
            return -2; // Admin logged in, no need to return an account index
        } else {
            printf("Incorrect admin password.\n");
            return -1;
        }
    }

    // Find the account
    for (int i = 0; i < account_count; i++) {
        if (account[i].ID == id_input) {
            printf("Enter password: ");
            scanf("%s", password_input);

            // Compare passwords
            if (strcmp(password_input, account[i].password) == 0) {
                valid_login = 1;
                printf("Login successful! Welcome, %s\n", account[i].name);
                return i;  // Return the index of the logged-in account
            } else {
                printf("Incorrect password.\n");
                return -1;
            }
        }
    }

    if (!valid_login) {
        printf("Account not found or invalid credentials.\n");
        return -1;  // Invalid login
    }
    return -1;  // If no valid account or admin login
}