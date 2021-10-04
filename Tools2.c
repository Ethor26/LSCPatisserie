//
// Created by ethan on 04/10/2021.
//

#include "Tools2.h"
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
// FONCTIONS OUTILS pour la création et manipulation de LSC d'entiers.

// --------------------------------------------------------------
// Fonction créeant un élément (objet) d'une LSC contenant un entier et la référence vers le suivant.
Element * creer_element_Int(int val){
    Element * nouv_el;
    nouv_el = (Element *)malloc(sizeof(Element));
    nouv_el->dataInt = val;
    nouv_el->next = NULL;
    return nouv_el;
}

// --------------------------------------------------------------
// Creation LSC D'entiers : version personnelle avec sélection de valeurs.
Element * CreationLSC_Int(){
    Element * El;
    // El = NULL; // Pour Test /*
    El = creer_element_Int(1);
    El->next = creer_element_Int(5);
    El->next->next = creer_element_Int(3); // */
    return El;
}

// --------------------------------------------------------------
// Creation LSC D'entiers : version du cours avec suite croissante.
Element* create_list(int n){
    if (n <= 0){
        return NULL;
    }
    else{
        Element* nouv_liste = creer_element_Int(1);
        Element* temp = nouv_liste;
        for(int i = 1; i<n; i++){
            temp->next = creer_element_Int(i + 1);
            temp = temp->next;
        }
        return nouv_liste;
    }
}

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

// --------------------------------------------------------------
// Libération LSC D'entiers : version du cours.
void free_list(Element* liste){
    if (liste != NULL){
        free_list(liste->next);
        free(liste);
    }
}
