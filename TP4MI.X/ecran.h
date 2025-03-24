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
* Description : Envoie la commande pour d�placer le curseur � la ligne et � la colonne demand�.
*
* Params : position
* 
* Retour : Aucun
*/
void curseurPosition(int position);

/*
* Fonction : videEcran
* Description : Envoie la commande pour vider l'�cran.
*
* Params : Aucun
* 
* Retour : Aucun
*/
void videEcran(void);

/*
* Fonction : ecrireCaractere
* Description : Envoie la commande pour envoyer le caract�re d�sir�.
*
* Params : caractere
* 
* Retour : Aucun
*/
void ecrireCaractere(char caractere);

void BR (char BaudRate);
#endif