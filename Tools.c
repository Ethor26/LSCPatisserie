//
// Created by ethan on 04/10/2021.
//

#include "Tools.h"
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

char * ConvCharChaine(char c){ // transforme un caractère en chaine de caractères
    return ((char[2]) { c, '\0' });
}

// ***************************************************************
// FONCTIONS OUTILS pour la création et manipulation de LSC.

// - - - - Fonctions utilitaires

// ----------------------------------------
// FONCTION : Permet à l'utilisateur de choisir sa faim pour limiter le nombre de parts aléatoire possible.
int ChoixFaim(){
    int Faim;
    do{
        printf("Entrez 1 pour grande fin et 2 pour petite faim\n");
        LireInt(&Faim);
    }while(Faim != 1 && Faim != 2); // Saisie sécurisée de la faim
    if(Faim == 2)
        return 1 + rand() % 10; // Si petite faim, nombre de part entre 0 et 10
    else if(Faim == 1)
        return 1 + rand() % 50; // Si grande faim, nombre de part entre 0 et 50 (maximum de la chaine de gout)
    return 0;
}

// --------------------------------------------------------------
//FONCTION renvoyant 1 si les lettre d'une chaine de caractère font bien toutes partie de l'ensemble {CVFAPBM}, 0 sinon
int VerifGout(char com[]){
    char gouts[8] = "CVFAPBM";
    int check = 0;
    for(int i=0; i<strlen(com); i++){ // pour chaque lettre dans la CC com
        for(int j=0; j<7; j++){ // dans l'ensemble de lettre {CVFAPBM}
            if (com[i] == gouts[j]) check = 1; // si la lettre de com se trouve dans l'ensemble, on check 1
        }
        if (check == 0) return 0; // si check vaut 0, on a une lettre hors de l'ensemble, donc on retourne 0
    }
    return 1; // tout va bien, on retourns 1
}

// - - - - - Pour Structure de Element str

// --------------------------------------------------------------
// FONCTION OUTIL qui créée une LSC d'Element_str
Element_str* creer_list(char ch[50]){
    Element_str* list_g;
    list_g = (Element_str*) malloc(sizeof (Element_str));
    for (int i =0; i<= 50; i++) // on va copier la CC ch[50] dans list_g -> texte
        list_g -> texte[i] = ch[i];
    list_g -> next = NULL;
    return list_g;
}

