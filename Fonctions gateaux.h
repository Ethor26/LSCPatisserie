//
// Created by maxim on 04/10/2021.
//

#ifndef LSCPATISSERIE_FONCTIONS_GATEAUX_H
#define LSCPATISSERIE_FONCTIONS_GATEAUX_H

#endif //LSCPATISSERIE_FONCTIONS_GATEAUX_H

# include "Tools.h"

// ****************************************
// PARTIE 1 : Fonctions de conception et demande de gateau

// ----------------------------------------
// FONCTION : Initialise la liste des gouts possibles
Element_str* initialiser_gouts();

// ----------------------------------------
// FONCTION : Convertie la liste de gout en commande de gateau
void passer_commande(char commande[50], File_Commandes* f_commandes );

// ----------------------------------------
// FONCTION : Récupération d'une commande de la liste de commandes.
Element_str* traiter_commande(File_Commandes* f_commandes);

// --------------------------------------------------------
// FONCTION Convertissant une commande en une liste chainée.
Element_str* conversion(char com[50]);

// ****************************************
// PARTIE 2 : Fonctions de creation et livraison de gateau

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
// FONCTION : Ordonnation la dégustation du client pour un gateau, retourne le nombre de parts restantes (s'il y en a).
// IMPORTANT : on considère qu'une part correspond à un gout de la pile de gout, le nombre de part aléatoire varie donc
// entre 0 et 50.
int degust1Gateau(Gateau * ElGateau, File_Degustation** f_degustation);

// ----------------------------------------
// FONCTION : Ordonnation de la dégustation du client : gateau à déguster et nombre de part.
void degustation(File_Degustation* f_degustation);

// **************************************************************
// FONTIONS INTERFACE UTILISATEUR qui propose un menu d'action à l'utilisateur.
int Interface_User(int *EcritCmd, Element_str * l_gouts, File_Commandes * f_commandes, File_Degustation * f_degustations);

// ------------------------------------------------------------
// FONCTION gérant le choix aléatoire du cas 6
void Aleat_Choix(int *EcritCmd, Element_str * l_gouts, File_Commandes * f_commandes, File_Degustation * f_degustations);