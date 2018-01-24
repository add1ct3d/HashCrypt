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
char* reverse(char *str);
unsigned long hash(const char *s);
unsigned long CRC32(const char *s);
long getFileSize(char* filename);
int getDigitSize(long long number);

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
    printf("ENCRYPT:\nFile Name: %s\nSeed: %s\nHash: %ld\nReverse: %s\nReverse Hash: %ld\n\n",
            filename, seed, hash(seed), reverse(seed), hash(reverse(seed)));

    int i;
    unsigned char* buffer = malloc(getFileSize(filename) * sizeof (*buffer));
    FILE* file = fopen(filename, "rb");
    fread(buffer, getFileSize(filename), 1, file); //buffer[i]
    fclose(file);
    printf("Hex Value: ");
    for(i=0;i<getFileSize(filename);i++){
        printf("%X ", buffer[i]);
    }
}

void decrypt(char* filename, char* seed) {
    printf("DECRYPT:\nFile Name: %s\nSeed: %s\nHash: %ld\n", filename, seed, hash(seed)); }

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

// Reverse string
char* reverse(char *str) {
    int len = strlen(str);
    char *p1 = str;
    char *p2 = str + len - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1++ = *p2;
        *p2-- = tmp;
    }
    return str;
}

// Generate Hashing key
unsigned long hash(const char *string) {
    return CRC32(string);
}

// CRC-32 Hashing Algorithm
unsigned long CRC32(const char *buf) {
    int len = strlen(buf);
    unsigned long crc = 0;
	static unsigned int table[256];
	static int have_table = 0;
	unsigned int rem;
	unsigned short octet;
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

// Returns the number of bytes in a file
long getFileSize(char* filename) {
    long size;
    FILE* file;
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    return size; }

int getDigitSize(long long number) {
    int count = 0;
    while(number != 0) {
        number /= 10;
        ++count; }
    return count;
}
