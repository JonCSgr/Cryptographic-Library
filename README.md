# Cryptographic-Library
This repository contains a cryptographic library that includes five different cryptographic ciphers. With this library, you can easily encrypt and decrypt messages using various ciphers.

## Usage
1. Write your plaintext in the `test.txt` file.
2. Write your key for the Playfair cipher in the `key.txt` file.
3. In the terminal, run the command `make run` and then execute the program using `./run.out`.
4. Follow the instructions in the terminal to encrypt or decrypt your message.

If you want to clean the files, use the command `make clean`.

## Example
1. Choose option 1 in the terminal for the first encryption algorithm.
2. Choose N=500.
3. The encryption is successful and there is an output file called `encryptedtext.txt` with the encrypted message.

To decrypt the message, follow the same process in reverse:
1. Run `./run.out`.
2. Choose option 2, which is the decrypt option for the first cipher.
3. Choose N=500 again since that's how you encrypted it in step 1.
4. There is now a file called `decryptedtxt.txt` with your decrypted message.

There are more encryption methods available - just follow the instructions in the terminal.
