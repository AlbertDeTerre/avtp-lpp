#include <stdio.h>

int main()
{
    //Ouverture des fichiers
    FILE *fdat;
    fdat = fopen("plats.dat", "r");

    //Variables et délcaration de fonctions
    int num;
    char plat[50];

    
    fscanf(fdat, "%2d", &num);
    fgets(plat, 50, fdat);
    printf("%-50s", plat);
}
