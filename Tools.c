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

// ***************************************************************
// FONCTIONS OUTILS pour la création et manipulation de LSC.

// - - - - - Pour Structure de Element str

// --------------------------------------------------------------
// Affichage LSC D'entiers : version du cours.
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

int p_est_vide(Pile_Gouts* p){
        return (p->data == NULL);
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

// - - - - - Pour Structure de File_Degustation

int taille_LSC_fileDegustation(File_Degustation * liste)
{
    if( liste == NULL){
        return 0;
    }
    else{
        return 1; //+ taille_LSC_rec(liste->Gateaux->next);
    }
}

// --------------------------------------------------------------
// Libération LSC
void free_list(File_Degustation* liste){
    if (liste != NULL){
        free_list(liste->Gateaux->next);
        free(liste);
    }
}

// - - - - - Pour Structure de File_commande

//---------------------------------------------------------------
// FONCTION OUTIL : Supprime 1 valeur d'une LSC (pas dans

void delete_1val(Element** liste, int val){
    while(*liste != NULL && (*liste)->dataInt == val){ // On supprime le 1ere élément, plusieurs fois avec while si sa
        // valeur est identique pour les suivants (d'affilée).
        Element* old = (*liste);
        (*liste) = (*liste)->next;
        free(old);
    }
    if (*liste != NULL){
        Element* temp = *liste;
        while(temp->next != NULL){
            if(temp->next->dataInt == val){
                Element* old = temp->next;
                temp->next = temp->next->next;
                free(old);
                break; // pour ne supprimer qu'une valeur
            }
            else{
                temp = temp->next;
            }
        }
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Vérifie si la liste de dégustation est vide.
int f_est_vide(File_Degustation* f){
    if (f->Gateaux == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Supprime un élément de la file de dégustation.
Gateau defiler(File_Degustation* f){
    //DONC je retire au début
    if(f_est_vide(f) != 1){
        Gateau res = *f->Gateaux->Gateau;
        Gateau * old = f->Gateaux->Gateau;
        f->Gateaux = f->Gateaux->next;
        free(old);
        return res;
    }
}