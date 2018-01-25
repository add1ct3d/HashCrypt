// HashCrypt Secure File Encryption
// Made by Isaac Delly
// https://github.com/Isaacdelly/HashCrypt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt(char*, char*);
void decrypt(char* filename, char* seed);
bool isFile(char* filename);
char* stripDash(char* string);

int main(int argc, char* argv[]) {

    // Exit program if command is incomplete
    if (argc == 2) {
        printf("Command required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }
    if (argc == 3) {
        printf("File name required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }
    if (argc == 4) {
        printf("Seed required\n\n");
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }

    // Check if file exists
    if (!isFile(stripDash(argv[3]))) {
        printf("error locating file: %s\n", stripDash(argv[3]));
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
        printf("Command not recognized: %s\n\n", argv[2]);
        printf("Expected Command: gcc hashcrypt.c -encrypt -file.txt -seed\n\n");
        exit(1); }

    return 0;
}

// Encrypt File
void encrypt(char* filename, char* seed) {
    printf("ENCRYPT:\nFile Name: %s\nSeed: %s\n", filename, seed); }

// Decrypt File
void decrypt(char* filename, char* seed) {
    printf("DECRYPT:\nFile Name: %s\nSeed: %s\n", filename, seed); }

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
