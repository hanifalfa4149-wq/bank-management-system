#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_NAME 50
#define MAX_TRANSACTIONS 100
#define MAX_PASSWORD 50

#include "transaction.h"

typedef struct Account
{
    int id;
    char name[MAX_NAME];
    char password[MAX_PASSWORD];
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

#endif