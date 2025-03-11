#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include"account.h"

void LoadAccountDetails(ACCOUNT *account, int *account_count);
void SaveAccountDetails(ACCOUNT *account, int account_count);

#endif