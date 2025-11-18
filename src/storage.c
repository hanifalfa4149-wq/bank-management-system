#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "transaction.h"
#include "utils.h"

void saveAllAccounts(Bank *bank)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(fp, "%d\n", bank->accountCount);

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];

        fprintf(fp, "%d %s %s %.2lf %d\n",
                acc->id, acc->name, acc->password, acc->balance, acc->transactionCount);

        for (int j = 0; j < acc->transactionCount; j++)
        {
            Transaction *t = &acc->transactions[j];
            fprintf(fp, "%s %.2lf %s %s\n",
                    t->type, t->amount, t->date, t->note);
        }
    }

    fclose(fp);
    printf("Data berhasil disimpan!\n");
}

void loadAllAccounts(Bank *bank)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp)
    {
        printf("Belum ada file data.\n");
        return;
    }

    fscanf(fp, "%d", &bank->accountCount);

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];

        fscanf(fp, "%d %s %s %lf %d",
               &acc->id, acc->name, acc->password, &acc->balance, &acc->transactionCount);

        for (int j = 0; j < acc->transactionCount; j++)
        {
            Transaction *t = &acc->transactions[j];
            fscanf(fp, "%s %lf %s", t->type, &t->amount, t->date);
            fgets(t->note, sizeof(t->note), fp);
            trimTrailingNewline(t->note);
        }
    }

    fclose(fp);
    printf("Data berhasil dimuat!\n");
}