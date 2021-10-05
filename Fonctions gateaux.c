#include "Fonctions gateaux.h"
#include "stdlib.h"

Element_str* initialiser_gouts(){

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
    Element_str* temp;
    Element_str* temp2;
    Element_str* temp3;
    temp = l_gouts;
    for(int i = 0; i< strlen(gateau->commande->texte); i++){
        while(gateau->commande->texte[i] != temp->texte[0]){
            temp = temp->next;
        }
        if(i==0){
            temp2 = temp;
            temp3 = temp2;
        }
        else{
            temp2->next = temp;
            temp2 = temp2->next;
        }
        temp = l_gouts;
    }
    gateau->p_gouts->Gouts = temp3;
}

void livrer(Gateau* gateau, File_Degustation* f_degustation){
    Element_gtx * ElGat = malloc(sizeof(Element_gtx));
    ElGat->Gateau = gateau;
    ElGat->next = f_degustation->Gateaux;
    f_degustation->Gateaux = ElGat;
    ElGat->Gateau->commande = NULL;
}

int degust1Gateau(Element_gtx * ElGateau, int nb_parts){
    Element_gtx * temp = ElGateau;
    int cpt = 0;
    while(cpt<nb_parts){
        if(temp != NULL){
            depiler_gouts(ElGateau->Gateau->p_gouts);
            temp = temp->next;
            cpt++;
        }
        else{
            return 0;
        }
    }
    return(1-nb_parts); // Remplacer 1 par taille de LSC
}

void degustation(File_Degustation* f_degustation, int nb_parts){
    File_Degustation* temp = f_degustation;
    int NbGat = 0;
    while(temp->Gateaux != NULL){
        int NbPartRest = degust1Gateau(f_degustation->Gateaux, nb_parts);
        if(NbPartRest == 0){
            NbGat++;
            defiler(f_degustation);
            printf("Gateau %d mange\n", NbGat);
            temp->Gateaux = temp->Gateaux->next;
        }
        else{
            printf("Apres dégustation de %d parts, il reste %d part à manger du Gateau %d\n",nb_parts, NbPartRest, NbGat);
        }
    }
}

