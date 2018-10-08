#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt (char* filename, char* seed);
void decrypt (char* filename, char* seed);
bool isFile (char* filename);
char* stripDash (char* string);
long getFileSize (char* filename);
unsigned int toHash(const char* buf);

#endif
