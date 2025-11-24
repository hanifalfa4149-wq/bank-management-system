#include <stdio.h>
#include "../include/admin.h"
#include "../include/audit.h"
#include "../include/operations.h"
#include "../include/utils.h"
#include "../include/account.h"

// Default admin credentials
#define ADMIN_KEY "ADMIN"
#define ADMIN_PASSWORD "admin123"

// Validate admin login
int adminLogin(const char *key, const char *password)
{
    if (bandingkanString(key, ADMIN_KEY) == 0 && bandingkanString(password, ADMIN_PASSWORD) == 0)
    {
        return 1; // Success
    }
    return 0; // Failed
}

// View all accounts
void viewAllAccounts(Bank *bank)
{
    printf("\n");
    printf("========================================\n");
    printf("        ALL ACCOUNTS (%d total)\n", bank->accountCount);
    printf("========================================\n");

    if (bank->accountCount == 0)
    {
        printf("Belum ada akun yang dibuat.\n");
        return;
    }

    printf("%-5s %-20s %-15s %-10s\n",
           "ID", "Name", "Balance", "Status");
    printf("----------------------------------------\n");

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];
        const char *status = acc->isFrozen ? "FROZEN" : "ACTIVE";
        printf("%-5d %-20s Rp %-13.2lf %-10s\n",
               acc->id, acc->name, acc->balance, status);
    }

    printf("========================================\n");
}

