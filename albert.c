#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct reservation{
    char date[11];
    int nbtables;
    int jour;
    int mois;
    int annee;
    int tables[50];
    struct reservation *suivant;
}reservation;

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
    int running = 1, identification(), jourSemaine(int, int, int), jourExiste(int, int, int, int, int, int);
    void reserver(table*), ajouterPersonnel(), supprimerPersonnel(), afficherPersonnel();
    void annulerReservation(), afficherReservations();
    table *tdeb, *tcourant;
    personnel *pcourant, *pdeb;
    
    table * lectureTable();
    personnel * lecturePersonnel();
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();
    pdeb = pcourant;
    tdeb = tcourant;

    //Si la personne s'identifie bien, on rentre dans la boucle, sinon one ne rentre pas dedans
    running = identification();

    //Si c'est le gérant -> menu admin
    if (running == 999){
        running = 1;
        while (running == 1)
        {
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 3: PERSONNEL | AUTRE: QUITTER)\n");
            scanf("%d", &option);

            //L'utilisateur veut encoder une réservation
            if(option == 1){
                printf("CHOISISSEZ UNE OPTION: (1: AJOUTER UNE RESERVATION | 2: ANNULER UNE RESERVATION | 3: AFFICHER | AUTRE: QUITTER)\n");
                scanf("%2d", &option);
                if (option == 1){
                    reserver(tdeb);
                }else if (option == 2){
                    annulerReservation();
                }else if (option == 3){
                    afficherReservations();
                }

            //L'utilisateur veut encoder une commande
            }else if(option == 2){

            //L'utilisateur veut changer le personnel;
            }else if(option == 3){
                printf("CHOISISSEZ UNE OPTION: (1: AJOUTER UN EMPLOYER | 2: LISTE DES EMPLOYES)\n");
                scanf("%d", &option);
                if (option == 1){
                    ajouterPersonnel();
                }else if(option == 2){
                    supprimerPersonnel();
                }else if(option == 3){
                    afficherPersonnel();
                }
            //L'utilisateur veut quitter le prog
            }else{
                break;
            }
        }
    //Si ce n'est qu'un simple employé -> menu employé 
    }else if (running > 0){
        running = 1;
        while (running == 1)
        {
            
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | AUTRE: QUITTER)\n");
            scanf("%d", &option);

            //L'utilisateur veut encoder une réservation
            if(option == 1){
                printf("1: AJOUTER UNE RESERVATION | 2: ANNULER UNE RESERVATION | AUTRE: QUITTER\n");
                scanf("%2d", &option);
                if (option == 1){
                    // reservation(tcourant);
                }else if (option == 2){
                    // annulerReservation();
                }

            //L'utilisateur veut encoder une commande
            }else if(option == 2){


            //L'utilisateur veut quitter le programme
            }else{
                break;
            }
        }
    }
    
    printf("\n** FIN DU PROGRAMME **\n");
}

// ------------------------- RECUPERE LA LISTE CHAINEE DES TABLES ---------------------------
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

// ----------------------- RECUPERE LA LISTE CHAINEE DES MEMBRES DU PERSONNEL --------------------------
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
    fclose(fpers);
    return deb;
}

// ----------------------------------------- IDENTIFICATION -----------------------------------------------
int identification(){
    //Déclaration des variables ainsi que du fichier
    int matricule, matEmp;
    char prenom[21];
    FILE *fdat = fopen("VoiturierPlasschaertPersonnel.dat", "r");

    //Demande le numéro de matricule de l'utilisateur pour qu'il s'identifie
    printf("Entrez votre matricule: ");
    scanf("%3d", &matricule);

    //Si le matricule entré est 0 --> retourne 0 pour quitter la boucle du main
    if (matricule == 0)
    {
        return 0;
    }
    

    //Parcours la liste des utilisateurs pour voir si la personne a entré un bon matricule
    fscanf(fdat, "%3d", &matEmp);
    while (!feof(fdat)){
        fscanf(fdat, "%20s", prenom);
        //Compare les deux matricules
        if (matEmp == matricule){
            printf("\n** IDENTIFICATION REUSSIE ! **\n");
            printf("Bienvenue dans le programme %-20s", prenom);
            return matricule;
        }
        fscanf(fdat, "%3d", &matEmp);
    }

    //Si le test entre les deux matricule échoue
    printf("\n!! Identification échouée !!\n");
    fclose(fdat);
    return -1;
}

