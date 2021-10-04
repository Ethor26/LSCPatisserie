// Déclaration bibliothèques (toutes ne sont pas utilisées)
# include "Fonctions gateaux.h"

int main() {
// Déclaration variables //
        int RefFich;

/*Algorithme */
        printf("Entrez la référence de l'exo de TD ou 0 pour un exo de cour ou -1 pour renommer un fichier: ");
        LireInt(&RefFich);
        switch(RefFich){
        // I. Algos principal
            case 1 : { printf("Debut de l'algorithme\n"); //
                break; }
        // II. Test de chacun
            case 2: { printf("Debut de l'algorithme\n");
                initialiser_gouts();
                break; }

        // III. Affichage par défaut (si erreurs).
            default : {
                printf("Au revoir");
            }
        return 0 ; }
}


