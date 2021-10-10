#include "Fonctions gateaux.h"

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
            f_commandes->commande = nouv_el; // si oui on ajoute directement la chaine
        }
        else { // si non on ajoute la chaine à la fin
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
            case 'A':{ ajout_val_fin_rec(&list, "A"); goto Suite; }// ajout_val_fin_rec(&, txt) --> voir Tools.c
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
    G = (Gateau*)malloc(sizeof(Gateau));
    G->commande = commande; // on ajoute a commande la commande de l'utilisateur
    G->p_gouts = creer_pile_gout(); // on ajoute a p_gouts une pile de gouts, voir Tools.c
    return G;
}

// ----------------------------------------
// FONCTION : Assemblage des gouts du gateau commandé
void construire_gateau(Gateau* gateau, Element_str* l_gouts){
    Element_str* temp = l_gouts; // pour naviguer dans l_gouts
    Element_str* temp2 = gateau->commande; // pour naviguer dans gateau->commande

    while (temp2 != NULL){ // tant qu'on a pas fini de parcourir temp2
        while(temp2->texte[0] != temp->texte[0] && temp->next != NULL){ // tant que leur premières lettre sont diff et que la liste est non nulle
            temp = temp->next;// on passe augout suivant jusqu'a qu'on trouve le gout correspondant
        }
        ajout_val_deb(&gateau->p_gouts->Gouts,temp->texte); // on ajoute au début de la pile le gout de temp, voir Tools.c
        display_list(gateau->p_gouts->Gouts); // voir Tools.c
        temp = l_gouts; // on réinitialise temp
        temp2 = temp2->next; // on avance à la chaine suivante
        }
}

// ----------------------------------------
// FONCTION : Ajout du gateau préparé dans la file de dégustation
void livrer(Gateau* gateau, File_Degustation* f_degustation){
    Element_gtx * ElGat = malloc(sizeof(Element_gtx)); // on crée la boite du gateau
    ElGat->Gateau = gateau; // on y insert le gateau
    ElGat->next = f_degustation->Gateaux; // on enregistre la place du premier gateau dans la file (et le premier de la LSC)
    f_degustation->Gateaux = ElGat; // notre boite devient le premier dans la file (et le premier de la LSC)
    ElGat->Gateau->commande = NULL;
}


// ----------------------------------------
// FONCTION : Ordonnation la dégustation du client pour un gateau, retourne le nombre de parts restantes (s'il y en a).
// IMPORTANT : on considère qu'une part correspond à un gout de la pile de gout, le nombre de part aléatoire varie donc
// entre 0 et 50.
int degust1Gateau(Gateau * ElGateau, File_Degustation** f_degustation){
    if(ElGateau->p_gouts != NULL){
        Gateau * Parcours = ElGateau;
        int nb_parts = ChoixFaim();
        printf("%d parts vont etre mangees. \n", nb_parts);
        int cpt = 0;
        while(cpt<nb_parts){
            if(Parcours->p_gouts->Gouts != NULL){
                Element_str * temp = Parcours->p_gouts->Gouts->next;
                depiler_gouts(ElGateau->p_gouts);
                Parcours->p_gouts->Gouts = temp;
                cpt++;
            }
            else{
                defiler_FileDeg(*f_degustation);
                return 0;
            }
        }
        printf("Parts restantes");
        return(taille_LSC_Gateau(ElGateau->p_gouts->Gouts)-nb_parts); // Remplacer 1 par taille de LSC
    }
    else{
        printf("Erreur : gateau déjà mangé");
        return 0;
    }
}

// ----------------------------------------
// FONCTION : Ordonnation de la dégustation du client : gateau à déguster et nombre de part.
void degustation(File_Degustation* f_degustation){
    File_Degustation* temp = f_degustation; // pour naviguer dans f_degustation
    int NbGat = 0;
    if(fileDeg_est_vide(f_degustation))
        printf("File de dégustation vide");
    while(fileDeg_est_vide(f_degustation) == 0){ // tant qu'on a pas fini de naviguer dans las LSC
        int NbPartRest = degust1Gateau(f_degustation->Gateaux->Gateau, &f_degustation); // ??
        if(NbPartRest == 0){ // cas ou tout a été mangé
            NbGat++;
            printf("Gateau %d mange\n", NbGat);
            temp->Gateaux = temp->Gateaux->next;
        }
        else{ // cas ou il reste des gateaux et les parts restantese du n-ième gateau
            printf("Il reste %d parts a manger du Gateau %d\n", NbPartRest, NbGat);
        }
    }
}

