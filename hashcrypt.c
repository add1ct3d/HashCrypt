// HashCrypt Secure File Encryption
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
char *toPointer(volatile char iptr);

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
    printf("ENCRYPT:\nFile Name: %s\nSeed: %s\nHash: %lX\n", filename, seed, toHash(seed)); // DEL
    printf("Hash Size: %d Bytes\n", sizeof(toHash(seed)));                                  // DEL

    // Declare common variables and char[]
    int i; int j;
    unsigned char binary[getFileSize(filename)];
    unsigned char hash[sizeof(toHash(seed))];

    // Convert hashed int into indexable unsigned hash[] of one byte each
    int x = toHash(seed);
    j = sizeof(toHash(seed))-1;
    for (size_t i = 0; i < sizeof(x); ++i) {
        unsigned char byte = *((unsigned char *)&x + i);
        hash[j] = (unsigned)byte;
        j--; }

    printf("Grouped Hash: ");                                                           //DEL
    for(i=0; i<sizeof(toHash(seed)); i++) {                                             //DEL
        printf("%0X ", hash[i]);                                                        //DEL
    }                                                                                   //DEL

    // Collect file contents into binary[]
    FILE *file = fopen(filename, "rb");
    fread(binary, sizeof(char), getFileSize(filename), file);

    printf("\nFile Contents: ");                                                         // DEL
    for (i=0; i<getFileSize(filename); i++ ) {                                           // DEL
        printf("%0X ", binary[i]); }                                                     // DEL

    // TODO Overflow


    printf("\n\n"); // DEL
    }

// Decrypt File
void decrypt (char* filename, char* seed) {
    printf("DECRYPT:\nFile Name: %s\nSeed: %s\n", filename, seed); }

// Hash seed using ?? hashing algorithm
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

long getFileSize(char* filename) {
    long size;
    FILE* file;
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    return size;
}
