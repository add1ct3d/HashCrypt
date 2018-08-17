#ifndef header
#define header
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

void encrypt (char*, char*);
void decrypt (char* filename, char* seed);
unsigned long toHash (char* seed);
bool isFile (char* filename);
char* stripDash (char* string);
long getFileSize (char* filename);
int CRC32(const char *s);
uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len);
