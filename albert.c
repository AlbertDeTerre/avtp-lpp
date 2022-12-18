#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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
    int running = 1, identification(), jourSemaine(int, int, int);
    void reservation(table*), annulerReservation(), ajouterPersonnel(), afficherPersonnel(personnel*);
    table *tdeb, *tcourant;
    personnel *pcourant, *pdeb;
    
    table * lectureTable();
    personnel * lecturePersonnel();
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();

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
                printf("1: AJOUTER UNE RESERVATION | 2: ANNULER UNE RESERVATION | AUTRE: QUITTER\n");
                scanf("%2d", &option);
                if (option == 1){
                    reservation(tcourant);
                }else if (option == 2){
                    annulerReservation();
                }

            //L'utilisateur veut encoder une commande
            }else if(option == 2){

            //L'utilisateur veut changer le personnel;
            }else if(option == 3){
                printf("1: AJOUTER UN EMPLOYER | 2: LISTE DES EMPLOYES\n");
                scanf("%d", &option);
                if (option == 1){
                    ajouterPersonnel(pcourant);
                }else if(option == 2){
                    afficherPersonnel(pcourant);
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
                    reservation(tcourant);
                }else if (option == 2){
                    annulerReservation();
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
    fclose(fpers);
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
            return matricule;
        }
        fscanf(fdat, "%3d", &matEmp);
    }

    //Si le test entre les deux matricule échoue
    printf("\n!! Identification échouée !!\n");
    fclose(fdat);
    return 0;
}

