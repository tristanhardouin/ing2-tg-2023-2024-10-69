//
// Created by trist_wbwnhau on 03/12/2023.
//
#include <stdio.h>

int main() {
    // Déclaration des variables
    FILE *fichier;
    char nomFichier[] = "temps_cycle.txt";
    int tempsDeCycle;

    // Ouverture du fichier en mode lecture
    fichier = fopen(nomFichier, "r");

    // Vérification si le fichier est ouvert avec succès
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return 1; // Quitter le programme avec un code d'erreur
    }

    // Lecture du temps de cycle depuis le fichier
    fscanf(fichier, "%d", &tempsDeCycle);

    // Fermeture du fichier
    fclose(fichier);

    // Affichage du temps de cycle
    printf("Le temps de cycle est de %d secondes.\n", tempsDeCycle);

    return 0; // Terminer le programme avec succès
}