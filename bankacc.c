//implementation: login/signin, administration, check transaction history, transfer money, 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include<stdbool.h>

#define MAX_TRANSACTIONS 40
#define MAX_ACCOUNT 2
#define Min_Pass_length 8

#define ADMIN_ID 1
#define ADMIN_PASSWORD "admin123"


// Struct definitions
typedef struct {
   char type[10];
   float amount;
   float balance;
} Transaction;

typedef struct {
   char name[100];
   int ID;
   char password[20];
   float balance;
} ACCOUNT;

// Function prototypes (menu)
int isValidPassword(const char *password);
void DisplayMenu(ACCOUNT *account, int current_account);
void DepositMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count);
void WithDrawMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count);
void checkBalance(int current_account, ACCOUNT account[]);
void viewTransactionHistory(int transaction_count, Transaction history[]);
void TransferMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count, int account_count);

// Function prototypes for login and sign-in
void SignIn(ACCOUNT *account, int *account_count);
int Login(ACCOUNT *account, int account_count);

//Function prototype for admin
int isAdmin(int id_input, char *password_input);
void AdminMenu(ACCOUNT *account, int account_count, Transaction history[], int transaction_count) ;
void ViewAllAccounts(ACCOUNT *account, int account_count);
void DeleteAccount(ACCOUNT *account, int *account_count);
void ViewAllTransactions(Transaction history[], int transaction_count);

int main(void) {

    // Declare variables 
    int choice, current_account, transaction_count = 0, account_count = 2;
    float withdraw, deposit;

    // Struct array
    Transaction history[MAX_TRANSACTIONS];
    ACCOUNT account[MAX_ACCOUNT] = {
        {"Moni", 100, "Rothmony12!", 500.00}, 
        {"Rath", 200, "Rothmony12!", 300.00}
    };

    // Main loop for selecting Sign In or Login
    do {
        system("cls");
        printf("Welcome to the Banking System\n");
        printf("1. Sign In (Create a new account)\n");
        printf("2. Login (Existing account)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // Sign In 
            SignIn(account, &account_count);
            break;
        case 2: 
            // Log In
            current_account = Login(account, account_count);
            if (current_account > -1) {
                // Proceed to menu

                do {
                    DisplayMenu(account, current_account);

                    // Prompt user for choice
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                    case 1: DepositMoney(current_account, account, history, &transaction_count); break;
                    case 2: WithDrawMoney(current_account, account, history, &transaction_count); break;
                    case 3: checkBalance(current_account, account); break;
                    case 4: viewTransactionHistory(transaction_count, history); break;
                    case 5: TransferMoney( current_account,  account,  history,  &transaction_count,  account_count); break;
                    case 6:
                        system("cls");
                        printf("\nExiting account...\n");
                        getchar();
                        getchar();
                        break;

                    default:
                        printf("\nInvalid choice! Please enter a valid option.\n");
                    }

                } while (choice != 5);

            } else if(current_account = -2) {
                AdminMenu(account, account_count, history, transaction_count);
            }
            break;
        case 3:
            system("cls");
            printf("\nExiting the system...\n");
            break;
        
        default:
            printf("\nInvalid choice! Please enter a valid option.\n");
            getchar();
            break;
        }
    } while (choice != 3);
    
    return 0;
}


//*************************************************************************************************************************************************/

// Function to validate password complexity
int isValidPassword(const char *password) {
    int hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    //does it reach the minimum amount 
    if (strlen(password) < Min_Pass_length) {
        return false;
    }

    for (int i = false; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
        if (strchr("@#$%^&*!", password[i])) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}


//*************************************************************************************************************************************************/

// Function to display the menu
void DisplayMenu(ACCOUNT *account, int current_account) {
    system("cls");
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
    system("cls");
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
        getchar();
        printf("Press Enter to exit\n");
        getchar();
        return;
    }

    // Prevent self-transfer
    if (receive_account == current_account) {
        printf("You cannot transfer money to yourself!\n");
        getchar();
        printf("Press Enter to exit\n");
        getchar();
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

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}


// Function to deposit money
void DepositMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count) {
    system("cls");
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

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

// Function to withdraw money
void WithDrawMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count) {
    system("cls");
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

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

// Function to check balance
void checkBalance(int current_account, ACCOUNT account[]) {
    system("cls");
    printf("\nAccount balance: %.2f USD\n", account[current_account].balance);

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

// Function to view transaction history
void viewTransactionHistory(int transaction_count, Transaction history[]) {
    system("cls");
    if (transaction_count == 0) {
        printf("\nNo transactions yet.\n");
    } else {
        printf("\nTransaction History:\n");
        for (int i = 0; i < transaction_count; i++) {
            printf("%s: %.2f USD, Balance after: %.2f USD\n", history[i].type, history[i].amount, history[i].balance);
        }
    }

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}


//*************************************************************************************************************************************************/
//sign in function 

void SignIn(ACCOUNT *account, int *account_count) {

    system("cls");
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

    system("cls");
    printf("Account created successfully!\n");

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

// Login function with improved admin check
int Login(ACCOUNT *account, int account_count) {
    int id_input;
    char password_input[20];  // Password input buffer
    int valid_login = 0;

    system("cls");
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

//*************************************************************************************************************************************************/


int isAdmin(int id_input, char *password_input) {
    printf("Enter admin password: ");
    scanf("%s", password_input);  // Prompt for password

    if (id_input == ADMIN_ID && strcmp(password_input, ADMIN_PASSWORD) == 0) {
        return 1;  // Return 1 if the user is an admin
    }
    return 0;  // If not admin
}

void AdminMenu(ACCOUNT *account, int account_count, Transaction history[], int transaction_count) {
    int choice;

    do {
        system("cls");
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
            system("cls");
            printf("Exiting Admin Menu...\n");

            getchar();
            printf("Press Enter to exit\n");
            getchar();

            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

void ViewAllAccounts(ACCOUNT *account, int account_count) {
    system("cls");
    if (account_count == 0) {
        printf("\nNo accounts available.\n");
    } else {
        printf("\nAll User Accounts:\n");
        for (int i = 0; i < account_count; i++) {
            printf("Account ID: %d, Name: %s, Balance: %.2f USD\n", account[i].ID, account[i].name, account[i].balance);
        }
    }

    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

void DeleteAccount(ACCOUNT *account, int *account_count) {
    int id_to_delete;
    system("cls");
    printf("\nEnter the Account ID to delete: ");
    scanf("%d", &id_to_delete);

    int found = 0;
    for (int i = 0; i < *account_count; i++) {
        if (account[i].ID == id_to_delete) {
            // Delete the account by shifting all accounts after it to the left
            for (int j = i; j < *account_count - 1; j++) {
                account[j] = account[j + 1];
            }
            (*account_count)--;  // Decrease account count
            printf("Account with ID %d has been deleted successfully.\n", id_to_delete);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account with ID %d not found.\n", id_to_delete);
    }
    getchar();
    printf("Press Enter to exit\n");
    getchar();
}

void ViewAllTransactions(Transaction history[], int transaction_count) {

    system("cls");
    if (transaction_count == 0) {
        printf("\nNo transactions available.\n");
    } else {
        printf("\nAll Transaction History:\n");
        for (int i = 0; i < transaction_count; i++) {
            printf("Transaction Type: %s, Amount: %.2f USD, Balance after: %.2f USD\n", 
                   history[i].type, history[i].amount, history[i].balance);
        }
    }
    getchar();
    printf("Press Enter to exit\n");
    getchar();
}




