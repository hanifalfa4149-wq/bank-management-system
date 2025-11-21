#ifndef BANK_H
#define BANK_H

#define MAX_ACCOUNTS 100
#define MAX_AUDIT_ENTRIES 1000

#include "account.h"
#include "audit.h"

typedef struct Bank
{
    Account accounts[MAX_ACCOUNTS];
    int accountCount;
    AuditLogEntry auditLog[MAX_AUDIT_ENTRIES];
    int auditCount;
} Bank;

void initBank(Bank *bank);

#endif