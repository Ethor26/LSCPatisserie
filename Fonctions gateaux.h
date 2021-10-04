//
// Created by maxim on 04/10/2021.
//

#ifndef LSCPATISSERIE_FONCTIONS_GATEAUX_H
#define LSCPATISSERIE_FONCTIONS_GATEAUX_H

#endif //LSCPATISSERIE_FONCTIONS_GATEAUX_H

# include "Tools2.h"
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

// ****************************************
// PARTIE 2 : Fonctions de conception et demande de gateau

// ----------------------------------------
// FONCTION : Initialise la liste des gouts possibles
Element_str* initialiser_gouts();

// ----------------------------------------
// FONCTION : Convertie la liste de gout en commande de gateau
void passer_commande(char commande[50], File_Commandes* f_commandes );

// ----------------------------------------
// FONCTION : Récupération d'une commande de la liste de commandes.
Element_str* traiter_commande(File_Commandes* f_commandes);

// ****************************************
// PARTIE 3 : Fonctions de creation et livraison de gateau

// ----------------------------------------
// FONCTION : Création de gateau à partir d'une commande
Gateau* creer_gateau(Element_str* commande);

// ----------------------------------------
// FONCTION : Assemblage des gouts du gateau commandé
void construire_gateau(Gateau* gateau, Element_str* l_gouts);

// ----------------------------------------
// FONCTION : Ajout du gateau préparé dans la file de dégustation
void livrer(Gateau* gateau, File_Degustation* f_degustation);

// ----------------------------------------
// FONCTION : Ordonnation de la dégustation du client : gateau à déguster et nombre de part.
void degustation(File_Degustation* f_degustation, int nb_parts);