// **************************************************************
// FONTIONS INTERFACE UTILISATEUR qui propose un menu d'action à l'utilisateur.

int Interface_User(int *EcritCmd, Element_str * l_gouts, File_Commandes * f_commandes, File_Degustation * f_degustations){
    int ChoixUser;
    do {
        printf("Quel est votre choix pour la gestion patissiere ? Entrez: \n"
               "1: Ecrire la commande \t 2: Recevoir la commande \t 3: Deguster un gateau \n"
               "4: Deguster tous les gateaux \t 5: Sortir \t 6: Commande aleatoire\n"); // Proposition du choix
        LireInt(&ChoixUser); // Entrée du choix de l'utilisateur (voir Tools.c)
    }while((int)ChoixUser < 1 || (int)ChoixUser > 6);

    switch(ChoixUser){
        case 1 : {
            printf("1) Ecriture de la commande.\n"); // Affiche le choix proposé
            // Fonction passer_commande
            char cmd[50];
            do{
                printf("Entrez la commande:");
                Lire(cmd, 50);
            }while(VerifGout(cmd) == 0); //voir Fonctions gateux.c

            *EcritCmd = 1; // Validation de l'initialisation
            passer_commande(cmd, f_commandes);
            printf("Commande recue\n");
            return ChoixUser;
        }
        case 2 : {
            if(*EcritCmd) {
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
            return ChoixUser;
        }
        case 3 : {
            printf("3) Degustation d'un gateau.\n"); // Affiche le choix proposé
            if(fileDeg_est_vide(f_degustations) == 0) {
                int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau, &f_degustations);
                printf("Il reste %d parts a manger du Gateau.\n", NbPartRest);
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            return ChoixUser;
        }
        case 4 : {
            printf("4) Degustation de tous les gateaux.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL){
                degustation(f_degustations); //+ verif si non vide
                printf("Tous les gateaux ont ete degustes.\n");
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            return ChoixUser;
        }
        case 5 : {
            printf("5) Fin du programme.\n"); // Affiche le choix proposé
            return ChoixUser;
        }

        case 6 : {
            int NbChang;
            printf("6) Commande Aleatoire : entrez le nombre de changements.\n"); // Affiche le choix proposé
            LireInt(&NbChang);
            for(int i = 0; i<NbChang; i++) // Remplacer par while avec aleat qui retourne le nbr de fin de programme
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
    int ChoixUser = 1 + rand() % 5;
    switch(ChoixUser){
        case 1 : {
            printf("1) Ecriture de la commande.\n"); // Affiche le choix proposé
            // Fonction passer_commande
            char cmd[50];
            do{
                printf("Entrez la commande:");
                Lire(cmd, 50);
            }while(VerifGout(cmd) == 0); //voir Fonctions gateux.c

            *EcritCmd = 1; // Validation de l'initialisation
            passer_commande(cmd, f_commandes);
            printf("Commande recue\n");
            break;
        }

        case 2 : {
            if(*EcritCmd) {
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
            break;
        }

        case 3 : {
            printf("3) Degustation d'un gateau.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL) {
                int NbPartRest = degust1Gateau(f_degustations->Gateaux->Gateau, f_degustations);
                printf("Il reste %d parts a manger du Gateau.\n", NbPartRest);
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            break;
        }
        case 4 : {
            printf("4) Degustation de tous les gateaux.\n"); // Affiche le choix proposé
            if(f_degustations->Gateaux != NULL){
                degustation(f_degustations); //+ verif si non vide
                printf("Tous les gateaux ont ete degustes.\n");
            }
            else
                printf("Pas de gateaux dans la liste de degustation\n");
            break;
        }
        case 5 : {
            printf("5) Fin du programme.\n"); // Affiche le choix proposé
            break;
        }

        default:{
            printf("Def : Retour menu");
            break;
        }
    }
}