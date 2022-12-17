#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
    
    //Déclaration des fonctions et variables;
    int running = 1, identification();
    void reservation(table*);
    table *tdeb, *tcourant;
    personnel *pdeb, *pcourant;
    table * lectureTable();
    personnel * lecturePersonnel();
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();

    //Si la personne s'identifie bien, on rentre dans la boucle, sinon one ne rentre pas dedans
    running = identification();

    while (running == 1)
    {
        int option = 3;
        printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | AUTRE: QUITTER)\n");
        scanf("%d", &option);

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

    printf("\n** FIN DU PROGRAMME **\n");
}

table * lectureTable(){

    //Ouverture du fichier qui va être lu ("table.dat")
    FILE *ftab;
    ftab = fopen("VoiturierPlasschaertTables.dat", "r");
    int num, n = 0;

    //Déclaration des différentes structures
    table *tdeb, *tcourant, *tsuivant;

    //Lecture du fichier et affectation des différentes valeurs lues dans les variables de la structure table
    tcourant = malloc(sizeof(table));
    tdeb = tcourant;
    fscanf(ftab, "%2d", &num);

    //Commencement de la boucle de lecture
    while (!feof(ftab)){ 
        n++;
        tcourant->num = num;      
        fscanf(ftab, "%2d", &tcourant->nbPersonnes);
        tsuivant = malloc(sizeof(table));
        tcourant->suivant = tsuivant;
        tcourant = tsuivant;
        fscanf(ftab, "%2d", &num);
    }

    tcourant = tdeb;
    for (int i = 0; i < n; i++){
        tcourant = tcourant->suivant;
    }
    tcourant->suivant = NULL;

    return tdeb;
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
    FILE *fres, *fdat, *fjours;
    fjours = fopen("VoiturierPlasschaertJours.dat", "r");
    fres = fopen("VoiturierPlasschaertReservations.res", "a");
    fdat = fopen("VoiturierPlasschaertReservations.res", "r");
    table *deb, *tableChoisie, *table;
    int reservations[8][50], existe = 0;
    char jours[8][10];

    //Déclaration des variables
    int nbPersonnes = 999999, numTableChoisie = 0, min = 999999, tablesRes[50], nbTablesRes, resReussie = 0;
    char jour[10], jourFichier[10];

    //Demande à l'utilisateur pour combien de personne le client à reserver
    printf("\nJour de la réservation: ");
    scanf("%9s", jour);

    for (int i = 0; i < 10; i++){
        if (jour[i] == '\0'){
            break;
        }
        jour[i] = toupper(jour[i]);
    }

    //Initialise le vecteur comprenant chaque jours de la semaine
    for (int i = 1; i <= 7; i++){
        fscanf(fjours, "%10s", jours[i]);

        if (strcmp(jours[i], jour) == 0){
            existe = 1;
        }
    }

    //SI le jour est lundi
    if (strcmp(jour, "LUNDI") == 0){
        printf("\nLe restaurant n'est pas ouvert le lundi !");
        existe = 0;
    }

    while (existe == 0)
    {
        //Demande le jour de la réservation;
        printf("\nJour de la réservation: ");
        scanf("%9s", jour);

        //Met le jour en MAJ
        for (int i = 0; i < 10; i++){
            if (jour[i] == '\0'){
                break;
            }
            jour[i] = toupper(jour[i]);
        }

        //Série de test pour voir si le jour est OK
        for (int i = 1; i <= 7; i++){
            if (strcmp(jours[i], jour) == 0){
                if (strcmp((jour), "LUNDI") == 0){
                    printf("\nLe restaurant n'est pas ouvert le lundi !");
                    break;
                }

                existe = 1;
            }
        }
    }
    
    //Demande le nombre de personnes
    printf("\nNombre de personnes: ");
    scanf("%2d", &nbPersonnes);

    //Initialisation d'un liste des tables déjà réservées le jour voulu
    for (int i = 1; i <= 7; i++){
        fscanf(fdat, "%9s", jours[i]);

        if (strcmp(jours[i], jour) == 0){
            fscanf(fdat, "%2d", &nbTablesRes);
            for (int j = 0; j < nbTablesRes; j++){
                fscanf(fdat, "%2d", &tablesRes[j]);
            }
            break;
        }else{
            fscanf(fdat, "%*[^\n]\n");
        }
    }

    //Parcours la liste de des tables a la recherche d'une table assez grande et regarde si elle est déjà prise
    while(courant->suivant != NULL){
        int reservee = 0;
        for (int i = 0; i < nbTablesRes; i++){
            if (tablesRes[i] == courant->num){
                reservee = 1;
                break;
            }
        }
        //La variable min sert à essayer d'optimiser le nombre de personne par table pour ne pas donner une table trop grande à un groupe
        if (reservee == 0 && courant->nbPersonnes >= nbPersonnes && courant->nbPersonnes < min){
            resReussie = 1;
            min = courant->nbPersonnes;
            numTableChoisie = courant->num;
            if (courant->nbPersonnes == nbPersonnes){
                break;
            }
        }
        courant = courant->suivant;
    }

    int reserverPlat = 2;

    //Demande si l'utilisateur veut réserver les plats à l'avance
    printf("\nLe plat à t il été réservé à l'avance ? (1: OUI | 0:NON)\n");
    scanf("%d", &reserverPlat);

    while (reserverPlat != 0 && reserverPlat != 1){
        printf("\nVoulez vous réserver un plat à l'avance ? (1: OUI | 0:NON)\n");
        scanf("%d", &reserverPlat);
    }

    if (reserverPlat == 0){
        return;
    }



}