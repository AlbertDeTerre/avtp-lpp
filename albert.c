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
<<<<<<< HEAD
    FILE *fboisson, *fmenu, *fboi, *fpersonnel, *fhoraire;
    fboisson = fopen("tables.dat", "r");
    fmenu = fopen("menu.dat", "r");
    fboi = fopen("boisson.dat", "r");
    fpersonnel = fopen("personnel.dat", "r");
    fhoraire = fopen("horaire.dat", "r");
    
    //Déclaration des fonctions et variables;
    int running = 1;
    table *tdeb, *bcourant;
=======
    FILE *ftab, *fmenu, *fboi, *fpersonnel, *fhoraire;
    
    //Déclaration des fonctions et variables;
    int running = 1, identification();
    void reservation(table*);
    table *tdeb, *tcourant;
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371
    personnel *pdeb, *pcourant;
    table * lectureTable();
    personnel * lecturePersonnel();
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    bcourant = lectureTable();
    pcourant = lecturePersonnel();

    //Si la personne s'identifie bien, on rentre dans la boucle, sinon one ne rentre pas dedans
    running = identification();

    while (running == 1)
    {
        int option;
        printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 0: QUITTER)\n");
        scanf("%d", &option);

        while (option != 1 && option != 2 && option != 0){
            printf("Que voulez vous faire ? (1: RESERVATION | 2: COMMANDE | AUTRE: QUITTER)\n");
            scanf("%d", &option);
        }

        //L'utilisateur veut encoder une réservation
        if(option == 1){
            reservation(tcourant);

        //L'utilisateur veut encoder une commande
        }else if(option == 2){
            

        //L'utilisateur veut quitter le programme
        }else{
            break;
        }
        
        running = 0;
    }

    printf("\n\n** FIN DU PROGRAMME **\n");
}

table * lectureTable(){

    //Ouverture du fichier qui va être lu ("table.dat")
<<<<<<< HEAD
    FILE *fboisson;
    fboisson = fopen("tables.dat", "r");
=======
    FILE *ftab;
    ftab = fopen("VoiturierPlasschaertTables.dat", "r");
    int num;
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371

    //Déclaration des différentes structures
    table *tdeb, *bcourant, *bsuivant;

    //Lecture du fichier et affectation des différentes valeurs lues dans les variables de la structure table
<<<<<<< HEAD
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
=======
    tcourant = malloc(sizeof(table));
    tdeb = tcourant;
    fscanf(ftab, "%2d", &num);

    //Commencement de la boucle de lecture
    while (!feof(ftab)){ 
        tcourant->num = num;      
        fscanf(ftab, "%2d", &tcourant->nbPersonnes);
        tsuivant = malloc(sizeof(table));
        tcourant->suivant = tsuivant;
        tcourant = tsuivant;
        fscanf(ftab, "%2d", &num);
    }
    tcourant = NULL;
    return tdeb;
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371
}

personnel * lecturePersonnel(){
    //Ouverture du fichier
    FILE *fpers;
    fpers = fopen("VoiturierPlasschaertPersonnel.dat", "r");

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
    courant = NULL;
    return deb;
}

int identification(){

    //Déclaration des variables ainsi que du fichier
    int matricule, matEmp;
    char prenom[21];
    FILE *fdat = fopen("VoiturierPlasschaertPersonnel.dat", "r");

    //Demande le numéro de matricule de l'utilisateur pour qu'il s'identifie
    printf("Entrez votre matricule: ");
    scanf("%3d", &matricule);

    //Parcours la liste des utilisateurs pour voir si la personne a entré un bon matricule
    fscanf(fdat, "%3d", &matEmp);
    while (!feof(fdat)){
        fscanf(fdat, "%20s", prenom);
        //Compare les deux matricules
        if (matEmp == matricule){
            printf("\n** IDENTIFICATION REUSSIE ! **\n");
            printf("Bienvenue dans le programme %-20s", prenom);
            return 1;
        }
        fscanf(fdat, "%3d", &matEmp);
    }

    //Si le test entre les deux matricule échoue
    printf("\n!! Identification échouée !!\n");
    return 0;
}

void reservation(table * courant){

    //Ouverture des fichiers nécéssaires
<<<<<<< HEAD
    FILE *fres, *fboissonles;
    fres = fopen("reservation.res", "w");
    fboissonles = fopen("tables.dat", "r");
=======
    FILE *fres, *fdat, *fjours;
    fjours = fopen("VoiturierPlasschaertJours.dat", "r");
    fres = fopen("VoiturierPlasschaertReservations.res", "a");
    fdat = fopen("VoiturierPlasschaertReservations.res", "r");
    table *deb, *tableChoisie, *table;
    int reservations[8][50], existe = 0;
    char jours[8][10];

    //Initialise le vecteur comprenant chaque jours de la semaine
    for (int i = 1; i <= 7; i++){
        fscanf(fjours, "%10s", jours[i]);
    }
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371

    //Déclaration des variables
    int nbPersonnes, persTable, numTable, min = 999999, nbTables;
    char jour[10], jourFichier[10];

    //Demande à l'utilisateur pour combien de personne le client à reserver
    printf("\nJour de la réservation: ");
    scanf("%9s", jour);

<<<<<<< HEAD
    //Rechercher parmis les tables
    fscanf(fboissonles, "%2d %2d", &numTable, &persTable);
    while (!feof(fboissonles)){
=======
    while(existe == 0){
        printf("\nCe jour n'existe pas !\nJour de la réservation: ");
        scanf("%9s", jour);
        for (int i = 1; i <= 7; i++){
            if (strcmp(jours[i], jour) == 0){
                if (i == 1){
                    printf ("\nPas de service le LUNDI !");
                }else{
                    existe = 1;
                    break;
                }
            }
        }
    }
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371


    printf("\nNombre de personnes: ");
    scanf("%2d", &nbPersonnes);

    //On parcours le fichier des reservations a la recherche du jours choisi
    for (int i = 1; i <= 7; i++){
        fscanf(fdat, "%10s %2d", &jourFichier, &nbTables);

        //Compare si le jour entré par l'utilisateur = celui lu dans le fichier
        if (strcmp(toupper(jourFichier), toupper(jour)) == 0){
            for (int i = 0; i < nbTables; i++){
                fscanf(fdat, "%2d", &numTable);
                
                if ((courant->nbPersonnes >= nbPersonnes) && (courant->nbPersonnes < min)){
                    
                    min = courant->nbPersonnes;
                    tableChoisie = courant;
                 }

            }
        }

<<<<<<< HEAD
        fscanf(fboissonles, "%2d %2d", &numTable, &persTable);
    }
}
=======
    }

    //Rechercher parmis les tables
    deb = courant;
    while (courant != NULL){
        if ((courant->nbPersonnes >= nbPersonnes) && (courant->nbPersonnes < min)){
            min = courant->nbPersonnes;
            tableChoisie = courant;
        }

        courant = courant->suivant;
    }

    if (min == 999){

    }

    printf("\nTable choisie: %2d", tableChoisie->num);

}
>>>>>>> 5565da5b5a61f6a719a71192a2f40f906e72c371
