#ifndef UTILS_H
#define UTILS_H

// Custom string functions
int hitungstring(char *str);
void salinString(char *dest, const char *src);
int bandingkanString(const char *s1, const char *s2);
void gabungkanString(char *dest, const char *src);
void buildTransferNote(char *note, const char *prefix, const char *name);

// Input functions
void getStringInput(char *buffer, int maxLength);
int getIntInput();
double getDoubleInput();
void clearInputBuffer();

// Utility functions
void clearScreen();
void pauseScreen();
void bersihkanString(char *str);

#endif