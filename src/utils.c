#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utils.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    getchar();
}

void trimTrailingNewline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}