#ifndef ADMIN_H
#define ADMIN_H

#include "bank.h"

typedef struct
{
    char masterKey[50];
    char password[50];
} AdminAccount;

// Admin management functions
int adminLogin(const char *key, const char *password);
void showAdminDashboard(Bank *bank);
void manageAccounts(Bank *bank);
void adminFreezeAccount(Bank *bank, int accountId, const char *reason);
void adminUnfreezeAccount(Bank *bank, int accountId);
void resetAccountPassword(Bank *bank, int accountId);
void viewAllAccounts(Bank *bank);
void viewAccountDetails(Bank *bank, int accountId);
void forceWithdraw(Bank *bank, int accountId, double amount, const char *reason);

#endif
