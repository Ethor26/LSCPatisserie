//
// Created by ethan on 04/10/2021.
//

#ifndef LSCPATISSERIE_TOOLS2_H
#define LSCPATISSERIE_TOOLS2_H

#endif //LSCPATISSERIE_TOOLS2_H
//
// Created by ethan on 13/09/2021.
//

#ifndef EXTD_TOOLS_H
#define EXTD_TOOLS_H

#endif //EXTD_TOOLS_H

// Bibliothèque de références.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// **************************************************************
// FONCTIONS OUTILS utilisées dans le reste du programme saisie sécurisée (empêche le problème de saisie de caractère.
void viderBuffer();
int Lire(char *chaine, int longueur);
void LireInt(int * valeur);

// ****************************************
// PARTIE 0 : STRUCTURES

// ----------------------------------------
// STRUCTURE 1: LSC de chaines de caractères.
typedef struct Element_str{
    char texte[50];
    struct Element_str* next;
}Element_str;

// ----------------------------------------
// STRUCTURE 2: Eléments constitutifs d'un gateau.
typedef struct Gateau{
    struct Element_str* commande;
    struct Pile_Gouts* p_gouts;
}Gateau;

// ----------------------------------------
// STRUCTURE 3: LSC de la structure gateau
typedef struct Element_gtx{
    struct Gateau* Gateau;
    struct Element_gtx* next;
}Element_gtx;

// ----------------------------------------
// STRUCTURE 4: File de STRUCTURE3 pour la commande
typedef struct File_Commandes{
    struct Element_gtx* Gateaux;
}File_Commandes;

// ----------------------------------------
// STRUCTURE 5: Pile de STRUCTURE1 pour le gateau.
typedef struct Pile_Gouts{
    struct Element_str* Gouts;
}Pile_Gouts;

// ----------------------------------------
// STRUCTURE 5: File de STRUCTURE3 pour la dégustation
typedef struct File_Degustation{
    struct Element_gtx* Gateaux;
}File_Degustation;

// ***************************************************************
// FONCTIONS OUTILS pour la création de structure quelquonques d'entiers et de caractères.
typedef struct element{
    int dataInt;
    struct element* next;
}Element;

void display_list(Element_str* liste);
void free_list(File_Degustation* liste);

// --------------------------------------------------------------
// FONCTION OUTIL : dépile la pile des gouts d'un gateau
char * depiler_gouts(Pile_Gouts * p);

//---------------------------------------------------------------
// FONCTION OUTIL: Vérifie si la liste de dégustation est vide.
int f_est_vide(File_Degustation* f);

//---------------------------------------------------------------
// FONCTION OUTIL: Supprime un élément de la file de dégustation.
Gateau defiler(File_Degustation* f);