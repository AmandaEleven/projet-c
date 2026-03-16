#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

    // hash du mdp en attendant gaeatan
    unsigned char hash[32];
    sha256(password, hash);  // sera fourni par Personne A

    // ecrire hash dans le fichier 
    FILE *fichier;
    if ((fichier = fopen(filepath, "wb")) == NULL) {
        fprintf(stderr, "Erreur : impossible de créer le fichier master\n");
        return;
    }

    if (fwrite(hash, sizeof(char), 32, fichier) != 32) {
        fprintf(stderr, "Erreur : écriture du hash échouée\n");
    }

    fclose(fichier);
    printf("Mot de passe maitre créé avec succès.\n");
}

int load_master(const char *filepath, unsigned char *hash) {
    FILE *fichier;

    if ((fichier = fopen(filepath, "rb")) == NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s", filepath);
        return 0;
    }

    if (fread(hash, sizeof(unsigned char), 32, fichier) != 32) {
        fprintf(stderr, "Erreur de lecture du hash\n");
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}

int verify_master(const char *filepath) {
    char password[128];
    unsigned char hash_saisi[32];
    unsigned char hash_stocke[32];
    printf("Entrez votre mot de passe: ");
    scanf("%s", password);

    // hasher le mot de passe saisi quand pA
    sha256(password, hash_saisi);

    if (load_master(filepath, hash_stocke) == 0) {
        fprintf(stderr, "Erreur\n");
        return 0;
    }

    if (memcmp(hash_saisi, hash_stocke, 32) == 0) {  //memcmp = strcmp pour le binaire
        printf("Mdp correct accès autoisé\n");
        return 1;
    }

    printf("Mot de passe incorrect\n");
    return 0;
}

