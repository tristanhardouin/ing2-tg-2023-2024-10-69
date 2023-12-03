struct operation {
    int duree;
    struct operation *suivant; // Ajout d'un pointeur vers la prochaine opération
};

// Définition de la structure temps_cycle
struct temps_cycle {
    int duree;
};