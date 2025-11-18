#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "bank.h"
#include "account.h"
#include "operations.h"
#include "utils.h"

void addTransaction(Account *acc, const char *type, double amount, const char *note)
{
    Transaction *t = &acc->transactions[acc->transactionCount];

    strcpy(t->type, type);
    t->amount = amount;
    strcpy(t->note, note);
    strcpy(t->date, "2025-01-01");

    acc->transactionCount++;
}

void deposit(Bank *bank, int id, double amount)
{
    Account *acc = findAccount(bank, id);
    if (!acc)
    {
        printf("Akun tidak ditemukan!\n");
        return;
    }

    acc->balance += amount;
    addTransaction(acc, "DEPOSIT", amount, "Setoran dana");

    printf("Deposit berhasil! Saldo baru: %.2lf\n", acc->balance);
}

void withdraw(Bank *bank, int id, double amount)
{
    Account *acc = findAccount(bank, id);
    if (!acc)
    {
        printf("Akun tidak ditemukan!\n");
        return;
    }

    if (acc->balance < amount)
    {
        printf("Saldo tidak cukup!\n");
        return;
    }

    acc->balance -= amount;
    addTransaction(acc, "WITHDRAW", amount, "Penarikan dana");

    printf("Withdraw berhasil! Saldo baru: %.2lf\n", acc->balance);
}

void showTransactionHistory(Bank *bank, int id)
{
    Account *acc = findAccount(bank, id);
    if (!acc)
    {
        printf("Akun tidak ditemukan!\n");
        return;
    }

    printf("\n=== RIWAYAT TRANSAKSI (%s) ===\n", acc->name);

    if (acc->transactionCount == 0)
    {
        printf("Belum ada transaksi.\n");
        return;
    }

    for (int i = 0; i < acc->transactionCount; i++)
    {
        Transaction *t = &acc->transactions[i];
        printf("%s | %.2lf | %s | %s\n",
               t->type, t->amount, t->date, t->note);
    }
}

void transferMoney(Bank *bank, int fromId, int toId, double amount)
{
    Account *fromAcc = findAccount(bank, fromId);
    Account *toAcc = findAccount(bank, toId);

    if (!fromAcc)
    {
        printf("Akun pengirim tidak ditemukan!\n");
        return;
    }

    if (!toAcc)
    {
        printf("Akun penerima tidak ditemukan!\n");
        return;
    }

    if (fromAcc->balance < amount)
    {
        printf("Saldo tidak cukup! Saldo Anda: %.2lf\n", fromAcc->balance);
        return;
    }

    char password[50];
    printf("Masukkan password akun Anda: ");
    scanf("%s", password);

    if (!validatePassword(fromAcc, password))
    {
        printf("Password salah!\n");
        return;
    }

    fromAcc->balance -= amount;
    toAcc->balance += amount;

    char note[60];
    sprintf(note, "Transfer ke %s", toAcc->name);
    addTransaction(fromAcc, "TRANSFER", amount, note);

    sprintf(note, "Transfer dari %s", fromAcc->name);
    addTransaction(toAcc, "TRANSFER", amount, note);

    printf("Transfer berhasil! Saldo baru: %.2lf\n", fromAcc->balance);
}