// View account details
void viewAccountDetails(Bank *bank, int accountId)
{
    Account *acc = findAccount(bank, accountId);

    if (acc == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    printf("\n");
    printf("========================================\n");
    printf("     ACCOUNT DETAILS - %s (ID: %d)\n", acc->name, acc->id);
    printf("========================================\n");
    printf("Name: %s\n", acc->name);
    printf("ID: %d\n", acc->id);
    printf("Balance: Rp %.2lf\n", acc->balance);
    printf("Status: %s\n", acc->isFrozen ? "FROZEN" : "ACTIVE");

    if (acc->isFrozen)
    {
        printf("Freeze Reason: %s\n", acc->freezeReason);
    }

    printf("\nTRANSACTION HISTORY:\n");
    printf("----------------------------------------\n");

    if (acc->transactionCount == 0)
    {
        printf("Belum ada transaksi\n");
    }
    else
    {
        printf("%-12s %-12s %-15s %s\n",
               "Date", "Type", "Amount", "Note");
        printf("----------------------------------------\n");

        for (int i = 0; i < acc->transactionCount; i++)
        {
            Transaction *trans = &acc->transactions[i];
            printf("%-12s %-12s Rp %-13.2lf %s\n",
                   trans->date, trans->type, trans->amount, trans->note);
        }
    }

    printf("========================================\n");
}

// Freeze account
void adminFreezeAccount(Bank *bank, int accountId, const char *reason)
{
    Account *acc = findAccount(bank, accountId);

    if (acc == NULL)
    {
        printf("Akun tidak ditemukan!\n");
        return;
    }

    if (acc->isFrozen)
    {
        printf("Akun sudah dibekukan\n");
        return;
    }

    freezeAccount(acc, reason);

    char description[300];
    sprintf(description, "Akun dibekukan. alasannya: %s", reason);
    addAuditEntry(bank, "ADMIN", "FREEZE_ACCOUNT", accountId, description);

    printf("✓ Akun %d (%s) sudah dibekukan.\n", accountId, acc->name);
}

// Unfreeze account
void adminUnfreezeAccount(Bank *bank, int accountId)
{
    Account *acc = findAccount(bank, accountId);

    if (acc == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    if (!acc->isFrozen)
    {
        printf("Account is not frozen!\n");
        return;
    }

    unfreezeAccount(acc);

    addAuditEntry(bank, "ADMIN", "UNFREEZE_ACCOUNT", accountId,
                  "Account unfrozen");

    printf("✓ Account %d (%s) has been unfrozen.\n", accountId, acc->name);
}

// Reset account password
void resetAccountPassword(Bank *bank, int accountId)
{
    Account *acc = findAccount(bank, accountId);

    if (acc == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    char newPassword[50];
    printf("Enter new password: ");
    scanf("%s", newPassword);

    char oldPassword[50];
    salinString(oldPassword, acc->password);

    salinString(acc->password, newPassword);

    char description[300];
    sprintf(description, "Password reset for account %d (%s)", accountId, acc->name);
    addAuditEntry(bank, "ADMIN", "RESET_PASSWORD", accountId, description);

    printf("✓ Password reset successfully.\n");
    printf("New password: %s (Customer should change this after login)\n", newPassword);
}

// Force withdraw
void forceWithdraw(Bank *bank, int accountId, double amount, const char *reason)
{
    Account *acc = findAccount(bank, accountId);

    if (acc == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    if (amount <= 0)
    {
        printf("Invalid amount!\n");
        return;
    }

    acc->balance -= amount;

    // Log transaction
    if (acc->transactionCount < MAX_TRANSACTIONS)
    {
        Transaction *trans = &acc->transactions[acc->transactionCount];
        salinString(trans->type, "FORCE_WITHDRAW");
        trans->amount = amount;
        salinString(trans->date, "");
        salinString(trans->note, "Force withdraw by admin: ");
        gabungkanString(trans->note, reason);
        acc->transactionCount++;
    }

    char description[300];
    sprintf(description, "Force withdraw from account %d. Reason: %s", accountId, reason);
    addAuditEntry(bank, "ADMIN", "FORCE_WITHDRAW", accountId, description);

    printf("✓ Withdrawn Rp %.2lf from account %d.\n", amount, accountId);
    printf("  New balance: Rp %.2lf\n", acc->balance);
}

// Manage accounts submenu
void manageAccounts(Bank *bank)
{
    int choice;
    int accountId;
    char reason[200];
    double amount;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("       MANAGE ACCOUNTS\n");
        printf("========================================\n");
        printf("1. Freeze Account\n");
        printf("2. Unfreeze Account\n");
        printf("3. Reset Password\n");
        printf("4. View Account Details\n");
        printf("5. Force Withdraw\n");
        printf("0. Back\n");
        printf("========================================\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Masukkan ID yang ingin dibekukan: ");
            scanf("%d", &accountId);
            printf("Apa alasan akun ini dibekukan?: ");
            scanf(" %[^\n]", reason);
            adminFreezeAccount(bank, accountId, reason);
            break;

        case 2:
            printf("masukkan ID akun: ");
            scanf("%d", &accountId);
            adminUnfreezeAccount(bank, accountId);
            break;

        case 3:
            printf("Masukkan ID akun: ");
            scanf("%d", &accountId);
            resetAccountPassword(bank, accountId);
            break;

        case 4:
            printf("Masukkan ID akun: ");
            scanf("%d", &accountId);
            viewAccountDetails(bank, accountId);
            break;

        case 5:
            printf("Masukkan ID akun: ");
            scanf("%d", &accountId);
            printf("Nominal withdraw: ");
            scanf("%lf", &amount);
            printf("Alasan withdraw?: ");
            scanf(" %[^\n]", reason);
            forceWithdraw(bank, accountId, amount, reason);
            break;

        case 0:
            printf("kembali ke dashboar admin\n");
            break;

        default:
            printf("Pilihan kamu invalid\n");
        }

    } while (choice != 0);
}

// Generate report
void generateReport(Bank *bank)
{
    printf("\n");
    printf("========================================\n");
    printf("     BANK STATISTICS & REPORTS\n");
    printf("========================================\n");

    printf("Total akun: %d\n", bank->accountCount);

    int activeCount = 0, frozenCount = 0;
    double totalBalance = 0;
    double highestBalance = 0;
    double lowestBalance = 999999999;
    int totalTransactions = 0;

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];

        if (acc->isFrozen)
            frozenCount++;
        else
            activeCount++;

        totalBalance += acc->balance;

        if (acc->balance > highestBalance)
            highestBalance = acc->balance;
        if (acc->balance < lowestBalance)
            lowestBalance = acc->balance;

        totalTransactions += acc->transactionCount;
    }

    printf("akun yang aktif: %d\n", activeCount);
    printf("akun yang dibekukan: %d\n", frozenCount);

    printf("\nBalance Summary:\n");
    printf("Total Balance: Rp %.2lf\n", totalBalance);

    if (bank->accountCount > 0)
    {
        printf("Average Balance: Rp %.2lf\n", totalBalance / bank->accountCount);
        printf("Highest Balance: Rp %.2lf\n", highestBalance);
        printf("Lowest Balance: Rp %.2lf\n", lowestBalance);
    }

    printf("\nTransaction Summary:\n");
    printf("Total Transactions: %d\n", totalTransactions);

    double totalDeposits = 0, totalWithdrawals = 0, totalTransfers = 0;

    for (int i = 0; i < bank->accountCount; i++)
    {
        Account *acc = &bank->accounts[i];
        for (int j = 0; j < acc->transactionCount; j++)
        {
            Transaction *trans = &acc->transactions[j];
            if (bandingkanString(trans->type, "DEPOSIT") == 0)
                totalDeposits += trans->amount;
            else if (bandingkanString(trans->type, "WITHDRAW") == 0)
                totalWithdrawals += trans->amount;
            else if (bandingkanString(trans->type, "TRANSFER") == 0)
                totalTransfers += trans->amount;
        }
    }

    printf("Total Deposits: Rp %.2lf\n", totalDeposits);
    printf("Total Withdrawals: Rp %.2lf\n", totalWithdrawals);
    printf("Total Transfers: Rp %.2lf\n", totalTransfers);

    printf("\nAudit Log:\n");
    printf("Total Audit Entries: %d\n", bank->auditCount);

    printf("========================================\n");
}

// Admin dashboard
void showAdminDashboard(Bank *bank)
{
    int choice;

    addAuditEntry(bank, "ADMIN", "LOGIN", -1, "Admin login successful");

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("         ADMIN DASHBOARD\n");
        printf("========================================\n");
        printf("1. Lihat Semua Akun\n");
        printf("2. Manage Akun\n");
        printf("3. Lihat Audit Log\n");
        printf("4. Buat laporan\n");
        printf("5. Buat Akun Baru\n");
        printf("0. Keluar\n");
        printf("========================================\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewAllAccounts(bank);
            break;

        case 2:
            manageAccounts(bank);
            break;

        case 3:
            viewAuditLog(bank);
            break;

        case 4:
            generateReport(bank);
            break;

        case 5:
            createAccount(bank);
            if (bank->accountCount > 0)
            {
                Account *newAcc = &bank->accounts[bank->accountCount - 1];
                printf("[ADMIN] Akun baru telah dibuat. ID: %d, Name: %s\n", newAcc->id, newAcc->name);
            }
            break;

        case 0:
            addAuditEntry(bank, "ADMIN", "LOGOUT", -1, "Admin logout");
            printf("Logout berhasil\n");
            break;

        default:
            printf("Pilihan invalid.\n");
        }

    } while (choice != 0);
}
