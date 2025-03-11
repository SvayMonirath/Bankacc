// account.c
#include <stdio.h>
#include <stdlib.h>
#include "account.h"

void LoadAccountDetails(ACCOUNT *account, int *account_count) {
    FILE *file = fopen("AllAccounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    *account_count = 0;
    while (fscanf(file, "Account ID: %d\n", &account[*account_count].ID) != EOF) {
        fscanf(file, "Name: %49[^\n]\n", account[*account_count].name);
        fscanf(file, "Password: %19[^\n]\n", account[*account_count].password);
        fscanf(file, "Balance: %lf\n", &account[*account_count].balance);
        fgetc(file);  // Skip the extra newline

        (*account_count)++;
    }

    fclose(file);
    printf("Account details loaded from file successfully.\n");
}

void SaveAccountDetails(ACCOUNT *account, int account_count) {
    FILE *file = fopen("AllAccounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < account_count; i++) {
        fprintf(file, "Account ID: %d\n", account[i].ID);
        fprintf(file, "Name: %s\n", account[i].name);
        fprintf(file, "Password: %s\n", account[i].password);  // You may want to exclude this for security
        fprintf(file, "Balance: %.2f\n", account[i].balance);
        fprintf(file, "----------------------------\n");
    }

    fclose(file);
    printf("Account details saved to file successfully.\n");
}
