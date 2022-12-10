#include <stdio.h>

int main()
{
    //Ouverture des fichiers
    FILE *fdat;
    fdat = fopen("menu.dat", "r");

    //Variables et délcaration de fonctions
    char menu[51];

    //Début du programme
    fscanf(fdat, "%5Os", menu);
    printf("%-50s", menu);
}