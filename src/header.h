#ifndef header
#define header
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt (char*, char*);
void decrypt (char* filename, char* seed);
bool isFile (char* filename);
char* stripDash (char* string);
long getFileSize (char* filename);
unsigned int toHash(const char* buf);