// --------------------------------------------------------------
// FONCTION OUTIL qui ajoute une valeur à la fin de la LSC d'Element_str
void ajout_val_fin_rec(Element_str** ad_liste, char txt[50]){
    if (*ad_liste == NULL) {
        *ad_liste = creer_list(txt); // voir Tools.c
    } else {
        ajout_val_fin_rec(&((*ad_liste)->next), txt);
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL qui ajoute une valeur à la fin de la LSC d'Element_str
void ajout_val_deb(Element_str** ad_liste, char txt[50]){
    if (*ad_liste == NULL) {
        *ad_liste = creer_list(txt); // voir Tools.c
    } else {
        Element_str* nouvel_el = creer_list(txt);
        nouvel_el->next = *ad_liste; // on enregiste la position de la première chaine
        *ad_liste = nouvel_el; // on décale le tout
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL qui mesure la taille de la LSC d'Element_str
int nb_el(Element_str* list){
    int cpt = 0;
    while (list != NULL){ // on parcours la liste
        cpt++;
        list = list -> next;
    }
    return cpt; //on retourne le nombre de boucles
}

// --------------------------------------------------------------
// FONCTION OUTIL Affichage LSC de chaine de caractères.
void display_list(Element_str * liste){ // fonction recursive (cf cours)
    if (liste != NULL){
        printf("%s-->", liste->texte);
        display_list(liste->next);
    }
    else{
        printf("X\n");
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer LSC d'Element_str
void free_Element_str(Element_str* el){
    // Element_str * temp = el;
    while(el != NULL) { // on parcours la liste
        Element_str * old = el;
        el = el->next; // on save la place de l'élément suivant
        free(old); // on free l'element présent
    }
}

// - - - - - Pour Structure de Gateau

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer structure Gateau
void free_gateau(Gateau* G){
    if (G != NULL){
        free_Element_str(G->commande); // on free G->commande, voir Tools.c
        free_pile_gout(G->p_gouts);
        free(G);
    }
}

// - - - - - Pour Structure de Elemnet_gtx

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer structure Element_gtx
void free_Element_gtx(Element_gtx* G){
    while(G != NULL){
        Element_gtx * old = G;
        G = G->next;
        free_gateau(old->Gateau);
        free(old);
    }
}


// - - - - - Pour Structure de Pile Gout

// --------------------------------------------------------------
// FONCTION OUTIL : initialise la pile des gouts
Pile_Gouts* creer_pile_gout(){
    Pile_Gouts* nouv_pile = (Pile_Gouts*)malloc(sizeof(Pile_Gouts));
    nouv_pile->Gouts = NULL;
    return nouv_pile;
}

// --------------------------------------------------------------
// FONCTION OUTIL : vérifie si la pile des gouts est vide
int p_est_vide(Pile_Gouts* p){
        return (p->Gouts == NULL);
}

// --------------------------------------------------------------
// FONCTION OUTIL : dépile la pile des gouts d'un gateau
char * depiler_gouts(Pile_Gouts * p){
    if(p_est_vide(p) == 1){
        //GARGL
        return "\0";
    }
    else{
        char * res = p->Gouts->texte;
        Element_str * old = p->Gouts;
        p->Gouts = p->Gouts->next;
        free(old);
        return res;
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer LSC d'Element_str
void free_pile_gout(Pile_Gouts* PG){ // fonction recursive
    if (p_est_vide(PG)== 0){ // fonction qui renvoie 0 si PG est vide
        free_Element_str(PG->Gouts); // voir Tools.c ligne 161
    }
}

// - - - - - Pour Structure de File_commande

//---------------------------------------------------------------
// FONCTION OUTIL: Initialise la file de commandes.
File_Commandes * creer_file_Cmd(){
    File_Commandes * nouv_file = (File_Commandes*)malloc(sizeof(File_Commandes));
    nouv_file->commande = NULL;
    return nouv_file;
}

//---------------------------------------------------------------
// FONCTION OUTIL: Verifie si la liste de commande est vide.
int file_commande_vide(File_Commandes* f){
    if(f->commande == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer file de commande
void free_FILE_commande(File_Commandes* cmd){
    if (file_commande_vide(cmd) == 0){
        free_Element_str(cmd->commande);
    }
}

// - - - - - Pour Structure de File_Degustation

//---------------------------------------------------------------
// FONCTION OUTIL: Initialise la file de dégustations.
File_Degustation * creer_file_deg(){
    File_Degustation * nouv_file = (File_Degustation*)malloc(sizeof(File_Degustation));
    nouv_file->Gateaux = NULL;
    return nouv_file;
}

//---------------------------------------------------------------
// FONCTION OUTIL: Retourne la taille de la pile de gouts d'un gateau.
int taille_LSC_Gateau(Element_str * liste)
{
    if( liste == NULL){
        return 0;
    }
    else{
        return 1 + taille_LSC_Gateau(liste->next);
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Vérifie si la liste de dégustation est vide.
int fileDeg_est_vide(File_Degustation* f){
    if (f->Gateaux == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//---------------------------------------------------------------
// FONCTION OUTIL: Supprime un élément de la file de dégustation (le dernier) : ON ajoute au début et on supprime à la fin
void defiler_FileDeg(File_Degustation* f){
    if(fileDeg_est_vide(f) != 1){
        Element_gtx * temp = f->Gateaux;
        while(f->Gateaux->next != NULL)
            f->Gateaux = f->Gateaux->next;
        Element_gtx * old = f->Gateaux;
        f->Gateaux = f->Gateaux->next;
        free_Element_gtx(old);
        // Réinitialisation de f->Gateaux
        f->Gateaux = temp;
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer file de dégustation
void free_file_degustation(File_Degustation* D){
    if (fileDeg_est_vide(D) == 0){
        free_Element_gtx(D->Gateaux);
    }
}

// --------------------------------------------------------------
// FONCTION OUTIL : pour libérer file de dégustation
void free_list_Degust(File_Degustation* liste){
    while(fileDeg_est_vide(liste) != 1){
        defiler_FileDeg(liste);
    }
    free(liste);
}

