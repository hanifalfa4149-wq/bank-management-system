#ifndef MENU_H
#define MENU_H

#include "bank.h"
#include "operations.h"

void showMainMenu(Bank *bank);
void handleMenu(Bank *bank);
void showEntryMenu();

// Customer login dan session khusus satu akun
Account *customerLogin(Bank *bank);
void handleCustomerSession(Bank *bank, Account *currentAcc);

#endif