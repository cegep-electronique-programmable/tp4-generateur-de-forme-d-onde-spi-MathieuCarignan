#include "ecran.h"
#include "mcc_generated_files/eusart1.h"
//#include"mcc_generated_files/eusart2.h"

void ecranAllume(void)
{
    EUSART1_Write(0xFE);
    EUSART1_Write(0x41);
}

void ecranEteint(void)
{
    EUSART1_Write(0xFE);
    EUSART1_Write(0x42);
}

void curseurPosition(int position)
{
    EUSART1_Write(0xFE);
    EUSART1_Write(0x45);
    EUSART1_Write(position);
}
void videEcran(void)
{
    EUSART1_Write(0xFE);
    EUSART1_Write(0x51);
}

void ecrireCaractere(char caractere)
{
    EUSART1_Write(caractere);
}

void BR (char BaudRate)
{
    EUSART1_Write(0xFE);
    EUSART1_Write(0x61);
    EUSART1_Write(BaudRate);
}