void reservation(table * courant){

    //Ouverture des fichiers nécéssaires
    FILE *fres, *fdat, *fjours;
    fjours = fopen("VoiturierPlasschaertJours.dat", "r");
    fdat = fopen("VoiturierPlasschaertReservations.res", "r");
    table *deb, *tableChoisie, *table;
    int reservations[8][50], existe = 0;
    char jours[8][10];

    //Déclaration des variables
    int nbPersonnes = 999999, numTableChoisie = 0, min = 999999, tablesRes[50], nbTablesRes, resReussie = 0;
    char jour[10], jourFichier[10];

    //Demande à l'utilisateur quel est le jour de la réservation
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

    int nbTablesResEcriture[8], tablesResEcriture[8][50];

    //Initialisation d'un liste des tables déjà réservées le jour voulu
    for (int i = 1; i <= 7; i++){
        fscanf(fdat, "%9s", jours[i]);
        if (strcmp(jours[i], jour) == 0){
            fscanf(fdat, "%2d", &nbTablesRes);
            nbTablesResEcriture[i] = nbTablesRes;
            for (int j = 0; j < nbTablesRes; j++){
                fscanf(fdat, "%2d", &tablesRes[j]);
                tablesResEcriture[i][j] = tablesRes[j];
            }
        }else{
            fscanf(fdat, "%2d", &nbTablesResEcriture[i]);
            for (int j = 0; j < nbTablesRes; j++){
                fscanf(fdat, "%2d", &tablesResEcriture[i][j]);
            }
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

    char tmp[10];

    //Si la table peut bien être réservée
    if(numTableChoisie != 0){
        for (int i = 1; i <= 7; i++){
            printf("%-9s %02d ", jours[i], nbTablesResEcriture[i]);
            for (int j = 0; j < nbTablesResEcriture[i]; j++){
                printf("%02d ", tablesResEcriture[i][j]);
            }
            printf("\n");
        }

        fclose(fdat);
        fres = fopen("VoiturierPlasschaertReservations.res", "w");

        for (int i = 1; i <= 7; i++){
            if(strcmp(jour, jours[i]) == 0){

                fprintf(fres, "%-9s %02d ", jours[i], nbTablesResEcriture[i] + 1);
            }else{
                fprintf(fres, "%-9s %02d ", jours[i], nbTablesResEcriture[i]);
            }

            for (int j = 0; j < nbTablesResEcriture[i]; j++){
                fprintf(fres, "%02d ", tablesResEcriture[i][j]);
                if (strcmp(jour, jours[i]) == 0 && j == nbTablesResEcriture[i] - 1){
                    fprintf(fres, "%02d", numTableChoisie);
                }
            }
            fprintf(fres, "\n");
        }
    }
    fclose(fres);
}

//Récupérer le numéro du jour de la semaine
int jourSemaine(int jour, int mois, int annee){
    int joursemaine = (jour += mois < 3 ? annee-- : annee - 2, 23*mois/9 + jour + 4 + annee/4- annee/100 + annee/400)%7; 
    if (joursemaine == 0){
        joursemaine = 7; 
    }
    return joursemaine;
}

void annulerReservation(){
    char tmp[10], jour[10], jours[8][10];
    int existe = 0, tablesRes[8][50], nbTablesRes[8];

    FILE *fjours, *freservR, *freservW;
    fjours = fopen("VoiturierPlasschaertJours.dat", "r");
    freservR = fopen("VoiturierPlasschaertReservations.res", "r");

    printf("Jour de la réservation à annuler: ");
    scanf("%9s", jour);

    //On met toutes les lettre en majuscule
    for (int i = 0; i < 10; i++){
        if (jour[i] == '\0'){
            break;
        }
        jour[i] = toupper(jour[i]);
    }

    //Check si le jour existe
    for (int i = 1; i <= 7; i++){
        fscanf(fjours, "%9s", jours[i]);

        if (strcmp(jour, jours[i]) == 0){
            existe = i;
        }
    }

    //Redemande le jour jusqu'a ce qu'il soit bon
    while (existe == 0){
        printf("\n!! CE JOUR N'EXISTE PAS !!\nJour de la réservation à annuler: ");
        scanf("%9s", jour);

        for (int i = 0; i < 10; i++){
            if (jour[i] == '\0'){
                break;
            }
            jour[i] = toupper(jour[i]);
        }

        for (int i = 1; i <= 7; i++){
            fscanf(fjours, "%9s", jours[i]);
            
            if (strcmp(jour, jours[i]) == 0){
                existe = i;
            }
        }
    }

    int numTableAnnuler = 0, nvNbTables = 0;

    printf("\nNuméro de la table à annuler: ");
    scanf("%2d", &numTableAnnuler);

    //Initialisation du vecteur avec toutes les tables reservées
    for (int i = 1; i <= 7; i++){
        fscanf(freservR, "%9s %2d", tmp, &nbTablesRes[i]);
        printf("%-9s %2d ", jours[i], nbTablesRes[i]);
        for (int j = 0; j < nbTablesRes[i]; j++){
            fscanf(freservR, "%2d", &tablesRes[i][j]);
            printf("%2d ", tablesRes[i][j]);
            if (strcmp(jours[i], jour) == 0 && tablesRes[i][j] == numTableAnnuler){
                nvNbTables = nbTablesRes[i] - 1;
            }
        }
        printf("\n");
    }

    //Fermeture du fichier de lecture
    fclose(freservR);

    freservW = fopen("VoiturierPlasschaertReservations.res", "w");
    //Réécriture dans le fichier réservations
    for (int i = 1; i <= 7; i++){

        //Si le jour = celui choisi et que le numéro de table à annuler existe, alors on ecrit le nouveau nombre de table
        if (strcmp(jours[i], jour) == 0 && numTableAnnuler != 0){
            fprintf(freservW, "%-9s %02d ", jours[i], nvNbTables);
        }else{
            fprintf(freservW, "%-9s %02d ", jours[i], nbTablesRes[i]);
        }
        for (int j = 0; j < nbTablesRes[i]; j++){
            if (!(strcmp(jours[i], jour) == 0 && tablesRes[i][j] == numTableAnnuler)){
                fprintf(freservW, "%02d ", tablesRes[i][j]);
            }
        }
        fprintf(freservW, "\n");
    }
    fclose(freservW);
}

void ajouterPersonnel(personnel * courant){
    int fonction = 0, mat;
    char nom[21], foncstr[21];

    FILE *fres;
    fres = fopen("VoiturierPlasschaertPersonnel.dat", "w");

    personnel *intercale, *deb;

    //Demande le type d'employé à ajouter
    printf("\nType d'employé: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
    scanf("%d", &fonction);

    while (!(fonction == 1 || fonction == 2 || fonction == 3)){
        printf("\nType d'employé: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
        scanf("%d", &fonction);
    }

    //Demande le prénom de l'employé à ajouter
    printf("\nPrénom du nouvel employé: ");
    scanf("%20s", nom);

    deb = courant;
    intercale = malloc(sizeof(personnel));
    while(courant->suivant != NULL){
        //Si ce test est vrai, alors l'élément courant est de meme type que celui qu'on ajoute
        if (courant->matricule / 100 == fonction && courant->suivant->matricule / 100 != fonction){
            mat = courant->matricule;
            strcpy(foncstr, courant->fonction);
            intercale->suivant = courant->suivant;
		    courant->suivant = intercale;
        }

        if (courant->matricule == 0){
            courant->matricule = mat + 1;
            strcpy(courant->fonction, foncstr);
            strcpy(courant->prenom, nom);
        }
        
        printf("%03d %-20s %-20s\n", courant->matricule, courant->prenom, courant->fonction);
        fprintf(fres, "%03d %-20s %-20s\n", courant->matricule, courant->prenom, courant->fonction);
        courant = courant->suivant;
    }

    // courant = deb;
    // while(courant->suivant != NULL){
        
    //     fprintf(fres, "%03d %-20s %-20s\n", courant->matricule, courant->prenom, courant->fonction);
    //     courant = courant->suivant;
    // }
    // fclose(fres);

}

void afficherPersonnel(personnel * courant){
    personnel *deb;
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