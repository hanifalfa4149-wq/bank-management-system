#include <stdio.h>
#include "bank.h"
#include "menu.h"
#include "utils.h"

int main()
{
    Bank bank;
    initBank(&bank);

    clearScreen();
    printf("=== BANK MANAGEMENT SYSTEM ===\n");

    handleMenu(&bank);

    return 0;
}