#include "Fonctions gateaux.h"
#include "stdlib.h"

Element_str* initialiser_gouts(){ // Commentaire inutile

}

void passer_commande(char commande[50], File_Commandes* f_commandes ){

}

Element_str* traiter_commande(File_Commandes* f_commandes){

}

Gateau* creer_gateau(Element_str* commande){
Gateau* G;
G = (Gateau*) malloc(sizeof(Gateau));
G->commande = commande;
return G;
}

void construire_gateau(Gateau* gateau, Element_str* l_gouts){
gateau->p_gouts->Gouts = l_gouts;
}

void livrer(Gateau* gateau, File_Degustation* f_degustation){

}

void degustation(File_Degustation* f_degustation, int nb_parts){

}