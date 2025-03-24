/*
* ecran.h
* Contient toutes les fonctions pour interagir avec l'ecran modele
* NHD-0420D3Z-FL-GBW
*
* Auteur : Philippe Lefebvre
*/

#ifndef ECRAN_H
#define ECRAN_H

/***********Includes************/


/************Defines************/


/*********Declarations**********/
/*
* Fonction : ecranAllume
* Description : Envoie la commande pour allumer l'ecran
*
* Params : Aucun
* 
* Retour : Aucun
*/
void ecranAllume(void);

/*
* Fonction : ecranEteint
* Description : Envoie la commande pour eteindre l'ecran
*
* Params : Aucun
* 
* Retour : Aucun
*/
void ecranEteint(void);

/*
* Fonction : curseurPosition
* Description : Envoie la commande pour déplacer le curseur à la ligne et à la colonne demandé.
*
* Params : position
* 
* Retour : Aucun
*/
void curseurPosition(int position);

/*
* Fonction : videEcran
* Description : Envoie la commande pour vider l'écran.
*
* Params : Aucun
* 
* Retour : Aucun
*/
void videEcran(void);

/*
* Fonction : ecrireCaractere
* Description : Envoie la commande pour envoyer le caractère désiré.
*
* Params : caractere
* 
* Retour : Aucun
*/
void ecrireCaractere(char caractere);

void BR (char BaudRate);
#endif