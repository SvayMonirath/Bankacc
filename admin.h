#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"
#include "transaction.h"
#include "function.h"

int isAdmin(int id_input, char *password_input);
void AdminMenu(ACCOUNT *account, int account_count, Transaction history[], int transaction_count);
void ViewAllAccounts(ACCOUNT *account, int account_count);
void DeleteAccount(ACCOUNT *account, int *account_count);
void ViewAllTransactions(Transaction history[], int transaction_count);

#endif
