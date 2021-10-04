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

// ***************************************************************
// FONCTIONS OUTILS pour la création de structure quelquonques d'entiers et de caractères.
typedef struct element{
    int dataInt;
    struct element* next;
}Element;

Element * creer_element_Int(int val);
Element * CreationLSC_Int();
Element* create_list(int n);
void display_list(Element* liste);
void free_list(Element* liste);