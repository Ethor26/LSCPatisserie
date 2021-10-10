// Déclaration bibliothèques (toutes ne sont pas utilisées)
# include "Fonctions gateaux.h"

int main() {
// Déclaration variables //
        int RefFich;
        int EcritCmd = 0; // Variable (booléens) vérifiant respectivement dans le main si la commande a
        // été écrite et recue.
        Element_str* l_gouts = initialiser_gouts(); //on crée la liste des gouts possible (voir Fonctions gateaux.c)
        File_Commandes * f_commandes = creer_file_Cmd(); //on crée la file des commandes (voir Tools.c)
        File_Degustation * f_degustations = creer_file_deg(); //on crée la file de degustation (voir Tools.c)

/*Algorithme */
        printf("Entrez la reference de l'algorithme a tester: \n");
        LireInt(&RefFich);
        switch(RefFich){
        // I. Algos principal
            case 1 : { printf("Debut de l'algorithme principal :\n");
                int ChoixUser;
                do {
                    ChoixUser = Interface_User(&EcritCmd, l_gouts, f_commandes, f_degustations);//voir Fonctions gateux.c
                }while(ChoixUser != 5); //Lancement de l'interface tant que l'utilisateur n'arrete pas le programme

                //Libération
                free_file_degustation(f_degustations);
                free_FILE_commande(f_commandes);
                free_Element_str(l_gouts);

                break;}

        // II. Test de chacun
            case 2: { printf("Debut de l'algorithme:\n");
                Element_str* gout = initialiser_gouts(); // voir Fonctions gateux.c
                display_list(gout); //voir Tools.c
                break; }

            case 3: { printf("Debut de l'algorithme:\n");
                char * ChaineTest = "CMV";
                int nbr = ChoixFaim();
                // conversion(ChaineTest); //voir Fonctions gateux.c
                break; }

            case 4: { printf("Debut de l'algorithme:\n");
                Element_str * ListeStrTest = creer_list("CMV");
                ajout_val_deb(&ListeStrTest, "VC");
                display_list(ListeStrTest);
                free_Element_str(ListeStrTest);
                display_list(ListeStrTest);
                break; }

            case 5:{
                printf("1) Ecriture de la commande.\n"); // Affiche le choix proposé
                // Fonction passer_commande
                char cmd[50];
                do{
                    printf("Entrez la commande:");
                    Lire(cmd, 50);
                }while(VerifGout(cmd) == 0); //voir Fonctions gateux.c

                EcritCmd = 1; // Validation de l'initialisation
                passer_commande(cmd, f_commandes);
                printf("Commande recue\n");

                if(EcritCmd) {
                    printf("2) Reception de commande.\n"); // Affiche le choix proposé
                    Element_str * liste_gouts_toDo = traiter_commande(f_commandes);
                    display_list(liste_gouts_toDo); // Pour test

                    Gateau * GatConstr = creer_gateau(f_commandes->commande);
                    GatConstr->commande = liste_gouts_toDo;
                    construire_gateau(GatConstr, l_gouts);
                    livrer(GatConstr, f_degustations);
                }
                else
                    printf("Ecrivez une commande avant.\n");

                printf("3) Degustation d'un gateau.\n"); // Affiche le choix proposé
                if(fileDeg_est_vide(f_degustations) == 0) {
                    int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau, &f_degustations);
                    printf("Il reste %d parts a manger du Gateau.\n", NbPartRest);
                }
                else
                    printf("Pas de gateaux dans la liste de degustation\n");

                break;
            }


            case 6: {
                printf("1) Ecriture de la commande.\n"); // Affiche le choix proposé
                // Fonction passer_commande
                char cmd[50];
                do {
                    printf("Entrez la commande:");
                    Lire(cmd, 50);
                } while (VerifGout(cmd) == 0); //voir Fonctions gateux.c

                EcritCmd = 1; // Validation de l'initialisation
                passer_commande(cmd, f_commandes);
                printf("Commande recue\n");

                if (EcritCmd) {
                    printf("2) Reception de commande.\n"); // Affiche le choix proposé
                    Element_str *liste_gouts_toDo = traiter_commande(f_commandes);
                    display_list(liste_gouts_toDo); // Pour test

                    Gateau *GatConstr = creer_gateau(f_commandes->commande);
                    GatConstr->commande = liste_gouts_toDo;
                    construire_gateau(GatConstr, l_gouts);
                    livrer(GatConstr, f_degustations);
                } else
                    printf("Ecrivez une commande avant.\n");

                printf("4) Degustation de tous les gateaux.\n"); // Affiche le choix proposé
                if (f_degustations->Gateaux != NULL) {
                    degustation(f_degustations); //+ verif si non vide
                    printf("Tous les gateaux ont ete degustes.\n");
                } else
                    printf("Pas de gateaux dans la liste de degustation\n");

                break;
            }

        // III. Affichage par défaut (si erreurs).
            default : {
                printf("Au revoir");
            }
        return 0 ; }

        //Libération des variables
        // free_list_Degust(liste)
}



