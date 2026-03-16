#ifndef MASTER_H
#define MASTER_H
#define MASTER_FILE ".master"
#define HASH_SIZE 32

typedef struct {
    unsigned char hash[HASH_SIZE];
} MasterKey;

extern int master_exists(const char *filepath);
extern void create_master(const char *filepath);
extern int load_master(const char *filepath, unsigned char *hash);
extern int verify_master(const char *filepath);

#endif
