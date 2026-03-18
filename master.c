#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "master.h"
#include "sha256.h"

int master_exists(const char *filepath) {
    FILE * fichier;
    if((fichier=fopen(filepath, "r")) == NULL){
        return 0;
    }
    fclose(fichier);
    return 1;
}

void create_master(const char *filepath) {
    char password[128];
    printf("Entrez un mot de passe maitre : ");
    scanf("%s", password);
    unsigned char hash[SHA256_HASH_SIZE];
    sha256_string(password, hash);  // fourni par Personne A

    FILE *fichier;
    if ((fichier = fopen(filepath, "wb")) == NULL) {
        fprintf(stderr, "Erreur de creation\n");
        return;
    }

    if (fwrite(hash, sizeof(char), SHA256_HASH_SIZE, fichier) != SHA256_HASH_SIZE) {
        fprintf(stderr, "Erreur ecriture du hash\n");
    }

    fclose(fichier);
    printf("Mdp reussi\n");
}

int load_master(const char *filepath, unsigned char *hash) {
    FILE *fichier;
    if ((fichier = fopen(filepath, "rb"))== NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s", filepath);
        return 0;
    }
    if (fread(hash, sizeof(unsigned char), SHA256_HASH_SIZE, fichier) != SHA256_HASH_SIZE) {
        fprintf(stderr,"Erreur de lecture du hash\n");
        fclose(fichier);
        return 0;
    }
    fclose(fichier);
    return 1;
}

int verify_master(const char *filepath) {
    char password[128];
    unsigned char hash_saisi[SHA256_HASH_SIZE];
    unsigned char hash_stocke[SHA256_HASH_SIZE];
    printf("Entrez votre mot de passe: ");
    scanf("%s", password);

    // hasher le mot de passe saisi
    sha256_string(password, hash_saisi);  // fourni par Personne A
    if (load_master(filepath, hash_stocke) == 0) {
        fprintf(stderr, "Erreur\n");
        return 0;
    }
    if (memcmp(hash_saisi, hash_stocke, SHA256_HASH_SIZE) == 0) {  //memcmp = strcmp pour le binaire
        printf("Mdp correct accès autoisé\n");
        return 1;
    }
    printf("Mot de passe incorrect\n");
    return 0;
}
