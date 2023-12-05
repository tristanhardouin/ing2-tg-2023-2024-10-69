/*int main()
{
    t_Graphe * g, *g2;
    int first,i;
    char nom_fichier[50];

    printf("entrer le nom du fichier du graphe:");
    gets(nom_fichier);
    g = lire_graphe(nom_fichier,0);


    /// afficher le graphe
    graphe_afficher(g);

    Reinitialisation 
    // ordre +2 pour correction bug CreerArete
    for(i=0;i<g->ordre;i++)
    {
        if(g->pSommet[i]->marquageFauxSommet==0){
            i++;
        }
        g->pSommet[i]->couleur=i;
    }

    // Recherche composantes connexes
    printf("\nListe composantes connexes\n");

    // reconstruction du graphe si jamais oriente
    g2 = lire_graphe(nom_fichier,1);

    Reinitialisation 
    // ordre +2 pour correction bug CreerArete
    for(i=0;i<g2->ordre;i++)
    {
        g2->pSommet[i]->couleur='B';
    }
    recherche_connexe(g2);

    tempsDeCycle(g2);

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>

// Définition de la structure operation
struct operation {
    int duree;
    struct operation *suivant; // Ajout d'un pointeur vers la prochaine opération
};

// Définition de la structure temps_cycle utilisé plus tard pour la fonction de calcul du temps de cycle
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
} // resultat



/*#include <stdio.h>
#include <stdlib.h>
#include "fcts_contrainte_precedences.h"
#include "fcts_lecture_fichiers.h"

struct matrice_adjacence* Creer_noeud(int X) {
    struct matrice_adjacence* noeud = (struct matrice_adjacence*)malloc(sizeof(struct matrice_adjacence));
    noeud->valeur = X;
    noeud->suiv = NULL;
    return noeud;
}

struct Graphes* Creer_graphe(int nbSommet) {
    struct Graphes* graph = (struct Graphes*)malloc(sizeof(struct Graphes));
    graph->nb_sommets = nbSommet;
    graph->list_adj = (struct matrice_adjacence**)malloc(nbSommet * sizeof(struct matrice_adjacence*));
    for (int i = 0; i < nbSommet; ++i){
        graph->list_adj[i] = NULL;
    }
    return graph;
}



void CreerArrete(struct Graphes* graph, int src, int dest) {
    struct matrice_adjacence* noeud = Creer_noeud(dest);
    noeud->suiv = graph->list_adj[src];
    graph->list_adj[src] = noeud;
}

struct Graphes* initialiser_Graphe() {
    FILE *file;
    file = fopen("../precedences.txt", "r");
    if (file == NULL) {
        printf("Erreur ouverture precedences");
    }
    int nbArrete = 0;
    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        if (src > nbArrete) nbArrete = src;
        if (dest > nbArrete) nbArrete = dest;
    }
    fseek(file, 0, SEEK_SET);
    struct Graphes *graph = Creer_graphe(nbArrete + 1);
    while (fscanf(file, "%d %d", &src, &dest) == 2) {
        CreerArrete(graph, src, dest);
    }
    fclose(file);
    return graph;
}
*/

