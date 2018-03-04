# HashCrypt

Secure file encryption and decryption through salted passphrase hashing

#

# Installation

```
$ git clone https://github.com/Isaacdelly/HashCrypt
```

#

# Usage

<h2>Self-Compilation:</h2>

Compile and execute the C code yourself

__Requires a C Compiler or IDE__

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

<h2>Excecutable</h2>

Execute the pre-compiled `hashcrypt.exe` file

Encryption: 

```
$ cd HashCrypt

$ hashcrypt.exe -encrypt -file -seed
```

Decryption: 

```
$ cd HashCrypt

$ hashcrypt.exe -decrypt -file -seed
```

#

# Arguments

This project requires execution-time arguments to operate.

Type `$ a -?` for help.

```
a.exe -commmand -file -seed

-command     'encrypt' or 'decrypt' depending on choice
-file        Desired file to be encrypted or decrypted
-seed        Secret passphrase that will be used to encrypt the file's data
```

#

# How It Works



