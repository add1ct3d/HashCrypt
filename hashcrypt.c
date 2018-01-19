#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include <inttypes.h>

void encrypt(char*, char*);
void decrypt(char* filename, char* seed);
bool isFile(char* filename);
char* stripDash(char* string);
uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len);
int hash(const char *s);

int main(int argc, char* argv[]) {

    // Exit program if command is incomplete
    if (argc == 1) {
        printf("Command required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }
    if (argc == 2) {
        printf("File name required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }
    if (argc == 3) {
        printf("Seed required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }

    // Call encrypt or decrypt depending command
    if (argc > 4) {
        if (!isFile(stripDash(argv[3]))) {
            printf("error locating file: %s\n", stripDash(argv[3]));
            exit(1); }

        char* seed = stripDash(argv[4]);
        if (argc > 5) {
            int i;
            for (i=5; i < argc; i++) {
                strcat(seed, " ");
                strcat(seed, stripDash(argv[i]));
            }
        }

        if (strcmp(stripDash(argv[2]), "encrypt") == 0) {
            encrypt(stripDash(argv[3]), seed); }
        else if (strcmp(stripDash(argv[2]), "decrypt") == 0) {
            decrypt(stripDash(argv[3]), seed); }
        else {
            printf("Command not recognized: %s\n\n", argv[2]);
            printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
            exit(1); }
    }
    return 0;
}

void encrypt(char* filename, char* seed) {
    printf("ENCRYPT:\nFile Name: %s\nSeed: %s\nHash: %X\n", filename, seed, hash(seed)); }

void decrypt(char* filename, char* seed) {
    printf("DECRYPT:\nFile Name: %s\nSeed: %s\nHash: %X\n", filename, seed, hash(seed)); }

// Checks if file exists
bool isFile(char* filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        fclose(file);
        return false; }
    else {
        fclose(file);
        return true; }
}

// Strip first char '-' from string
char* stripDash(char* string) {
    if (string[0] == '-') {
        return strchr(string, string[1]); }
    else {
        return string; }
}

// CRC-32 Hashing Algorithm
uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len) {
	static uint32_t table[256];
	static int have_table = 0;
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const char *p, *q;

	/* Not thread safe - no mutex */
	if (have_table == 0) {
		/* Generate CRC table */
		for (i = 0; i < 256; i++) {
			rem = i;
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320; }
				else
					rem >>= 1; }
			table[i] = rem; }
		have_table = 1; }

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet]; }
	return ~crc;
}

// Returns hash value of string
int hash(const char *s) {
	return rc_crc32(0, s, strlen(s));
}
