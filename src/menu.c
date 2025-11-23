#include <stdio.h>
#include "../include/menu.h"
#include "../include/account.h"
#include "../include/transaction.h"
#include "../include/storage.h"
#include "../include/utils.h"
#include "../include/operations.h"
#include "../include/admin.h"
#include "../include/audit.h"

// Entry menu - choose between customer and admin
void showEntryMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("        BANK MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Customer Login\n");
    printf("2. Admin Login\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

void showMainMenu(Bank *bank)
{
    printf("\n===== BANK SYSTEM MENU =====\n");
    printf("1. Lihat Info Akun\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Lihat Riwayat Transaksi\n");
    printf("5. Transfer Uang\n");
    printf("6. Ubah Password\n");
    printf("7. Simpan Data\n");
    printf("8. Muat Data\n");
    printf("0. Logout\n");
}

// Login customer berbasis ID dan password
Account *customerLogin(Bank *bank)
{
    int id;
    char password[50];
    Account *acc;

    printf("\n=== CUSTOMER LOGIN ===\n");
    printf("ID akun: ");
    scanf("%d", &id);

    acc = findAccount(bank, id);
    if (!acc)
    {
        printf("Akun tidak ditemukan!\n");
        return NULL;
    }

    if (acc->isFrozen)
    {
        printf("Akun sedang dibekukan, tidak dapat login.\n");
        return NULL;
    }

    printf("Password: ");
    scanf("%s", password);

    if (!validatePassword(acc, password))
    {
        printf("Password salah!\n");
        return NULL;
    }

    printf("Login berhasil. Selamat datang, %s!\n", acc->name);
    return acc;
}

// Menu khusus untuk satu akun customer yang sudah login
void handleCustomerSession(Bank *bank, Account *currentAcc)
{
    int pilih, toId;
    double amount;
    char password[50];

    do
    {
        printf("\nAkun aktif: %s (ID: %d) | Saldo: %.2lf\n",
               currentAcc->name, currentAcc->id, currentAcc->balance);
        showMainMenu(bank);
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            printf("ID: %d | Nama: %s | Saldo: %.2lf\n",
                   currentAcc->id, currentAcc->name, currentAcc->balance);
            break;

        case 2:
            printf("Nominal deposit: ");
            scanf("%lf", &amount);
            deposit(bank, currentAcc->id, amount);
            break;

        case 3:
            printf("Nominal withdraw: ");
            scanf("%lf", &amount);
            withdraw(bank, currentAcc->id, amount);
            break;

        case 4:
            showTransactionHistory(bank, currentAcc->id);
            break;

        case 5:
            printf("ID akun penerima: ");
            scanf("%d", &toId);
            printf("Nominal transfer: ");
            scanf("%lf", &amount);
            transferMoney(bank, currentAcc->id, toId, amount);
            break;

        case 6:
            printf("Masukkan password lama: ");
            scanf("%s", password);
            if (validatePassword(currentAcc, password))
            {
                printf("Masukkan password baru: ");
                scanf("%s", password);
                setAccountPassword(currentAcc, password);
                printf("Password berhasil diubah!\n");
            }
            else
            {
                printf("Password salah!\n");
            }
            break;

        case 7:
            saveAllAccounts(bank);
            break;

        case 8:
            loadAllAccounts(bank);
            break;

        case 0:
            printf("Logout...\n");
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }

        if (pilih != 0)
        {
            pauseScreen();
        }

    } while (pilih != 0);
}

void handleMenu(Bank *bank)
{
    int pilih, id, toId;
    double amount;
    char password[50];
    Account *acc;

    do
    {
        showEntryMenu();
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            acc = customerLogin(bank);
            if (acc)
            {
                handleCustomerSession(bank, acc);
            }
            break;

        case 2:
            // Admin login dan menu
            break;

        case 0:
            printf("Keluar...\n");
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }

        pauseScreen();

    } while (pilih != 0);
}