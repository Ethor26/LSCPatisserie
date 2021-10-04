//
// Created by maxim on 04/10/2021.
//

#ifndef LSCPATISSERIE_FONCTIONS_GATEAUX_H
#define LSCPATISSERIE_FONCTIONS_GATEAUX_H

#endif //LSCPATISSERIE_FONCTIONS_GATEAUX_H

typedef struct Element_str{
    char texte[50];
    struct Element_str* next;
}Element_str;

typedef struct Gateau{
    struct Element_str* commande;
    struct Pile_Gouts* p_gouts;
}Gateau;

typedef struct Element_gtx{
    struct Gateau* Gateau;
    struct Element_gtx* next;
}Element_gtx;

typedef struct File_Commandes{
struct Element_gtx* Gateaux;
}File_Commandes;

typedef struct Pile_Gouts{
struct Element_str* Gouts;
}Pile_Gouts;

typedef struct File_Degustation{
struct Element_gtx* Gateaux;
}File_Degustation;

Element_str* initialiser_gouts();

void passer_commande(char commande[50], File_Commandes* f_commandes );

Element_str* traiter_commande(File_Commandes* f_commandes);

Gateau* creer_gateau(Element_str* commande);

void construire_gateau(Gateau* gateau, Element_str* l_gouts);

void livrer(Gateau* gateau, File_Degustation* f_degustation);

void degustation(File_Degustation* f_degustation, int nb_parts);
