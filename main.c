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

}