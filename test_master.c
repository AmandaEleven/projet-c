#include <stdio.h>
#include <string.h>
#include "master.h"

#define TEST_FILE ".master_test"

int main(void) {
    unsigned char hash[SHA256_HASH_SIZE];
    FILE *fichier = fopen(TEST_FILE, "wb");
    if (fichier == NULL) {
        printf("erreur creation\n");
        return 1;
    }
    sha256_string("motdepasse123", hash);
    fwrite(hash, sizeof(unsigned char), SHA256_HASH_SIZE, fichier);
    fclose(fichier);

    if (master_exists(TEST_FILE)) {
        printf("verif check\n");
    } else {
        printf("pas check\n");
        return 1;
    }

    unsigned char hash_lu[SHA256_HASH_SIZE];
    if (load_master(TEST_FILE, hash_lu) && memcmp(hash, hash_lu, SHA256_HASH_SIZE) == 0) {
        printf("load check\n");
    } else {
        printf("load erreur\n");
        return 1;
    }
    unsigned char key[AES_KEY_SIZE];
    derive_key("motdepasse123", key);
    if (key[0] != 0) {
        printf("sha check\n");
    } else {
        printf("sha erreeur\n");
        return 1;
    }
    unsigned char hash_faux[SHA256_HASH_SIZE];
    sha256_string("mauvaismdp", hash_faux);
    if (memcmp(hash, hash_faux, SHA256_HASH_SIZE) != 0) {
        printf("oui\n");
    } else {
        printf("non\n");
        return 1;
    }
    printf("200 OK\n");
    return 0;
}
