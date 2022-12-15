#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structure table
typedef struct table{
    int num;                    //Numéro de la table
    int nbPersonnes;            //Nombre de personnes pouvant être à cette table
    struct table *suivant;      //Client suivant de la liste chainée
}table;

//Structure personnel
typedef struct personnel{
    int matricule;              //Matricule du membre du personnel
    char prenom[21];            //Prenom du membre du personnel
    char fonction[21];          //Fonction du membre du personnel (cuisinier, serveur, ...)
    struct personnel *suivant;
}personnel;

int main()
{
    //Ouverture des fichiers
    FILE *ftab, *fmenu, *fboi, *fpersonnel, *fhoraire;
    ftab = fopen("tables.dat", "r");
    fmenu = fopen("menu.dat", "r");
    fboi = fopen("boisson.dat", "r");
    fpersonnel = fopen("personnel.dat", "r");
    fhoraire = fopen("horaire.dat", "r");
    
    //Déclaration des fonctions et variables;
    int running = 1;
    table *tdeb, *tcourant;
    personnel *pdeb, *pcourant;
    table * lectureTable();
    personnel * lecturePersonnel();
    

    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();

    pdeb = pcourant;
    while (pcourant->suivant != NULL){
        printf("03d %20s %20s\n", pcourant->matricule, pcourant->prenom, pcourant->fonction);
        pcourant = pcourant->suivant;
    }


    // while (running == 1)
    // {

    // }
}

table * lectureTable(){

    //Ouverture du fichier qui va être lu ("table.dat")
    FILE *ftab;
    ftab = fopen("tables.dat", "r");

    //Déclaration des différentes structures
    table *tdeb, *tcourant, *tsuivant;

    //Lecture du fichier et affectation des différentes valeurs lues dans les variables de la structure table
    tcourant = malloc(sizeof(table));
    tdeb = tcourant;
    fscanf(ftab, "%2d", &tcourant->num);

    //Commencement de la boucle de lecture
    while (!feof(ftab)){       
        fscanf(ftab, "%2d", &tcourant->nbPersonnes);
        
        tsuivant = malloc(sizeof(table));
        tcourant->suivant = tsuivant;
        tcourant = tsuivant;
        fscanf(ftab, "%2d", &tcourant->num);
    }
    //affectation de la premiere structure de la liste à tcourant
    tcourant = tdeb;

    return tcourant;
}

personnel * lecturePersonnel(){
    //Ouverture du fichier
    FILE *fpers;
    fpers = fopen("personnel.dat", "r");

    //Declaration des structures
    int mat;
    personnel *deb, *courant, *suivant;
    courant = malloc(sizeof(personnel));
    deb = courant;

    //TODO : BOUCLE DE LECTURE ET AFFECTATIONS
    fscanf(fpers, "%3d", &mat);
    while(!feof(fpers)){
        courant->matricule = mat;
        fscanf(fpers, "%20s %20s", courant->prenom, courant->fonction);
        suivant = malloc(sizeof(personnel));
        courant->suivant = suivant;
        courant = suivant;
        fscanf(fpers, "%3d", &mat);
    }
    
    courant = deb;
    return courant;
}

void identification(){
    
    int matricule;
    FILE *fdat = fopen("VoiturierPlasschaertPersonnel.dat", "r");

    printf("Entrez votre matricule: ");
    scanf("%3d", &matricule);

    while (!feof(fdat)){
        
    }
}

void reservation(){
    //Ouverture des fichiers nécéssaires
    FILE *fres, *ftables;
    fres = fopen("reservation.res", "w");
    ftables = fopen("tables.dat", "r");

    //Déclaration des variables
    int nbPersonne, persTable, numTable;
    char jour[10];

    //Demande à l'utilisateur pour combien de personne le client à reserver
    printf("Jour de la réservation: ");
    scanf("%9s", jour);
    printf("Nombre de personnes: ");
    scanf("%2d", &nbPersonne);

    //Rechercher parmis les tables
    fscanf(ftables, "%2d %2d", &numTable, &persTable);
    while (!feof(ftables)){

        if (persTable >= nbPersonne){
            
        }

        fscanf(ftables, "%2d %2d", &numTable, &persTable);
    }
}