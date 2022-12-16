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
    FILE *fboisson, *fmenu, *fboi, *fpersonnel, *fhoraire;
    fboisson = fopen("tables.dat", "r");
    fmenu = fopen("menu.dat", "r");
    fboi = fopen("boisson.dat", "r");
    fpersonnel = fopen("personnel.dat", "r");
    fhoraire = fopen("horaire.dat", "r");
    
    //Déclaration des fonctions et variables;
    int running = 1;
    table *tdeb, *bcourant;
    personnel *pdeb, *pcourant;
    table * lectureTable();
    personnel * lecturePersonnel();
    

    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    bcourant = lectureTable();
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
    FILE *fboisson;
    fboisson = fopen("tables.dat", "r");

    //Déclaration des différentes structures
    table *tdeb, *bcourant, *bsuivant;

    //Lecture du fichier et affectation des différentes valeurs lues dans les variables de la structure table
    bcourant = malloc(sizeof(table));
    tdeb = bcourant;
    fscanf(fboisson, "%2d", &bcourant->num);

    //Commencement de la boucle de lecture
    while (!feof(fboisson)){       
        fscanf(fboisson, "%2d", &bcourant->nbPersonnes);
        
        bsuivant = malloc(sizeof(table));
        bcourant->suivant = bsuivant;
        bcourant = bsuivant;
        fscanf(fboisson, "%2d", &bcourant->num);
    }
    //affectation de la premiere structure de la liste à bcourant
    bcourant = tdeb;

    return bcourant;
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
    FILE *fres, *fboissonles;
    fres = fopen("reservation.res", "w");
    fboissonles = fopen("tables.dat", "r");

    //Déclaration des variables
    int nbPersonne, persTable, numTable;
    char jour[10];

    //Demande à l'utilisateur pour combien de personne le client à reserver
    printf("Jour de la réservation: ");
    scanf("%9s", jour);
    printf("Nombre de personnes: ");
    scanf("%2d", &nbPersonne);

    //Rechercher parmis les tables
    fscanf(fboissonles, "%2d %2d", &numTable, &persTable);
    while (!feof(fboissonles)){

        if (persTable >= nbPersonne){
            
        }

        fscanf(fboissonles, "%2d %2d", &numTable, &persTable);
    }
}
