#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/bank.h"
#include "../include/audit.h"

// Get current timestamp
void getCurrentTimestamp(char *timestamp)
{
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", localTime);
}

// Add audit entry
void addAuditEntry(Bank *bank, const char *admin, const char *action,
                   int targetAccountId, const char *description)
{
    if (bank->auditCount >= MAX_AUDIT_ENTRIES)
    {
        printf("Audit log is full!\n");
        return;
    }

    AuditLogEntry *entry = &bank->auditLog[bank->auditCount];
    entry->logId = bank->auditCount + 1;

    strcpy(entry->adminName, admin);
    strcpy(entry->actionType, action);
    entry->targetAccountId = targetAccountId;
    getCurrentTimestamp(entry->timestamp);
    strcpy(entry->description, description);
    strcpy(entry->details, "-");

    bank->auditCount++;
}

// View audit log
void viewAuditLog(Bank *bank)
{
    printf("\n");
    printf("========================================\n");
    printf("          AUDIT LOG (%d entries)\n", bank->auditCount);
    printf("========================================\n");

    if (bank->auditCount == 0)
    {
        printf("No audit entries yet.\n");
        return;
    }

    printf("%-5s %-10s %-20s %-12s %-19s\n",
           "ID", "Admin", "Action", "Account", "Timestamp");
    printf("========================================\n");

    for (int i = 0; i < bank->auditCount; i++)
    {
        AuditLogEntry *entry = &bank->auditLog[i];
        printf("%-5d %-10s %-20s %-12d %-19s\n",
               entry->logId,
               entry->adminName,
               entry->actionType,
               entry->targetAccountId,
               entry->timestamp);
        printf("  Description: %s\n", entry->description);
    }

    printf("========================================\n");
}