// ----------------------------------------- AFFICHER LES RESERVATIONS ------------------------------------
void afficherReservations(){
    FILE *fdat, *fres;
    fdat = fopen("VoiturierPlasschaertReservations.dat", "r");
    reservation * lectureReservations();
    //Variables utile pour récupérer la date du jour
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Date d'aujourd'hui
    int jourAuj = tm.tm_mday;
    int moisAuj = tm.tm_mon + 1;
    int anneeAuj = tm.tm_year + 1900;
    int jourExiste(int, int, int, int, int, int);

    //On check si le fichier est vide
    int c = fgetc(fdat), vide;
    if (c == EOF){
        vide = 1;
    }else{
        vide = 0;
        ungetc(c, fdat);
    }

    //Fermer le fichier
    fclose(fdat);

    //Si le fichier est vide on arrete l'annulation de la reservation
    if (vide == 1){
        printf("\n!! IMPOSSIBLE D'AFFICHER LES RESERVATIONS CAR IL N'Y EN A AUCUNE !!\n");
        return;
    }

    reservation *courant, *deb;
    courant = lectureReservations();
    deb = courant;

    //On parcourt la liste des reservations
    printf("                    RESERVATIONS                      \n");
    printf("=====================================================\n");
    printf("DATES        | TABLES RESERVEES\n");
    while(courant->suivant != NULL){
        if (jourExiste(courant->jour, courant->mois, courant->annee, anneeAuj, moisAuj, jourAuj) == 1){
            printf("-------------|---------------------------------------\n");
            printf("%-10s   ", courant->date);
            for (int i = 0; i < courant->nbtables; i++){
                printf("| %02d ", courant->tables[i]);
            }
            printf("\n");
        }
        courant = courant->suivant;
    }
    printf("=====================================================\n");

}



// ----------------------------------------- AJOUTE UN EMPLOYE -------------------------------------------

