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

    loadAllAccounts(&bank);
    loadAuditLog(&bank);

    clearScreen();

    int choice;
    do
    {
        showEntryMenu();
        printf("pilih: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // mode customer dengan login ID + password
            Account *loggedIn = customerLogin(&bank);
            if (loggedIn)
            {
                handleCustomerSession(&bank, loggedIn);
            }
        }
        else if (choice == 2)
        {
            // mode admin
            char key[50], password[50];

            printf("\nmasukkan master key: ");
            scanf("%s", key);
            printf("Masukkan password: ");
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

    saveAllAccounts(&bank);
    saveAuditLog(&bank);

    printf("Terima kasih sudah menggunakan jasa bank kami...\n");
    return 0;
}