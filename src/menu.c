#include <stdio.h>
#include "menu.h"
#include "account.h"
#include "transaction.h"
#include "storage.h"
#include "utils.h"
#include "operations.h"

void showMainMenu(Bank *bank)
{
    printf("\n===== BANK SYSTEM MENU =====\n");
    printf("1. Buat Akun Baru\n");
    printf("2. Lihat Semua Akun\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Lihat Riwayat Transaksi\n");
    printf("6. Transfer Uang\n");
    printf("7. Ubah Password\n");
    printf("8. Simpan Data\n");
    printf("9. Muat Data\n");
    printf("0. Keluar\n");
}

void handleMenu(Bank *bank)
{
    int pilih, id, toId;
    double amount;
    char password[50];
    Account *acc;

    do
    {
        showMainMenu(bank);
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            createAccount(bank);
            break;

        case 2:
            showAllAccounts(bank);
            break;

        case 3:
            printf("ID akun: ");
            scanf("%d", &id);
            printf("Nominal: ");
            scanf("%lf", &amount);
            deposit(bank, id, amount);
            break;

        case 4:
            printf("ID akun: ");
            scanf("%d", &id);
            printf("Nominal: ");
            scanf("%lf", &amount);
            withdraw(bank, id, amount);
            break;

        case 5:
            printf("ID akun: ");
            scanf("%d", &id);
            showTransactionHistory(bank, id);
            break;

        case 6:
            printf("ID akun pengirim: ");
            scanf("%d", &id);
            printf("ID akun penerima: ");
            scanf("%d", &toId);
            printf("Nominal: ");
            scanf("%lf", &amount);
            transferMoney(bank, id, toId, amount);
            break;

        case 7:
            printf("ID akun: ");
            scanf("%d", &id);
            acc = findAccount(bank, id);
            if (!acc)
            {
                printf("Akun tidak ditemukan!\n");
            }
            else
            {
                printf("Masukkan password lama: ");
                scanf("%s", password);
                if (validatePassword(acc, password))
                {
                    printf("Masukkan password baru: ");
                    scanf("%s", password);
                    setAccountPassword(acc, password);
                    printf("Password berhasil diubah!\n");
                }
                else
                {
                    printf("Password salah!\n");
                }
            }
            break;

        case 8:
            saveAllAccounts(bank);
            break;

        case 9:
            loadAllAccounts(bank);
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