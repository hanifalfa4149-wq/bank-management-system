#ifndef STORAGE_H
#define STORAGE_H

#include "bank.h"
#include "account.h"

#define DATA_FILE "../data/data_bank.txt"

void saveAllAccounts(Bank *bank);
void loadAllAccounts(Bank *bank);
void saveAuditLog(Bank *bank);
void loadAuditLog(Bank *bank);

#endif