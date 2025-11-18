#ifndef BANK_H
#define BANK_H

#define MAX_ACCOUNTS 100

#include "account.h"

typedef struct Bank
{
    Account accounts[MAX_ACCOUNTS];
    int accountCount;
} Bank;

void initBank(Bank *bank);

#endif