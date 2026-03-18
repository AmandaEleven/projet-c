#include <stdio.h>
#include <string.h>
#include "aes.h"

int main(void) {
    unsigned char key[16] = {
        0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
        0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
    };
    unsigned char iv[16] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
    };

    unsigned char original[64] = "voila ce qu'il faut aes cbc";
    unsigned char chiffre[64];
    unsigned char dechiffre[64];
    int taille;

    taille = ajt_zero(original, 32);
    encrypt_cbc(original, taille, key, iv, chiffre);
    decrypt_cbc(chiffre, taille, key, iv, dechiffre);
    taille = enlv_zero(dechiffre, taille);

    if (memcmp(original, dechiffre, taille) == 0) {
        printf("aescbc ok\n");
        return 0;
    }

    printf("erreur\n");
    return 1;
}
