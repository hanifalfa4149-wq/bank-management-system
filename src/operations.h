#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "bank.h"
#include "account.h"

void createAccount(Bank *bank);
void showAllAccounts(Bank *bank);
Account *findAccount(Bank *bank, int id);
void addTransaction(Account *acc, const char *type, double amount, const char *note);
void deposit(Bank *bank, int id, double amount);
void withdraw(Bank *bank, int id, double amount);
void showTransactionHistory(Bank *bank, int id);
int validatePassword(Account *acc, const char *password);
void setAccountPassword(Account *acc, const char *password);
void transferMoney(Bank *bank, int fromId, int toId, double amount);

#endif
