#include "Fonctions gateaux.h"
#include "stdlib.h"

// ****************************************
// PARTIE 1 : Fonctions de conception et demande de gateau

// ----------------------------------------
// FONCTION : Initialise la liste des gouts possibles
Element_str* initialiser_gouts(){
    //on crée un premier pointeur
    Element_str* gout = (Element_str*)malloc(sizeof(Element_str));

    char T_gouts[7][20] = {{"Chocolat"},
                           {"Vanille"},
                           {"Fraise"},
                           {"Abricot"},
                           {"Pomme"},
                           {"Banane"},
                           {"Myrtille"}};
    // ce compteur va permettre de naviguer dans le tableau de gouts
    int cpt = 0;
    strcpy(gout->texte, T_gouts[cpt]);
    gout->next = NULL;

    //on naviguera dans la LSC grace à temp
    Element_str* temp = gout;

    while(cpt < 6){
        cpt++;
        // on cré une nouvelle chaine qu'on lira à la chaine précédente
        Element_str* temp2 = (Element_str*)malloc(sizeof(Element_str));
        strcpy(temp2->texte, T_gouts[cpt]);
        temp2->next = NULL;
        temp->next = temp2;
        // on avance dans temp
        temp = temp->next;
    }
    return gout;
}



// ----------------------------------------
// FONCTION : Convertie la liste de gout en commande de gateau
void passer_commande(char commande[50], File_Commandes* f_commandes){
    if (nb_el(f_commandes->commande) <10) // on compte le nombre d'elements, voir fonctions Tools.c
    {
        Element_str * nouv_el = creer_list(commande); // on une LSC de type Element_str, voir fonctions Tools.c

        // Ajout à la fin de la file LSC f_commandes le nouvel element nouv_el
        if (file_commande_vide(f_commandes)) { // on regarde si la liste est vide ou non, voir fonctions Tools.c
            f_commandes->commande = nouv_el;
        }
        else {
            Element_str *temp = f_commandes->commande;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nouv_el;
        }
    }
    else{
        printf("Liste de commandes pleine.\n");
    }
}

// ----------------------------------------
// FONCTION : Récupération d'une commande de la liste de commandes.
Element_str* traiter_commande(File_Commandes* f_commandes){
    if (f_commandes != NULL){
        Element_str* cpt = conversion(f_commandes->commande->texte); //Conversion de la chaine de caractère de la
        // commande en LSC
        Element_str* temp = f_commandes->commande -> next; //Suppression de la commande récupérée de la file de commande
        free(f_commandes->commande);
        f_commandes->commande = temp;
        return cpt;
    }
    return NULL;
}


// --------------------------------------------------------
// FONCTION Convertissant une commande en une liste chainée.
Element_str* conversion(char com[50]){
    Element_str* list = creer_list(ConvCharChaine(com[0]));
    for (int i =1; i <= strlen(com); i++){ //on va parcourir la commande (chaine de caractère)
        switch(com[i]){ // pour chaque caractère, on va creer une chaine dans la LSC list
            case 'C':{ ajout_val_fin_rec(&list, "C"); goto Suite; }
            case 'V':{ ajout_val_fin_rec(&list, "V"); goto Suite; }
            case 'F':{ ajout_val_fin_rec(&list, "F"); goto Suite; }
            case 'A':{ ajout_val_fin_rec(&list, "A"); goto Suite; }
            case 'P':{ ajout_val_fin_rec(&list, "P"); goto Suite; }
            case 'B':{ ajout_val_fin_rec(&list, "B"); goto Suite; }
            case 'M':{ ajout_val_fin_rec(&list, "M"); goto Suite; }
            case '\0':return list;
        }
            Suite: ;
    }
    return list;
}

// ****************************************
// PARTIE 2 : Fonctions de creation et livraison de gateau

// ----------------------------------------
// FONCTION : Création de gateau à partir d'une commande
Gateau* creer_gateau(Element_str* commande){
    Gateau* G;
    G = (Gateau*) malloc(sizeof(Gateau));
    G->commande = commande;
    return G;
}

// ----------------------------------------
// FONCTION : Assemblage des gouts du gateau commandé
void construire_gateau(Gateau* gateau, Element_str* l_gouts){
    Element_str* temp;
    temp = l_gouts;
    for(int i = 0; i< strlen(gateau->commande->texte); i++){
        while(gateau->commande->texte[i] != temp->texte[0]){
            temp = temp->next;
        }
        ajout_val_fin_rec(&gateau->p_gouts->Gouts,temp->texte);
        temp = l_gouts;
        }
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
            char cmd[50];
            do{
                printf("Entrez la commande:");
                Lire(cmd, 50);
            }while(VerifGout(cmd) == 0);

            *EcritCmd = 1; // Validation de l'initialisation
            passer_commande(cmd, f_commandes);
            printf("Commande recue\n");
            return ChoixUser;
        }
        case 2 : {
            if(*EcritCmd) {
                printf("Reception de commande.\n"); // Affiche le choix proposé
                Element_str * liste_gouts_toDo = traiter_commande(f_commandes);
                display_list(liste_gouts_toDo); // Pour test

                Gateau * GatConstr = creer_gateau(f_commandes->commande);
                construire_gateau(GatConstr, liste_gouts_toDo); // l_gouts à vérifier
                printf("Pass constrGat");
                livrer(GatConstr, f_degustations);
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
            char cmd[50];
            Lire(cmd, 50);
            *EcritCmd = 1; // Validation de l'initialisation
        }
        case 2 : {
            if(*EcritCmd) {
                printf("Reception de commande.\n"); // Affiche le choix proposé
                Gateau * GatConstr = creer_gateau(f_commandes->commande);
                construire_gateau(GatConstr, l_gouts); // l_gouts à vérifier
                livrer(GatConstr, f_degustations);
                printf("Commande recue.");
            }
            else
                printf("Ecrivez une commande avant.\n");
        }
        case 3 : {
            printf("Degustation d'un gateau.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL) {
                int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau);
                printf("Il reste %d parts à manger du Gateau.\n", NbPartRest);
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
        }
        case 4 : {
            printf("Degustation de tous les gateaux.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL){
                degustation(f_degustations); //+ verif si non vide
                printf("Tous les gateaux ont été dégustés.\n");
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
        }
        case 5 : {
            printf("Fin du programme.\n"); // Affiche le choix proposé
        }

        case 6 : {
            int NbChang;
            printf("Commande Aleatoire : entrez le nombre de changements.\n"); // Affiche le choix proposé
            LireInt(&NbChang);
            for(int i = 0; i<NbChang; i++)
                Aleat_Choix(EcritCmd, l_gouts, f_commandes, f_degustations);
        }

        default:{
            printf("default");
        }
    }
}