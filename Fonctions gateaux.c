#include "Fonctions gateaux.h"
#include "stdlib.h"

Element_str* initialiser_gouts(){

}

void passer_commande(char commande[50], File_Commandes* f_commandes ){

}

Element_str* traiter_commande(File_Commandes* f_commandes){

}

Gateau* creer_gateau(Element_str* commande){
Gateau* G;
G = (Gateau*) malloc(sizeof(Gateau));
G->commande = commande;
return G;
}

void construire_gateau(Gateau* gateau, Element_str* l_gouts){
    Element_str* temp;
    Element_str* temp2;
    Element_str* temp3;
    temp = l_gouts;
    for(int i = 0; i< strlen(gateau->commande->texte); i++){
        while(gateau->commande->texte[i] != temp->texte[0]){
            temp = temp->next;
        }
        if(i==0){
            temp2 = temp;
            temp3 = temp2;
        }
        else{
            temp2->next = temp;
            temp2 = temp2->next;
        }
        temp = l_gouts;
    }
    gateau->p_gouts->Gouts = temp3;
}

// ----------------------------------------
// FONCTION : Ajout du gateau préparé dans la file de dégustation
void livrer(Gateau* gateau, File_Degustation* f_degustation){
    Element_gtx * ElGat = malloc(sizeof(Element_gtx));
    ElGat->Gateau = gateau;
    ElGat->next = f_degustation->Gateaux;
    f_degustation->Gateaux = ElGat;
    ElGat->Gateau->commande = NULL;
}

// ----------------------------------------
// FONCTION : Ordonnation la dégustation du client pour un gateau, retourne le nombre de parts restantes (s'il y en a).
int degust1Gateau(Gateau * ElGateau){
    Gateau * temp = ElGateau;
    int nb_parts = 1 + rand() % 8;
    printf("%d parts vont être mangées. \n", nb_parts);
    int cpt = 0;
    while(cpt<nb_parts){
        if(temp->p_gouts->Gouts != NULL){
            depiler_gouts(ElGateau->p_gouts);
            temp->p_gouts->Gouts = temp->p_gouts->Gouts->next;
            cpt++;
        }
        else{
            return 0;
        }
    }
    printf("Parts restantes (test)");
    return(taille_LSC_Gateau(ElGateau->p_gouts->Gouts)-nb_parts); // Remplacer 1 par taille de LSC
}

// ----------------------------------------
// FONCTION : Ordonnation de la dégustation du client : gateau à déguster et nombre de part.
void degustation(File_Degustation* f_degustation){
    File_Degustation* temp = f_degustation;
    int NbGat = 0;
    while(temp->Gateaux != NULL){
        int NbPartRest = degust1Gateau(f_degustation->Gateaux->Gateau);
        if(NbPartRest == 0){
            NbGat++;
            defiler_FileDeg(f_degustation);
            printf("Gateau %d mange\n", NbGat);
            temp->Gateaux = temp->Gateaux->next;
        }
        else{
            printf("Il reste %d parts à manger du Gateau %d\n", NbPartRest, NbGat);
        }
    }
}

// **************************************************************
// FONTIONS INTERFACE UTILISATEUR qui propose un menu d'action à l'utilisateur.

int Interface_User(int *EcritCmd, Element_str * l_gouts, File_Commandes * f_commandes, File_Degustation * f_degustations){
    int ChoixUser;
    do {
        printf("Quel est votre choix pour la gestion patissière ? Entrez: \n"
               "1: Ecrire la commande \t 2: Recevoir la commande \t 3: Deguster un gateau \n"
               "4: Deguster tous les gateaux \t 5: Sortir \t 6: Commande aléatoire\n"); // Proposition du choix
        LireInt(&ChoixUser); // Entrée du choix de l'utilisateur
    }while((int)ChoixUser < 1 || (int)ChoixUser > 6);
    switch(ChoixUser){
        case 1 : {
            printf("Ecriture de la commande.\n"); // Affiche le choix proposé
            // Fonction passer_commande
            *EcritCmd = 1; // Validation de l'initialisation
            return ChoixUser;
        }
        case 2 : {
            if(*EcritCmd) {
                printf("Reception de commande.\n"); // Affiche le choix proposé
                livrer(f_commandes->Gateaux->Gateau, f_degustations);
                printf("Commande recue.");
            }
            else
                printf("Ecrivez une commande avant.\n");
            return ChoixUser;
        }
        case 3 : {
            printf("Degustation d'un gateau.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL) {
                int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau);
                printf("Il reste %d parts à manger du Gateau.\n", NbPartRest);
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            return ChoixUser;
        }
        case 4 : {
            printf("Degustation de tous les gateaux.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL){
                degustation(f_degustations); //+ verif si non vide
                printf("Tous les gateaux ont été dégustés.\n");
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            return ChoixUser;
        }
        case 5 : {
            printf("Fin du programme.\n"); // Affiche le choix proposé
            return ChoixUser;
        }

        case 6 : {
            int NbChang;
            printf("Commande Aléatoire : entrez le nombre de changements.\n"); // Affiche le choix proposé
            LireInt(&NbChang);
            for(int i = 0; i<NbChang; i++)
                Aleat_Choix(EcritCmd, l_gouts, f_commandes, f_degustations);
            return ChoixUser;
        }

        default:{
            return ChoixUser;
        }
    }
}

// ------------------------------------------------------------
// FONCTION gérant le choix aléatoire du cas 6
void Aleat_Choix(int *EcritCmd, Element_str * l_gouts, File_Commandes * f_commandes, File_Degustation * f_degustations){
    int ChoixUser = 1 + rand() % 4;
    switch(ChoixUser){
        case 1 : {
            printf("Ecriture de la commande.\n"); // Affiche le choix proposé
            // Fonction passer_commande
            *EcritCmd = 1; // Validation de l'initialisation
            break;
        }
        case 2 : {
            printf("Reception de commande en cours.\n");// Affiche le choix proposé
            if(*EcritCmd) {
                livrer(f_commandes->Gateaux->Gateau, f_degustations);
                printf("Commande recue.");
            }
            else
                printf("Ecrivez une commande avant.\n");
        }
            break;
        case 3 : {
            printf("Degustation d'un gateau.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL) {
                int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau);
                printf("Il reste %d parts à manger du Gateau.\n", NbPartRest);
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
        }
            break;
        case 4 : {
            printf("Degustation de tous les gateaux.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL){
                degustation(f_degustations); //+ verif si non vide
                printf("Tous les gateaux ont été dégustés.\n");
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
        }
            break;

        default:{
            printf("Instruction non comprise.\n");
            break;
        }
    }
}