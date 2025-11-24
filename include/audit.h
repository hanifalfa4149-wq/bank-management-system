#ifndef AUDIT_H
#define AUDIT_H

#define MAX_AUDIT_ACTION 50
#define MAX_AUDIT_DESC 300
#define MAX_AUDIT_DETAILS 300

typedef struct
{
    int logId;
    char adminName[50];
    char actionType[MAX_AUDIT_ACTION];
    int targetAccountId; // -1 if N/A
    char timestamp[20];
    char description[MAX_AUDIT_DESC];
    char details[MAX_AUDIT_DETAILS];
} AuditLogEntry;

typedef struct Bank Bank;

void addAuditEntry(Bank *bank, const char *admin, const char *action,
                   int targetAccountId, const char *description);
void viewAuditLog(Bank *bank);

#endif
