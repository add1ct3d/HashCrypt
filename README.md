# HashCrypt

Secure file encryption and decryption through salted passphrase hashing

#

# Installation

```
$ git clone https://github.com/Isaacdelly/HashCrypt
```

#

# Usage

Encryption: 

```
$ cd HashCrypt

$ gcc hashcrypt.c

$ a.exe -encrypt -file -seed
```

Decryption: 

```
$ cd HashCrypt

$ gcc hashcrypt.c

$ a.exe -decrypt -file -seed
```

#

# Arguments

This project requires execution-time arguments to operate.

Type `$ -?` for help.

```
a.exe -commmand -file -seed

-command     'encrypt' or 'decrypt' depending on choice
-file        Desired file to be encrypted or decrypted
-seed        Secret passphrase that will be used to encrypt the file's data
```

#

# How It Works

This program works by treating the binary data of the target file as an unsigned char array, where each index of the array holds one byte of the target file's code. It then hashes the given seed into a random hexidecimal using a hashing algorithm.

Using both the file's hex values, and the hashed hex values, the program combines them together to add, or in many cases overflow, into an arbitrary byte value. The new encrypted data is unrecognizable and has no correlation to the orginal data because each byte is added by unique portion of the 32 character hexidecimal hash value.


Contents of Text File: | "hello" | Hex Value of File Contents: |__68 65 6C 6C 6F__ 
------------|------------|------------|------------
__Seed String:__ | __"apple"__ | __Hashed Seed:__ |__A9 2E D0 50 A9 ...>__
X | X | __Encypted Data:__ |__11 93 3C BC 18__


The only weakness in this system is a common passphrase, which may be possible to brute force using a password cracking tool. However, if a strong, unique passphrase is used, it is impossible to crack.

#
