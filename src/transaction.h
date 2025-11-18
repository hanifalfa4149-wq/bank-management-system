#ifndef TRANSACTION_H
#define TRANSACTION_H

#define MAX_NOTE 60
#define MAX_DATE 20

typedef struct
{
    char type[20];
    double amount;
    char date[MAX_DATE];
    char note[MAX_NOTE];
} Transaction;

#endif