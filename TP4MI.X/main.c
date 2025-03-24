/**
 * Auteur 
 * Maxime Champagne
 * 3 mars 2022
 * 
 * Modifié par
 *
 *
 * SPI/main.c
 * 
*/
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "ecran.h"

#define MAX 60

// Enum pour tous les états que le code peut être.
enum{
    Selection,
    Triangle,
    Sinus,
    Carree
};

// Les valeurs pour que le potentiomètre crée une onde sinusoïdale.
uint8_t const sin[MAX] ={
              254,254,252,249,244,238,231,222,213,202,
              191,179,167,154,141,127,114,101,88,76,
              64,53,42,33,24,17,11,6,3,1,
              0,1,3,6,11,17,24,33,42,53,
              64,76,88,101,114,128,141,154,167,179,
              191,202,213,222,231,238,244,249,252,254};

// Les valeurs pour que le potentiomètre crée une onde carrée.
uint8_t const car[MAX] ={
             0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,0,0,
			  255,255,255,255,255,255,255,255,255,255,
			  255,255,255,255,255,255,255,255,255,255,
			  255,255,255,255,255,255,255,255,255,255};

// Les valeurs pour que le potentiomètre crée une onde triangulaire.
uint8_t const tri[MAX] ={
            9,17,26,34,43,51,60,68,77,85,
			 94,102,111,119,128,136,145,153,162,170,
			 179,187,196,204,213,221,230,238,247,255,
			 247,238,230,221,213,204,196,187,179,170,
			 162,153,145,136,128,119,111,102,94,86,
			 77,68,60,51,43,34,26,17,9,0};

// choix de fréquence dépendemment du chiffre désiré.
int frequence = 5;

// Pour changer le temps auquel le timer recommençera.
int reset = 0xFCBF;

// Valeur initiale de l'état
int Etat = Selection;

// Compteurs individuels pour les fonctions d'onde.
uint8_t TimerI = 0;
uint8_t Si = 0;
uint8_t Ti = 0;
uint8_t Ci = 0;

void out_dig(uint8_t x);
void sinus_60(void);
void triangle_60(void);
void carree_60(void);
void myTimer1_ISR(void);

/*
                         Main application
 */
