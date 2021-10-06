//
// Created by maxim on 04/10/2021.
//

#ifndef LSCPATISSERIE_FONCTIONS_GATEAUX_H
#define LSCPATISSERIE_FONCTIONS_GATEAUX_H

#endif //LSCPATISSERIE_FONCTIONS_GATEAUX_H

# include "Tools.h"

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
void degustation(File_Degustation* f_degustation);

// **************************************************************
// FONTIONS INTERFACE UTILISATEUR qui propose un menu d'action à l'utilisateur.
int Interface_User(int *EcritCmd, int*ReceptCmd);