// HashCrypt Secure File Encryption and Decryption
// Made by Isaac Delly
// https://github.com/isaacdelly/HashCrypt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt (char*, char*);
void decrypt (char* filename, char* seed);
unsigned long toHash (char* seed);
bool isFile (char* filename);
char* stripDash (char* string);
long getFileSize (char* filename);

int main (int argc, char* argv[]) {

    if (argc == 2) {
        if (strcmp(stripDash(argv[1]), "?") == 0) {
            printf("\nExample Usage: a.exe -commmand -file -seed\n\n");
            printf("-command     'encrypt' or 'decrypt' depending on desired outcome\n");
            printf("-file        file path to be encrypted or decrypted\n");
            printf("-seed        secret passphrase that will be used to encrypt the file's data\n");
            exit(0); }
    }

    // Exit program if command is incomplete
    if (argc < 4) {
        printf("\nERROR: Unable To Process Command\nExpected Command: a.exe -command -file -seed\n");
        exit(-1); }

    // Check if file exists
    if (!isFile(stripDash(argv[2]))) {
        printf("ERROR: Error Locating File %s\n", stripDash(argv[2]));
        exit(-1); }

    // Combine seed args to one string
    char* seed = stripDash(argv[3]);
    if (argc > 4) {
        int i;
        for (i=4; i < argc; i++) {
            strcat(seed, " ");
            strcat(seed, stripDash(argv[i]));
        }
    }

    // Call encrypt or decrypt
    if (strcmp(stripDash(argv[1]), "encrypt") == 0) {
        encrypt(stripDash(argv[2]), seed); }
    else if (strcmp(stripDash(argv[1]), "decrypt") == 0) {
        decrypt(stripDash(argv[2]), seed); }
    else {
        printf("ERROR: Unable To Process Command\nExpected Command: a.exe -command -file.txt -seed\n");
        exit(-1); }

    return 0;
}

// Encrypt File
void encrypt (char* filename, char* seed) {

    // Declare common variables and unsigned char[]
    int i; int j; int k; int x;
    unsigned char binary[getFileSize(filename)];
    unsigned char hash[sizeof(toHash(seed))];
    unsigned char encrypted[sizeof(toHash(seed)) * getFileSize(filename)];

    // Convert hashed seed into unsigned char hash[]
    printf("\nHashing seed...");
    x = toHash(seed);
    j = sizeof(toHash(seed))-1;
    for (size_t i = 0; i < sizeof(x); ++i) {
        unsigned char byte = *((unsigned char *)&x + i);
        hash[j] = (unsigned)byte;
        j--; }

    // Collect target file contents into unsigned char binary[]
    printf("\nCollecting file contents...\n");
    FILE *file = fopen(filename, "rb");
    fread(binary, sizeof(char), getFileSize(filename), file);

    // Overflow binary[] + hash[] = encrypted[] to create an unidentifiable hex value
    j=0;
    for (i=0; i<getFileSize(filename); i++) {
        encrypted[i] = binary[i] + hash[j];
         int pre = snprintf(NULL, 0, "%d", i+1);
         int size = snprintf(NULL, 0, "%ld", getFileSize(filename));
         for (k=0; k<= pre+size+27; k++) {
             printf("\b"); }
         printf("Encrypting byte %d out of %ld...", i+1, getFileSize(filename));
        j++;
        if (j >= sizeof(toHash(seed))) {
            j = 0; }
    }

    // Write encrypted data to file
    FILE* encrypted_data;
    encrypted_data = fopen(filename,"wb");
    fwrite(encrypted, sizeof(binary), 1, encrypted_data);
    printf("\n%s encrypted successfully\n", filename);

    return 1;
}

// Decrypt File
void decrypt (char* filename, char* seed) {

    // Declare common variables and unsigned char[]
    int i; int j; int k; int x;
    unsigned char binary[getFileSize(filename)];
    unsigned char hash[sizeof(toHash(seed))];
    unsigned char decrypted[sizeof(toHash(seed)) * getFileSize(filename)];

    // Convert hashed seed into unsigned char hash[]
    printf("\nHashing seed...");
    x = toHash(seed);
    j = sizeof(toHash(seed))-1;
    for (size_t i = 0; i < sizeof(x); ++i) {
        unsigned char byte = *((unsigned char *)&x + i);
        hash[j] = (unsigned)byte;
        j--; }

    // Collect target file contents into unsigned char binary[]
    printf("\nCollecting file contents...\n");
    FILE *file = fopen(filename, "rb");
    fread(binary, sizeof(char), getFileSize(filename), file);

    // Underflow binary[] - hash[] = decrypted[] to revert back to original hex value
    j=0;
    for (i=0; i<getFileSize(filename); i++) {
        decrypted[i] = binary[i] - hash[j];
        int pre = snprintf(NULL, 0, "%d", i+1);
        int size = snprintf(NULL, 0, "%ld", getFileSize(filename));
        for (k=0; k<= pre+size+27; k++) {
            printf("\b"); }
        printf("Decrypting byte %d out of %ld...", i+1, getFileSize(filename));
        j++;
        if (j >= sizeof(toHash(seed))) {
            j = 0; }
    }

    // Write decrypted data to file
    FILE* decrypted_data;
    decrypted_data = fopen(filename,"wb");
    fwrite(decrypted, sizeof(binary), 1, decrypted_data);
    printf("\n%s decrypted successfully\n", filename);

    return 1;
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

// Returns number of bytes in a file
long getFileSize (char* filename) {
    long size;
    FILE* file;
    file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    return size;
}