void ajouterPersonnel(){

    FILE *fres;
    personnel * lecturePersonnel();

    personnel *courant, *deb, *intercale;
    courant = lecturePersonnel();
    deb = courant;

    int fonction;
    char prenom[21];

    //Demande le type d'employé à ajouter
    printf("\nType d'employé: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
    scanf("%d", &fonction);

    while (!(fonction == 1 || fonction == 2 || fonction == 3)){
        printf("\nType d'employé: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
        scanf("%d", &fonction);
    }

    //Demande le prénom de l'employé à ajouter
    printf("\nPrénom du nouvel employé: ");
    scanf("%20s", prenom);
    int nbEmpFonction[4];

    for (int i = 1; i <=3; i++){
        nbEmpFonction[i] = 0;
    }

    while(courant->suivant != NULL){
        nbEmpFonction[courant->matricule / 100] ++;
        courant = courant->suivant;
    }
    
    fres = fopen("VoiturierPlasschaertPersonnel.dat", "w");

    //Stockage des différentes fonctions ous forme de string
    char fonctions[4][21];
    strcpy(fonctions[1], "GERANT");
    strcpy(fonctions[2], "CUISINIER");
    strcpy(fonctions[3], "SERVEUR");


    int count = 0, nbEmp = 0, matPrecedent = 0;
    courant = deb;
    intercale = malloc(sizeof(personnel));
    //Parcourt la liste des employés
    while(courant->suivant != NULL){
        //Si l'employé courant a la fonction de l'employé que l'on veut ajouter
        if(courant->matricule / 100 == fonction){
            count++;
            //Si on est a l'employé recherché
            if(count == nbEmpFonction[courant->matricule / 100]){
                intercale->suivant = courant->suivant;
                courant->suivant = intercale;
                strcpy(courant->suivant->fonction, courant->fonction);
                strcpy(courant->suivant->prenom, prenom);
                courant->suivant->matricule = courant->matricule + 1;
            }
        //S'il n'y pas encore d'employé dans la section qu'on ajoute ou si le fichier ne contient que le gérant
        }else if((courant->matricule == 999 && (courant->suivant == NULL || courant->suivant->matricule / 100 > fonction)) || (courant->matricule != 999 && courant->suivant->matricule / 100 > 1 + courant->matricule / 100 && fonction == 1 + courant->matricule / 100)){
            intercale->suivant = courant->suivant;
            courant->suivant = intercale;
            strcpy(courant->suivant->fonction, fonctions[fonction]);
            strcpy(courant->suivant->prenom, prenom);
            courant->suivant->matricule = fonction * 100 + 1;
        }
        fprintf(fres, "%03d %-20s %-20s\n", courant->matricule, courant->prenom, courant->fonction);
        matPrecedent = courant->matricule;
        courant = courant->suivant;
    }
    fclose(fres);
}

// -------------------------------- SUPPRIME UN EMPLOYE -------------------------------------
void supprimerPersonnel(){
    
    FILE *fres;
    personnel * lecturePersonnel();
    
    //Liste d'employés
    personnel *courant, *deb, *intercale;
    intercale = malloc(sizeof(personnel));
    courant = lecturePersonnel();
    deb = courant;

    int fonction, present = 0, mat;
    char prenom[21];

    //Demande l'employé a supprimer
    printf("Matricule de l'employé à supprimer: ");
    scanf("%d", &mat);
    if (mat <=0){
    	return;
	}

    fres = fopen("VoiturierPlasschaertPersonnel.dat", "w");

    //On parcourt la liste des employés
    while (courant->suivant != NULL){
        //Si l'employé courant est celui qu'on veut supprimer, on le supprime
        if (courant->suivant->matricule == mat){
            present = 1;
            intercale = courant->suivant->suivant;
            courant->suivant = intercale;
        }

        fprintf(fres, "%03d %-20s %-20s\n", courant->matricule, courant->prenom, courant->fonction);
        courant = courant->suivant;
    }

    //Si l'employé n'existe pas
    if (present != 1){
        printf("\n!!CET EMPLOYE N'EXISTE PAS!!\n");
    }
    fclose(fres);
}

// ---------------------------------- AFFICHE LA LISTE DES EMPLOYES ----------------------------------
void afficherPersonnel(){
    personnel *deb, *courant;
    personnel * lecturePersonnel();
    courant = lecturePersonnel();
    deb = courant;
    char tmpfonc[21] = "";

    while(courant->suivant != NULL){
        if (strcmp(tmpfonc, courant->fonction) != 0){
            strcpy(tmpfonc, courant->fonction);
            printf("\n%-20s\n=========================================\n", tmpfonc);
        }

        printf("    Matricule: %03d - Prénom: %-20s\n", courant->matricule, courant->prenom);
        courant = courant->suivant;
    }
}

// ---------------------- RECUPERE TOUTES LES RESERVATIONS SOUS FORME DE LISTE CHAINEE ---------------------
reservation * lectureReservations(){

    FILE *fdat;
    fdat = fopen("VoiturierPlasschaertReservations.dat", "r");

    int jour;

    reservation *courant, *suivant, *deb;
    courant = malloc(sizeof(reservation));
    deb = courant;

    fscanf(fdat, "%2d", &jour);
    while (!feof(fdat)){
        courant->jour = jour;
        fscanf(fdat, "-%2d-%4d %2d", &courant->mois, &courant->annee, &courant->nbtables);
        for(int i = 0; i < courant->nbtables; i++){
            fscanf(fdat, "%2d ", &courant->tables[i]);
        }

        sprintf(courant->date, "%02d-%02d-%04d", courant->jour, courant->mois, courant->annee);
        suivant = malloc(sizeof(reservation));
        courant->suivant = suivant;
        courant = courant->suivant;
        fscanf(fdat, "%2d", &jour);
    }

    return deb;
}

// ---------------------------------------- AJOUTE UNE RESERVATION -----------------------------------------
void reserver(table * tcourant){

    FILE *fdat, *fres;
    fdat = fopen("VoiturierPlasschaertReservations.dat", "r");

    int jourExiste(int, int, int, int, int, int);
    reservation * lectureReservations();
    reservation *courant, *deb;

    //Variables utile pour récupérer la date du jour
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Date d'aujourd'hui
    int jourAuj = tm.tm_mday;
    int moisAuj = tm.tm_mon + 1;
    int anneeAuj = tm.tm_year + 1900;

    int c = fgetc(fdat), vide;
    if (c == EOF){
        vide = 1;
    }else{
        vide = 0;
        ungetc(c, fdat);
    }

    fclose(fdat);

    int jourRes, moisRes, anneeRes;
    //Demande d'entrer une date à l'utilisateur
    printf("\nDate de la réservation: (FORMAT: JJ-MM-AAAA)\n");
    scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
    
    //Vérifie si la date entrée est correcte
    int existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    while(existe != 1){
        printf("!! DATE NON EXISTANTE !!\nDate de la réservation: (FORMAT: JJ-MM-AAAA)\n");
        scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
        existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    }

    char dateRes[11];
    sprintf(dateRes, "%02d-%02d-%04d", jourRes, moisRes, anneeRes);


    int nbPersonnes, min = 999999, tableChoisie = 999, existeRes = 0;
    //Demande du nombre de personnes
    printf("Nombre de personnes: ");
    scanf("%2d", &nbPersonnes);

    table *tdeb;
    tdeb = tcourant;

    //Si le fichier est vide
    if (vide == 1){
        fres = fopen("VoiturierPlasschaertReservations.dat", "w");

        //On parcourt la liste des table pour pouvoir choisir une table
        while(tcourant->suivant != NULL){

            //Si la table peut acceuillir le nombre de personne voulu
            if (tcourant->nbPersonnes > nbPersonnes && min > nbPersonnes){
                min = nbPersonnes;
                tableChoisie = tcourant->num;
            }else if(tcourant->nbPersonnes == nbPersonnes){
                tableChoisie = tcourant->num;
                break;
            }
            tcourant = tcourant->suivant;   
        }

        //Si aucune table n'est assez grande
        if (tableChoisie == 999){
            printf("\n!! LE RESTAURANT N'A PLUS DE TABLE DISPONIBLE POUR AUTANT DE PERSONNES !!\n");
            return;
        }

        //On imprime la table
        fprintf(fres, "%-10s 01 %02d\n", dateRes, tableChoisie);
        fclose(fres);
        return;

    //SI le fichier n'est pas vide
    }else{
        //Lecture des réservations
        courant = lectureReservations();
        deb = courant;

        //On parcours la liste des réservations
        while(courant->suivant != NULL){
            //Si la date est déjà présente
            if (strcmp(courant->date, dateRes) == 0){
                existeRes = 1;
            }
            courant = courant->suivant;
        }

        courant = deb;
        //Si la réservation existe
        if (existeRes == 1){
            //Si la réservation existe, on ouvre le fichier en mode 'w'
            fres = fopen("VoiturierPlasschaertReservations.dat", "w");
            //On parcours la liste des réservations
            while(courant->suivant != NULL){
                //Une fois que la réservation est la bonne, on va faire les tests
                if (strcmp(courant->date, dateRes) == 0){
                    //On reprend la liste de tables au tout début
                    tcourant = tdeb;
                    //On parcourt la liste des tables
                    while (tcourant->suivant != NULL){
                        //Si la table peut acceuillir le nombre de personne voulu
                        if (tcourant->nbPersonnes >= nbPersonnes && min >= nbPersonnes){
                            min = nbPersonnes;
                            tableChoisie = tcourant->num;
                        }

                        //On parcourt les tables réservées pour la date donnée
                        for(int i = 0; i < courant->nbtables; i++){
                            if (tableChoisie == courant->tables[i]){
                                tableChoisie = 999;
                            }
                        }
                        tcourant = tcourant->suivant;
                    }
                    //Si aucune table n'est dispo
                    if (tableChoisie == 999){
                        printf("\n!! LE RESTAURANT N'A PLUS DE TABLE DISPONIBLE POUR AUTANT DE PERSONNES !!\n");
                        fprintf(fres, "%-10s %02d ", dateRes, courant->nbtables);
                        for (int i = 0; i < courant->nbtables; i++){
                            fprintf(fres, "%02d ", courant->tables[i]);
                        }
                        return;
                    //Si une table est dispo
                    }else{
                        fprintf(fres, "%-10s %02d ", dateRes, courant->nbtables + 1);
                        for (int i = 0; i < courant->nbtables; i++){
                            fprintf(fres, "%02d ", courant->tables[i]);
                        }
                        fprintf(fres, "%02d\n", tableChoisie);
                    }
                //Si la reservation n'est pas la bonne, on la print simplement
                }else{
                    fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables);
                    for (int i = 0; i < courant->nbtables; i++){
                        fprintf(fres, "%02d ", courant->tables[i]);
                    }
                    fprintf(fres, "\n");
                }
                courant = courant->suivant;
            }
            fclose(fres);
        
        //Si la réservation n'existe pas
        }else{
            //On ouvre le fichier en mode "append" pour pouvoir ajouter à la suite de celui ci
            tcourant = tdeb;
            //Fait les tests pour trouver une table adéquate
            while (tcourant->suivant != NULL){
                //Si la table peut acceuillir le nombre de personne voulu
                if (tcourant->nbPersonnes > nbPersonnes && min > nbPersonnes){
                    min = nbPersonnes;
                    tableChoisie = tcourant->num;
                }else if (tcourant->nbPersonnes == nbPersonnes){
                    tableChoisie = tcourant->num;
                    break;
                }
                tcourant = tcourant->suivant;
            }

            //Si aucune table n'est adéquate
            if (tableChoisie == 999){
                printf("\nLe restaurant n'a pas de table disponible pour autant de personnes !");
                return;
            //SI une table est adéquate;
            }else{
                fres = fopen("VoiturierPlasschaertReservations.dat", "a");
                fprintf(fres, "%-10s %02d %02d", dateRes, 1, tableChoisie);
                fclose(fres);
                return;
            }
        }
    }
}

// ------------------------------------------- ANNULE UN RESERVATION ----------------------------------------
void annulerReservation(){
    
    FILE *fdat, *fres;
    fdat = fopen("VoiturierPlasschaertReservations.dat", "r");

    //Variables utile pour récupérer la date du jour
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Date d'aujourd'hui
    int jourAuj = tm.tm_mday;
    int moisAuj = tm.tm_mon + 1;
    int anneeAuj = tm.tm_year + 1900;
    int jourExiste(int, int, int, int, int, int);

    //On check si le fichier est vide
    int c = fgetc(fdat), vide;
    if (c == EOF){
        vide = 1;
    }else{
        vide = 0;
        ungetc(c, fdat);
    }

    //Fermer le fichier
    fclose(fdat);

    //Si le fichier est vide on arrete l'annulation de la reservation
    if (vide == 1){
        printf("\n!! IMPOSSIBLE D'ANNULER UNE RESERVATION CAR IL N'Y EN A AUCUNE !!\n");
        return;
    }

    int jourRes, moisRes, anneeRes;
    //Demande d'entrer une date à l'utilisateur
    printf("\nDate de la réservation: (FORMAT: JJ-MM-AAAA)\n");
    scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
    
    //Vérifie si la date entrée est correcte
    int existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    while(existe != 1){
        printf("!! DATE NON EXISTANTE !!\nDate de la réservation: (FORMAT: JJ-MM-AAAA)\n");
        scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
        existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    }

    reservation *courant, *deb;
    courant = lectureReservations();
    deb = courant;

    int resExiste = 0, numTable;

    char dateRes[11];
    sprintf(dateRes, "%02d-%02d-%04d", jourRes, moisRes, anneeRes);

    printf("Table à annuler: ");
    scanf("\n%2d", &numTable);

    //On parcourt la liste des réservation
    while (courant->suivant != NULL){
        //On regarde si la date entrée est présente
        if(strcmp(dateRes, courant->date) == 0){
            for (int i = 0; i < courant->nbtables; i++){
                if (courant->tables[i] == numTable){
                    resExiste = 1;
                }
            }
        }else{
            printf("\n!! IL N'Y A AUCUNE RESERVATION POUR CETTE DATE !!");
            return;
        }
        courant = courant->suivant;
    }

    //Si la réservation voulue n'existe pas
    if (resExiste == 0){
        printf("\n!! CETTE TABLE N'EST PAS RESERVE POUR LE JOUR SUIVANT: %-10s !!\n", dateRes);
        return;
    }

    fres = fopen("VoiturierPlasschaertReservations.dat", "w");
    //Si la réservation existe, on la retire
    courant = deb;
    while (courant->suivant != NULL){
        //Si c'est la ligne qu'on cherche a changer
        if(strcmp(dateRes, courant->date) == 0){
            //Si le nb de table == 1 alors il n'y en restera plus après suppresion donc on supp la ligne entière
            if(courant->nbtables == 1){
                fprintf(fres, "");
            //SINON on print seulement les tables qu'on garde
            }else{
                fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables - 1);
                for (int i = 0; i < courant->nbtables; i++){
                    if (courant->tables[i] != numTable){
                        fprintf(fres, "%02d ", courant->tables[i]);
                    }
                }
                fprintf(fres, "\n");
            }
        //Si c'est pas la ligne a changer, on print tout
        }else{
            fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables);
            for (int i = 0; i < courant->nbtables; i++){
                fprintf(fres, "%02d ", courant->tables[i]);
            }
            fprintf(fres, "\n");
        }
        courant = courant->suivant;
    }
    fclose(fres);
}

//  ---------------------------------- VERIFIE SI UN JOUR EXISTE ----------------------------------
int jourExiste(int jour, int mois, int annee, int anneeCourante, int moisCourant, int jourCourant){
    int verifdate = 0;
    if (annee == anneeCourante){
        if (mois >= moisCourant && mois <= 12){
            if (((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) && mois == 2){
                if (jour >= jourCourant && jour <= 29){
                    verifdate = 1;
                }
            }else if(mois == 2){
                if (jour >= jourCourant && jour <= 28){
                    verifdate = 1;
                }
            }else if(mois == 1 || mois == 3 || mois == 5|| mois == 7 || mois == 8 || mois == 10 || mois == 12){
                if (jour >= jourCourant && jour <= 31){
                    verifdate = 1;
                }
            }else{
                if (jour >= jourCourant && jour <= 30){
                    verifdate = 1;
                }
            }
        }
    }
    return verifdate;
}
