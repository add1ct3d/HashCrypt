// HashCrypt Secure File Encryption and Decryption
// Made by Isaac Delly
// https://github.com/Isaacdelly/HashCrypt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt (char*, char*);
void decrypt (char* filename, char* seed);
unsigned long toHash (char* seed);
bool isFile (char* filename);
char* stripDash (char* string);
long getFileSize(char* filename);

int main (int argc, char* argv[]) {

    // Exit program if command is incomplete
    if (argc < 5) {
        printf("ERROR: Unable To Process Command\nExpected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n");
        exit(1); }

    // Check if file exists
    if (!isFile(stripDash(argv[3]))) {
        printf("ERROR: Error Locating File %s\n", stripDash(argv[3]));
        exit(1); }

    // Combine seed args to one string
    char* seed = stripDash(argv[4]);
    if (argc > 5) {
        int i;
        for (i=5; i < argc; i++) {
            strcat(seed, " ");
            strcat(seed, stripDash(argv[i]));
        }
    }

    // Call encrypt or decrypt
    if (strcmp(stripDash(argv[2]), "encrypt") == 0) {
        encrypt(stripDash(argv[3]), seed); }
    else if (strcmp(stripDash(argv[2]), "decrypt") == 0) {
        decrypt(stripDash(argv[3]), seed); }
    else {
        printf("ERROR: Unable To Process Command\nExpected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n");
        exit(1); }

    return 0;
}

// Encrypt File
void encrypt (char* filename, char* seed) {

    // Declare common variables and unsigned char[]
    int i; int j;
    unsigned char binary[getFileSize(filename)];
    unsigned char hash[sizeof(toHash(seed))];
    unsigned char encrypted[sizeof(toHash(seed)) * getFileSize(filename)];

    // Convert hashed seed into indexable unsigned hash[]
    int x = toHash(seed);
    j = sizeof(toHash(seed))-1;
    for (size_t i = 0; i < sizeof(x); ++i) {
        unsigned char byte = *((unsigned char *)&x + i);
        hash[j] = (unsigned)byte;
        j--; }

    // Collect target file contents into binary[]
    FILE *file = fopen(filename, "rb");
    fread(binary, sizeof(char), getFileSize(filename), file);

    // Overflow binary[] + hash[] = encrypted[] to created an unidentifiable value
    i=0; j=0;
    while (i<getFileSize(filename)) {
        encrypted[i] = binary[j] + hash[j];
        i++; j++;
        if (j > sizeof(toHash(seed))) {
            j = 0; }
    }

    // Write encrypted data to file
    FILE* encrypted_data;
    encrypted_data = fopen(filename,"wb");
    fwrite(encrypted, sizeof(binary), 1, encrypted_data);
}

// Decrypt File
void decrypt (char* filename, char* seed) {

    // Declare common variables and unsigned char[]
    int i; int j;
    unsigned char binary[getFileSize(filename)];
    unsigned char hash[sizeof(toHash(seed))];
    unsigned char decrypted[sizeof(toHash(seed)) * getFileSize(filename)];

    // Convert hashed seed into indexable unsigned hash[]
    int x = toHash(seed);
    j = sizeof(toHash(seed))-1;
    for (size_t i = 0; i < sizeof(x); ++i) {
        unsigned char byte = *((unsigned char *)&x + i);
        hash[j] = (unsigned)byte;
        j--; }

    // Collect target file contents into binary[]
    FILE *file = fopen(filename, "rb");
    fread(binary, sizeof(char), getFileSize(filename), file);

    // Underflow binary[] - hash[] = decrypted[] to revert back to original value
    i=0; j=0;
    while (i<getFileSize(filename)) {
        decrypted[i] = binary[j] - hash[j];
        i++; j++;
        if (j > sizeof(toHash(seed))) {
            j = 0; }
    }

    // Write decrypted data to file
    FILE* decrypted_data;
    decrypted_data = fopen(filename,"wb");
    fwrite(decrypted, sizeof(binary), 1, decrypted_data);
}

// Hash seed using CRC-32 hashing algorithm
unsigned long toHash (char* seed) {
     return CRC32(seed);
}

// Checks if file exists
bool isFile (char* filename) {
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
char* stripDash (char* string) {
    if (string[0] == '-') {
        return strchr(string, string[1]); }
    else {
        return string; }
}

// Return number of bytes in a file
long getFileSize(char* filename) {
    long size;
    FILE* file;
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    return size;
}
