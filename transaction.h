#ifndef TRANSACTION_H
#define TRANSACTION_H

#define MAX_TRANSACTIONS 40

typedef struct {
    char type[20];
    float amount;
    float balance;
} Transaction;

// Function prototypes
void viewTransactionHistory(int transaction_count, Transaction history[]);

#endif