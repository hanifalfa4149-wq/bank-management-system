#include <stdio.h>
#include <string.h>
#include "account.h"
#include "bank.h"

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
    return strcmp(acc->password, password) == 0;
}

void setAccountPassword(Account *acc, const char *password)
{
    strcpy(acc->password, password);
}