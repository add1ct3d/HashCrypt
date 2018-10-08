# HashCrypt

Secure file encryption and decryption through salted passphrase hashing

#

# Installation

```
git clone https://github.com/Isaacdelly/HashCrypt.git hashcrypt
```

#

# Complilation

If you have the GCC C/C++ compiler:

```
cd hashcrypt/src

gcc -I./ -o hashcrypt hashcrypt.c hash.c
``` 

<b>hashcrypt.exe</b> is generated in hashcrypt/src and is used to interact with the program


#

# Usage

Encryption: 

```
hashcrypt -encrypt -file -seed
```

Decryption: 

```
hashcrypt -decrypt -file -seed
```

#

# Arguments

This project requires execution-time arguments to operate.

Type `-?` for help.

```
hashcrypt -commmand -file -seed

-command     'encrypt' or 'decrypt' depending on desired outcome
-file        file path to be encrypted or decrypted
-seed        secret passphrase that will be used to encrypt or decrypt the file's data
```

#

# How It Works

This program works by treating the binary data of the target file as an unsigned char array, where each index of the array holds one byte of the target file's code. It then hashes the given seed into a hexidecimal string using the CRC-32 hashing algorithm.

Using both the file's hex values, and the hashed hex values, the program combines them together to add, or in many cases overflow, into an arbitrary byte value. The new encrypted data is unrecognizable and has no correlation to the orginal data because each byte is added by a unique portion of the 8 character CRC-32 hash. Similarly, decrypting the file includes subtracting, or underflowing, the encrypted file's binary data by the hashed values, returning the obfuscated code to its original value.

The only weakness in this system is a common passphrase, which may be possible to brute force using a password cracking tool. However, if a unique passphrase is used, it should be impossible to brute force because of CRC-32's 32 bit hash length.

#
