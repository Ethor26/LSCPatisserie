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
// FONCTIONS OUTILS pour la création et manipulation de LSC.

// - - - - - Pour Structure de Element str

// --------------------------------------------------------------
// Affichage LSC de chaine de caractères.
void display_list(Element_str * liste);

// - - - - - Pour Structure de Pile Gout

//---------------------------------------------------------------
// FONCTION OUTIL: Retourne la taille de la pile de gouts d'un gateau.
int taille_LSC_Gateau(Element_str * liste);

// --------------------------------------------------------------
// FONCTION OUTIL : vérifie si la pile des gouts est vide
int p_est_vide(Pile_Gouts* p);

// --------------------------------------------------------------
// FONCTION OUTIL : dépile la pile des gouts d'un gateau
char * depiler_gouts(Pile_Gouts * p);

// - - - - - Pour Structure de File_commande

// - - - - - Pour Structure de File_Degustation

//---------------------------------------------------------------
// FONCTION OUTIL: Vérifie si la liste de dégustation est vide.
int fileDeg_est_vide(File_Degustation* f);

//---------------------------------------------------------------
// FONCTION OUTIL: Supprime un élément de la file de dégustation.
void defiler_FileDeg(File_Degustation* f);

// --------------------------------------------------------------
// FONCTION OUTIL: Libération de la file de dégustation.
void free_list_Degust(File_Degustation* liste);