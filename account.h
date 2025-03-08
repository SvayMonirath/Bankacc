#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transaction.h"

#define MAX_ACCOUNT 10
#define MAX_NAME_LENGTH 50
#define Min_Pass_length 20  

#define ADMIN_ID 9999
#define ADMIN_PASSWORD "admin123"

typedef struct {
    char name[MAX_NAME_LENGTH]; 
    int ID;  // Add this field for account ID
    char password[Min_Pass_length];
    double balance;
} ACCOUNT;

// Function prototypes
void SignIn(ACCOUNT *account, int *account_count);
int Login(ACCOUNT *account, int account_count);
int isValidPassword(const char *password);
void DisplayMenu(ACCOUNT *account, int current_account);
void DepositMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count);
void WithDrawMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count);
void checkBalance(int current_account, ACCOUNT account[]);
void TransferMoney(int current_account, ACCOUNT account[], Transaction history[], int *transaction_count, int account_count);

#endif