void main(void)
{   
    int RxData = '0';
    
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(myTimer1_ISR);
    
    //????
    SSPCON1bits.SSPEN = 1;
    
    // S'assurer que le potentiomètre n'est pas utilisé tant qu'on ne le demande pas.
    IO_RA5_SetHigh();
    
    // Remise du potentiomètre à 0.
    out_dig(0);
    
    // Initiation de l'écran et de l'interface pour l'utilisateur.
    videEcran();
    curseurPosition(0x00);
    printf("Choisissez une onde");
    curseurPosition(0x14);
    printf("[S]in [T]ri [C]ar");
    
    while (1)
    {
        // Lecture du bouton appuyé sur le clavier.
        if (EUSART1_is_rx_ready())
        {
            RxData = EUSART1_Read();
        }
        
        // Machine à états pour la sélection d'onde.
        switch (Etat)
        {
            case Selection:
                
                if(RxData == 's')
                {
                    Etat = Sinus;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Sinus");
                    curseurPosition(0x14);
                    printf("[T]ri [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 't')
                {
                    Etat = Triangle;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Triangle");
                    curseurPosition(0x14);
                    printf("[S]in [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'c')
                {
                    Etat = Carree;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Carree");
                    curseurPosition(0x14);
                    printf("[T]ri [S]in [R]etour");
                    RxData = '0';
                }
                break;
            
            case Sinus:
                
                if(RxData == 't')
                {
                    Etat = Triangle;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Triangle");
                    curseurPosition(0x14);
                    printf("[S]in [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'c')
                {
                    Etat = Carree;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Carree");
                    curseurPosition(0x14);
                    printf("[T]ri [S]in [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'r')
                {
                    Etat = Selection;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Choisissez une onde");
                    curseurPosition(0x14);
                    printf("[S]in [T]ri [C]ar");
                    RxData = '0';
                    out_dig(0);
                }
                break;
                
            case Triangle:
                
                if(RxData == 's')
                {
                    Etat = Sinus;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Sinus");
                    curseurPosition(0x14);
                    printf("[T]ri [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'c')
                {
                    Etat = Carree;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Carree");
                    curseurPosition(0x14);
                    printf("[T]ri [S]in [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'r')
                {
                    Etat = Selection;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Choisissez une onde");
                    curseurPosition(0x14);
                    printf("[S]in [T]ri [C]ar");
                    RxData = '0';
                    out_dig(0);
                }
                break;
                
            case Carree:
                
                if(RxData == 's')
                {
                    Etat = Sinus;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Sinus");
                    curseurPosition(0x14);
                    printf("[T]ri [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 't')
                {
                    Etat = Triangle;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Onde: Triangle");
                    curseurPosition(0x14);
                    printf("[S]in [C]ar [R]etour");
                    RxData = '0';
                }
                else if(RxData == 'r')
                {
                    Etat = Selection;
                    videEcran();
                    curseurPosition(0x00);
                    printf("Choisissez une onde");
                    curseurPosition(0x14);
                    printf("[S]in [T]ri [C]ar");
                    RxData = '0';
                    out_dig(0);
                }
                break;
        }
        
        // Changement de la fréquence + ou -
        if(Etat != Selection)
        {
            if(RxData == '+')
            {
                if (frequence > 1)
                {
                    frequence -= 1;
                    RxData = '0';
                }
            }
            else if(RxData == '-')
            {
                if (frequence < 5)
                {
                    frequence += 1;
                    RxData = '0';
                }
            }
        }
        
        // Choix du temps auquel le timer recommençera pour avoir la fréquence désirée.
        switch (frequence)
        {
            case 1:
                // 100Hz
                reset = 0xF2FB;
                break;
            case 2:
                // 80Hz
                reset = 0xEFB9;
                break;
            case 3:
                // 60Hz
                reset = 0xEA4C;
                break;
            case 4:
                // 40Hz
                reset = 0xDF73;
                break;
            case 5:
                // 20Hz
                reset = 0xBEE5;
                break;
        }
        
    }

           
}

//---------------------------------------------------------------
// Routine d'interruption du Timer1
//---------------------------------------------------------------
void myTimer1_ISR(void){
    TMR1_WriteTimer(reset);
    switch (Etat)
    {
        case Sinus:
            sinus_60();
            break;
        case Triangle:
            triangle_60();
            break;
        case Carree:
            carree_60();
            break;
    }
}
    
//----------------------------------------------------------------
// Transmission au pot. d'une onde comprenant 60 points par cycle.
//----------------------------------------------------------------
void sinus_60(void) {
    out_dig(sin[Si]);
    Si++;
    if(Si == MAX)
    {
        Si = 0;
    }
}

//----------------------------------------------------------------
// Transmission au pot. d'une onde comprenant 60 points par cycle.
//----------------------------------------------------------------
void triangle_60(void) {
    out_dig(tri[Ti]);
    Ti++;
    if(Ti == MAX)
    {
        Ti = 0;
    }
}

//----------------------------------------------------------------
// Transmission au pot. d'une onde comprenant 60 points par cycle.
//----------------------------------------------------------------
void carree_60(void) {
    out_dig(car[Ci]);
    Ci++;
    if(Ci == MAX)
    {
        Ci = 0;
    }
}


//----------------------------------------------------------------
//  Transmission d'une donnee a la sortie du pot. numerique
//----------------------------------------------------------------
void out_dig(uint8_t x)
{
	IO_RA5_SetLow();   // selection du potentiometre
	SPI_ExchangeByte(0x11);  // ecriture, pot. 0
	SPI_ExchangeByte(x);
	IO_RA5_SetHigh();
	//__delay_ms(1);
}
