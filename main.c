#include <stdio.h>

int main()
{
    //Ouverture des fichiers
    FILE *fdat;
    fdat = fopen("VoiturierPlasschaert01.dat", "r");

    //Variables et délcaration de fonctions
    char menu[50];

    //Début du programme
    fgets(menu, 50, fdat);
    printf("%-50s", plat);
    printf("test");
}