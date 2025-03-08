#include <stdio.h>

#include "transaction.h"
#include"function.h"

void viewTransactionHistory(int transaction_count, Transaction history[]) {
    ClearSystem();
    if (transaction_count == 0) {
        printf("\nNo transactions yet.\n");
    } else {
        printf("\nTransaction History:\n");
        for (int i = 0; i < transaction_count; i++) {
            printf("%s: %.2f USD, Balance after: %.2f USD\n", history[i].type, history[i].amount, history[i].balance);
        }
    }

     PauseSystem();
}