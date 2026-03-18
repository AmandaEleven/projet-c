#ifndef MASTER_H
#define MASTER_H

#include "sha256.h"
#include "aes.h"
#define MASTER_FILE ".master"
int master_exists(const char *filepath);
void create_master(const char *filepath);
int load_master(const char *filepath, unsigned char *hash);
int verify_master(const char *filepath);
void derive_key(const char *password, unsigned char key[AES_KEY_SIZE]);

#endif
