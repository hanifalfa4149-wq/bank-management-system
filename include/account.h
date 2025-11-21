#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_NAME 50
#define MAX_TRANSACTIONS 100
#define MAX_PASSWORD 50
#define MAX_FREEZE_REASON 200

#include "transaction.h"

typedef struct Account
{
    int id;
    char name[MAX_NAME];
    char password[MAX_PASSWORD];
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
    int isFrozen; // 0=active, 1=frozen
    char freezeReason[MAX_FREEZE_REASON];
} Account;

// Account functions
int isAccountFrozen(Account *acc);
void freezeAccount(Account *acc, const char *reason);
void unfreezeAccount(Account *acc);

#endif