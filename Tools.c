//
// Created by ethan on 04/10/2021.
//

#include "Tools.h"
//
// Created by ethan on 13/09/2021.
//

// **************************************************************
// FONCTIONS OUTILS utilisées dans le reste du programme saisie sécurisée (empêche le problème de saisie de caractère.

// --------------------------------------------------------------
//FONCTION permettant de vider le buffer (emplacement de stockage en mémoire, par exemple de caractère) pour éviter les
// débordements
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

// --------------------------------------------------------------
//FONCTION permettant de lire une chaine de caractère plus ou moins longue de manière sécurisée.
int Lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}


// --------------------------------------------------------------
//FONCTION permettant de lire un entier avec le fonction lire de manière sécurisée
void LireInt(int * valeur)
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire
    do{
        Lire(nombreTexte, 100);
        *valeur = strtol(nombreTexte, NULL, 10);
    }while(*valeur == 0 && strcmp(nombreTexte, "0") != 0);
}

char * ConvCharChaine(char c){
    return ((char[2]) { c, '\0' });
}

// ***************************************************************
// FONCTIONS OUTILS pour la création et manipulation de LSC.

// - - - - - Pour Structure de Element str

// --------------------------------------------------------------
// FONCTION OUTIL qui créée une LSC d'Element_str
Element_str* creer_list(char ch[50]){
    Element_str* list_g;
    list_g = (Element_str*) malloc(sizeof (Element_str));
    for (int i =0; i<= 50; i++)
        list_g -> texte[i] = ch[i];
    list_g -> next = NULL;
    return list_g;
}

// --------------------------------------------------------------
// FONCTION OUTIL qui ajoute une valeur à la fin de la LSC d'Element_str
void ajout_val_fin_rec(Element_str** ad_liste, char txt[50]){
    if (*ad_liste == NULL) {
        *ad_liste = creer_list(txt); // voir Tools.c
    } else {
        ajout_val_fin_rec(&((*ad_liste)->next), txt);
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL qui mesure la taille de la LSC d'Element_str
int nb_el(Element_str* list){
    int cpt = 0;
    while (list != NULL){
        cpt++;
        list = list -> next;
    }
    return cpt;
}

// --------------------------------------------------------------
// FONCTION OUTIL Affichage LSC de chaine de caractères.
void display_list(Element_str * liste){
    if (liste != NULL){
        printf("%s-->", liste->texte);
        display_list(liste->next);
    }
    else{
        printf("X\n");
    }
}

// - - - - - Pour Structure de Pile Gout

// --------------------------------------------------------------
// FONCTION OUTIL : initialise la pile des gouts
Pile_Gouts* creer_pile_gout(){
    Pile_Gouts* nouv_pile = (Pile_Gouts*)malloc(sizeof(Pile_Gouts));
    nouv_pile->Gouts = NULL;
    return nouv_pile;
}

// --------------------------------------------------------------
// FONCTION OUTIL : vérifie si la pile des gouts est vide
int p_est_vide(Pile_Gouts* p){
        return (p->Gouts == NULL);
}

// --------------------------------------------------------------
// FONCTION OUTIL : dépile la pile des gouts d'un gateau
char * depiler_gouts(Pile_Gouts * p){
    if(p_est_vide(p) == 1){
        //GARGL
        return "\0";
    }
    else{
        char * res = p->Gouts->texte;
        Element_str * old = p->Gouts;
        p->Gouts = p->Gouts->next;
        free(old);
        return res;
    }
}



// - - - - - Pour Structure de File_commande

//---------------------------------------------------------------
// FONCTION OUTIL: Initialise la file de commandes.
File_Commandes * creer_file_Cmd(){
    File_Commandes * nouv_file = (File_Commandes*)malloc(sizeof(File_Commandes));
    nouv_file->commande = NULL;
    return nouv_file;
}

//---------------------------------------------------------------
// FONCTION OUTIL: Verifie si la liste de commande est vide.
int file_commande_vide(File_Commandes* f){
    if(f->commande == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

// - - - - - Pour Structure de File_Degustation

//---------------------------------------------------------------
// FONCTION OUTIL: Initialise la file de dégustations.
File_Degustation * creer_file_deg(){
    File_Degustation * nouv_file = (File_Degustation*)malloc(sizeof(File_Degustation));
    nouv_file->Gateaux = NULL;
    return nouv_file;
}

//---------------------------------------------------------------
// FONCTION OUTIL: Retourne la taille de la pile de gouts d'un gateau.
int taille_LSC_Gateau(Element_str * liste)
{
    if( liste == NULL){
        return 0;
    }
    else{
        return 1 + taille_LSC_Gateau(liste->next);
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Vérifie si la liste de dégustation est vide.
int fileDeg_est_vide(File_Degustation* f){
    if (f->Gateaux == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Supprime un élément de la file de dégustation.
void defiler_FileDeg(File_Degustation* f){
    if(fileDeg_est_vide(f) != 1){
        Element_gtx * temp = f->Gateaux;
        while(f->Gateaux->next != NULL)
            f->Gateaux = f->Gateaux->next;
        Gateau * old = f->Gateaux->Gateau;
        f->Gateaux = f->Gateaux->next;
        free(old);
        // Réinitialisation de f->Gateaux
        f->Gateaux = temp;
    }
}

// --------------------------------------------------------------
// Libération file de dégustation
void free_list_Degust(File_Degustation* liste){
    while(fileDeg_est_vide(liste) != 1){
        defiler_FileDeg(liste);
    }
    free(liste);
}
