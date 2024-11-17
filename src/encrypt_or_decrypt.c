/*
 * File name     : encrypt_or_decrypt.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program to encrypt or decrypt a file with openssl.
 */


#include "../main.h"

// value is used to know whether to encrypt (1) or decrypt (0) the file
void encrypt_or_decrypt(const char *inputFilepath, const char *outputFilepath, const char *password, const size_t value) {
    // key = encryption/decryption key and iv = initialization vector
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, key, iv);
    
    FILE *infile = fopen(inputFilepath, "rb");
    FILE *outfile = fopen(outputFilepath, "wb"); 
    
    if (!infile || !outfile) {
        perror("File open error");
        return;
    }

    // initialization of the encryption/decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (value == 1) {
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    } else {
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    }
    
    // file encrypted/decrypted in blocks of 1024 bytes (buffer size)
    unsigned char buffer[1024];
    unsigned char text[1024 + EVP_MAX_BLOCK_LENGTH];
    int32_t len;

    // output data is stored in text and then written to the output file
    while (1) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), infile);
        if (bytesRead <= 0) break;

        if (value == 1) {
            EVP_EncryptUpdate(ctx, text, &len, buffer, bytesRead);
        } else {
            EVP_DecryptUpdate(ctx, text, &len, buffer, bytesRead);
        }
        fwrite(text, 1, len, outfile);
    }

    // manages AES padding
    if (value == 1) {
        EVP_EncryptFinal_ex(ctx, text, &len);
    } else {
        EVP_DecryptFinal_ex(ctx, text, &len);
    }
    fwrite(text, 1, len, outfile);
    
    EVP_CIPHER_CTX_free(ctx);
    fclose(infile);
    fclose(outfile);
}
