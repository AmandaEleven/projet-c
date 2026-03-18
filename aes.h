#ifndef AES_H
#define AES_H
#define AES_BLOCK_SIZE 16
#define AES_KEY_SIZE 16
#define AES_IV_SIZE 16

void aes_cbc_encrypt(unsigned char *data, int data_len,
                     const unsigned char *key,
                     const unsigned char *iv,
                     unsigned char *output);

void aes_cbc_decrypt(unsigned char *data, int data_len,
                     const unsigned char *key,
                     const unsigned char *iv,
                     unsigned char *output);

#endif
