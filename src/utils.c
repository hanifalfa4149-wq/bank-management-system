#include <stdio.h>
#include "../include/utils.h"

// fungsi strlen
int hitungstring(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

// fungsi strcpy
void salinString(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// fungsi strcmp
int bandingkanString(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            return (int)(s1[i] - s2[i]);
        }
        i++;
    }

    return (int)(s1[i] - s2[i]);
}

// funsgsi strcat
void gabungkanString(char *dest, const char *src)
{
    int destLen = hitungstring(dest);
    int i = 0;
    while (src[i] != '\0')
    {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
}

// Helper untuk pattern "Transfer ke %s" pattern
void buildTransferNote(char *note, const char *prefix, const char *name)
{
    int i = 0;
    while (prefix[i] != '\0')
    {
        note[i] = prefix[i];
        i++;
    }
    int j = 0;
    while (name[j] != '\0')
    {
        note[i] = name[j];
        i++;
        j++;
    }
    note[i] = '\0';
}

// trimTrailingNewline
void bersihkanString(char *str)
{
    int len = hitungstring(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void clearScreen()
{
    // Simple clear without system() call
    for (int i = 0; i < 100; i++)
    {
        printf("\n");
    }
}

void pauseScreen()
{
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    getchar();
}