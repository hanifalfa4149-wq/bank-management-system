#include <stdio.h>
#include "../include/bank.h"
#include "../include/menu.h"
#include "../include/utils.h"
#include "../include/admin.h"
#include "../include/audit.h"
#include "../include/storage.h"

int main()
{
    Bank bank;
    initBank(&bank);

    // Load existing data
    loadAllAccounts(&bank);
    loadAuditLog(&bank);

    clearScreen();

    int choice;
    do
    {
        showEntryMenu();
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // Customer mode
            handleMenu(&bank);
        }
        else if (choice == 2)
        {
            // Admin mode
            char key[50], password[50];

            printf("\nEnter Master Key: ");
            scanf("%s", key);
            printf("Enter Password: ");
            scanf("%s", password);

            if (adminLogin(key, password))
            {
                printf("✓ Admin login successful!\n");
                showAdminDashboard(&bank);
            }
            else
            {
                printf("✗ Invalid admin credentials!\n");
                addAuditEntry(&bank, "UNKNOWN", "LOGIN_FAILED", -1,
                              "Invalid admin credentials");
            }
        }

    } while (choice != 0);

    // Save data before exit
    saveAllAccounts(&bank);
    saveAuditLog(&bank);

    printf("Goodbye!\n");
    return 0;
}