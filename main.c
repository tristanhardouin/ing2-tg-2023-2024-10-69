#include <stdio.h>
#include <stdlib.h>

// Définition de la structure operation
struct operation {
    int duree;
    struct operation *suivant; // Ajout d'un pointeur vers la prochaine opération
};

// Définition de la structure temps_cycle utilisé plus tard pour la fonction de calcul 
struct temps_cycle {
    int duree;
};

// Fonction pour lire le temps de cycle de la ligne de production
struct temps_cycle lire_temps_cycle() {
    // Ouvrir le fichier en lecture
    FILE *fp = fopen("temps_cycle.txt", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        exit(EXIT_FAILURE);
    }

    // Lire la première ligne du fichier
    char ligne[10];
    fgets(ligne, sizeof(ligne), fp);

    // Fermer le fichier
    fclose(fp);

    // Convertir la chaîne de caractères en un entier
    int duree = atoi(ligne);
    printf("Le temps de cycle est de : %d\n",duree);
    // Créer la structure temps_cycle
    struct temps_cycle temps_cycle = {.duree = duree};

    return temps_cycle;
}

// Fonction pour lire la liste des opérations
struct operation *lire_operations() {
    // Ouvrir le fichier en lecture
    FILE *fp = fopen("operations.txt", "r");

    // Vérifier si le fichier est ouvert 
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier operations.txt");
        exit(EXIT_FAILURE);
    }

    // Initialiser la liste des opérations
    struct operation *operations = NULL;

    // Lire les lignes du fichier
    while (!feof(fp)) {
        // Allouer de l'espace pour une nouvelle opération
        struct operation *nouvelle_operation = malloc(sizeof(struct operation));

        // Vérifier si l'allocation a réussi
        if (nouvelle_operation == NULL) {
            perror("Erreur lors de l'allocation mémoire");
            exit(EXIT_FAILURE);
        }

        // Lire la durée de l'opération
        fscanf(fp, "%d", &nouvelle_operation->duree);
        nouvelle_operation->suivant = NULL; // Initialiser le pointeur suivant

        printf("%d\n",nouvelle_operation->duree);
        // Ajouter la nouvelle opération à la liste
        if (operations == NULL) {
            operations = nouvelle_operation; // Première opération dans la liste
        } else {
            struct operation *temp = operations;
            while (temp->suivant != NULL) {
                temp = temp->suivant;
            }
            temp->suivant = nouvelle_operation; // Ajouter à la fin de la liste
        }
    }

    // Fermer le fichier
    fclose(fp);

    return operations;
}


int main() {
    // Lire le temps de cycle
    struct temps_cycle temps_cycle = lire_temps_cycle();
    printf("les operations sont :\n");
    // Lire la liste des opérations
    struct operation *operations = lire_operations();

    // Vérifier si la durée totale des opérations ne dépasse pas le temps de cycle
    int duree_totale = 0;
    struct operation *operation = operations;
    while (operation != NULL) {
        duree_totale += operation->duree;
        operation = operation->suivant;
    }
    if (duree_totale > temps_cycle.duree) {
        printf("La duree totale des operations depasse le temps de cycle\n");
    } else {
        printf("La duree totale des operations ne depasse pas le temps de cycle\n");
    }

    // Libérer la mémoire allouée pour la liste des opérations
    while (operations != NULL) {
        struct operation *operation_a_liberer = operations;
        operations = operations->suivant;
        free(operation_a_liberer);
    }

    return 0;
}
