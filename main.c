// Déclaration bibliothèques (toutes ne sont pas utilisées)
# include "Fonctions gateaux.h"

int main() {
// Déclaration variables //
        int RefFich;
        int EcritCmd = 0, ReceptCmd = 0; // Variable (booléens) vérifiant respectivement dans le main si la commande a
        // été écrite et recue.
/*Algorithme */
        printf("Entrez la référence de l'algorithme à tester");
        LireInt(&RefFich);
        switch(RefFich){
        // I. Algos principal
            case 1 : { printf("Debut de l'algorithme principal :\n");
                // Creation du rubik (pas dans le choix de l'utilisateur)
                ; // Creation d'un rubik's Cube: a voir si dans ce case ou hors de la fonction.
                int ChoixUser;
                do {
                    ChoixUser = Interface_User(&EcritCmd, &ReceptCmd);
                }while(ChoixUser != 5);

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

        //Libération des variables
        // free_list_Degust(liste)
}



