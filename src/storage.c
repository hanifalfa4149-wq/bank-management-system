#include <stdio.h>
#include "../include/storage.h"
#include "../include/transaction.h"
#include "../include/audit.h"
#include "../include/utils.h"

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

        fprintf(fp, "%d|%s|%s|%.2lf|%d|%d|%s\n",
                acc->id, acc->name, acc->password, acc->balance,
                acc->transactionCount, acc->isFrozen, acc->freezeReason);

        for (int j = 0; j < acc->transactionCount; j++)
        {
            Transaction *t = &acc->transactions[j];
            fprintf(fp, "%s|%.2lf|%s|%s\n",
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

    if (fscanf(fp, "%d\n", &bank->accountCount) != 1)
    {
        printf("Format file data tidak valid.\n");
        fclose(fp);
        bank->accountCount = 0;
        return;
    }

    if (bank->accountCount > MAX_ACCOUNTS)
    {
        bank->accountCount = MAX_ACCOUNTS;
    }

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];
        char line[512];

        if (!fgets(line, sizeof(line), fp))
        {
            bank->accountCount = i;
            break;
        }

        if (sscanf(line, "%d|%49[^|]|%49[^|]|%lf|%d|%d|%199[^\n]",
                   &acc->id, acc->name, acc->password, &acc->balance,
                   &acc->transactionCount, &acc->isFrozen, acc->freezeReason) < 6)
        {
            printf("Baris akun tidak valid, melewati sisa data.\n");
            bank->accountCount = i;
            break;
        }

        if (acc->transactionCount < 0)
            acc->transactionCount = 0;
        if (acc->transactionCount > MAX_TRANSACTIONS)
            acc->transactionCount = MAX_TRANSACTIONS;

        for (int j = 0; j < acc->transactionCount; j++)
        {
            Transaction *t = &acc->transactions[j];

            if (!fgets(line, sizeof(line), fp))
            {
                acc->transactionCount = j;
                break;
            }

            if (sscanf(line, "%19[^|]|%lf|%19[^|]|%59[^\n]",
                       t->type, &t->amount, t->date, t->note) < 3)
            {
                acc->transactionCount = j;
                break;
            }
        }
    }

    fclose(fp);
    printf("Data berhasil dimuat!\n");
}

void saveAuditLog(Bank *bank)
{
    FILE *fp = fopen("../data/audit_log.txt", "w");
    if (!fp)
    {
        return;
    }

    fprintf(fp, "%d\n", bank->auditCount);

    for (int i = 0; i < bank->auditCount; i++)
    {
        AuditLogEntry *entry = &bank->auditLog[i];
        fprintf(fp, "%d|%s|%s|%d|%s|%s|%s\n",
                entry->logId, entry->adminName, entry->actionType,
                entry->targetAccountId, entry->timestamp,
                entry->description, entry->details);
    }

    fclose(fp);
}

void loadAuditLog(Bank *bank)
{
    FILE *fp = fopen("../data/audit_log.txt", "r");
    if (!fp)
    {
        bank->auditCount = 0;
        return;
    }

    fscanf(fp, "%d\n", &bank->auditCount);

    for (int i = 0; i < bank->auditCount && i < MAX_AUDIT_ENTRIES; i++)
    {
        AuditLogEntry *entry = &bank->auditLog[i];
        char line[1024];

        if (fgets(line, sizeof(line), fp) == NULL)
            break;

        sscanf(line, "%d|%49[^|]|%49[^|]|%d|%19[^|]|%299[^|]|%299[^\n]",
               &entry->logId, entry->adminName, entry->actionType,
               &entry->targetAccountId, entry->timestamp,
               entry->description, entry->details);
    }

    fclose(fp);
}