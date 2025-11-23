#include <stdio.h>
#include "../include/account.h"
#include "../include/bank.h"
#include "../include/utils.h"

void createAccount(Bank *bank)
{
    if (bank->accountCount >= MAX_ACCOUNTS)
    {
        printf("Kapasitas akun penuh!\n");
        return;
    }

    Account *acc = &bank->accounts[bank->accountCount];

    acc->id = bank->accountCount + 1;
    printf("Masukkan nama: ");
    scanf("%s", acc->name);

    printf("Masukkan password: ");
    scanf("%s", acc->password);

    acc->balance = 0;
    acc->transactionCount = 0;

    bank->accountCount++;

    printf("Akun berhasil dibuat! ID: %d\n", acc->id);
}

Account *findAccount(Bank *bank, int id)
{
    for (int i = 0; i < bank->accountCount; i++)
    {
        if (bank->accounts[i].id == id)
            return &bank->accounts[i];
    }
    return NULL;
}

void showAllAccounts(Bank *bank)
{
    if (bank->accountCount == 0)
    {
        printf("Belum ada akun yang terdaftar.\n");
        return;
    }

    printf("\n=== DAFTAR AKUN ===\n");
    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];
        printf("ID: %d | Nama: %s | Saldo: %.2lf\n",
               acc->id, acc->name, acc->balance);
    }
}

int validatePassword(Account *acc, const char *password)
{
    return bandingkanString(acc->password, password) == 0;
}

void setAccountPassword(Account *acc, const char *password)
{
    salinString(acc->password, password);
}

int isAccountFrozen(Account *acc)
{
    return acc->isFrozen;
}

void freezeAccount(Account *acc, const char *reason)
{
    acc->isFrozen = 1;
    salinString(acc->freezeReason, reason);
}

void unfreezeAccount(Account *acc)
{
    acc->isFrozen = 0;
    salinString(acc->freezeReason, "");
}

// Hapus akun dari bank dengan menggeser array accounts
void closeAccount(Bank *bank, int accountId)
{
    int index = -1;
    int i;

    for (i = 0; i < bank->accountCount; i++)
    {
        if (bank->accounts[i].id == accountId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Account not found!\n");
        return;
    }

    for (i = index; i < bank->accountCount - 1; i++)
    {
        bank->accounts[i] = bank->accounts[i + 1];
    }

    bank->accountCount--;
    printf("Account %d has been closed.\n", accountId);
}