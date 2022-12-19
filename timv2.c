#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int i,j; //declaration general pour les compteurs





//structure table 
typedef struct listePlats{
      int id;
      char nom[50];
      float prix;
      struct listePlats *suivant;
    }listePlats;

    typedef struct listeBoissons{
      int id;
      char nom[50];
      float prix;
      struct listeBoissons *suivant;
    }listeBoissons;

    typedef struct boisson{
      int id;
      char nom[50];
      float prix;
    }boisson;

    typedef struct plat{
      int id;
      char nom[50];
      float prix;
    }plat;
//Structure de ticket
    typedef struct ticket{
        float prixPlats,prixBoissons;
        int nbplats;
		int nbboissons;
        struct plat plats[20];
        struct boisson boissons[100];
        char date[11];
    }ticket;
    //Structure personnel
typedef struct personnel{
    int matricule;              //Matricule du membre du personnel
    char prenom[21];            //Prenom du membre du personnel
    char fonction[21];          //Fonction du membre du personnel (cuisinier, serveur, ...)
    struct personnel *suivant;
}personnel;

//Structure table
typedef struct table{
    int num;                    //Numéro de la table
    int nbPersonnes;		//Nombre de personnes pouvant être à cette table
	struct ticket ticket;            
    struct table *suivant;      //Client suivant de la liste chainée
}table;





table * lectureTable(){
	//ouverture des fichiers
	int i;
	FILE *fTable;
	fTable = fopen("VoiturierPlasschaertTables.dat","r");
	table *tdeb, *tsuivant,*tcourant;

    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    tcourant = malloc(sizeof(table));
    tdeb = tcourant;
    fscanf(fTable, "%2d", &tcourant->num);
    i=0;
    //Commencement de la boucle de lecture
    while (!feof(fTable)){       
        tsuivant = malloc(sizeof(table));
        tcourant->suivant = tsuivant;
		i++;
		tcourant->ticket.nbplats = 0;
		tcourant->ticket.nbboissons =0;
		tcourant->ticket.prixPlats = 0;
		tcourant->ticket.prixBoissons = 0;
		fscanf(fTable,"%2d",&tcourant->nbPersonnes);
        tcourant = tsuivant;
        fscanf(fTable, "%2d", &tcourant->num);
        
    }
    //affectation de la premiere structure de la liste a bcourant
    tcourant = tdeb;
     //mise Null dans le dernier element;
    for(j=1;j<i;j++){
    	tcourant = tcourant->suivant;}
	tcourant->suivant =NULL;
    
    

    return tdeb;
	
}


listeBoissons * lectureBoisson(){
	//ouverture des fichiers
	int i;
	FILE *fboisson;
	fboisson = fopen("VoiturierPlasschaertBoisson.dat","r");
	listeBoissons *bdeb, *bcourant, *bsuivant;

    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    bcourant = malloc(sizeof(listeBoissons));
    bdeb = bcourant;
    fscanf(fboisson, "%d", &bcourant->id);
    i=0;
    //Commencement de la boucle de lecture
    while (!feof(fboisson)){       
        fscanf(fboisson, "%s %f", &bcourant->nom,&bcourant->prix);
        bsuivant = malloc(sizeof(listeBoissons));
        bcourant->suivant = bsuivant;
		i++;
        bcourant = bsuivant;
        fscanf(fboisson, "%2d", &bcourant->id);
        
    }
    //affectation de la premiere structure de la liste a bcourant
    bcourant = bdeb;
     //mise Null dans le dernier element;
    for(j=1;j<i;j++){
    	bcourant = bcourant->suivant;}
	bcourant->suivant =NULL;
    return bdeb;
	
	
	
}


listePlats * lecturePlat(){
	//ouverture des fichiers
	
	FILE *fplat;
	fplat = fopen("VoiturierPlasschaertMenu.dat","r");
	listePlats *pdeb, *pcourant, *psuivant;




    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    pcourant = malloc(sizeof(listePlats));
    pdeb = pcourant;
    fscanf(fplat, "%2d", &pcourant->id);
    i=0;
    
    //Commencement de la boucle de lecture
    while (!feof(fplat)){       
        fscanf(fplat, "%s %f", &pcourant->nom,&pcourant->prix);
        psuivant = malloc(sizeof(listePlats));
        pcourant->suivant = psuivant;
        i++;
        pcourant = psuivant;
        fscanf(fplat, "%2d", &pcourant->id);
    }
    //affectation de la premiere structure de la liste pcourant
    pcourant = pdeb;
    for(j=1;j<i;j++){
    	pcourant = pcourant->suivant;
	}
	pcourant->suivant = NULL;
    return pdeb;
	
}

void faireCommande(listePlats *pcourant, listeBoissons *bcourant,table *tablecourant){
	int tab, type, id;
	
	listeBoissons *bdeb,*bsuivant;
	listePlats  *pdeb,*psuivant;
	table *tabledeb, *tablesuivant;
	tabledeb = tablecourant;
	void ajoutart(int, int , int, listePlats*, listeBoissons*,table*);
	i=0;
	while(tablecourant != NULL){
		tablecourant = tablecourant->suivant;
		i++;
	}
	i--;
	tablecourant = tabledeb;
	//demande de la table.
	printf("TABLE N�");
	scanf("%d",&tab);
	if((tab>=1)&&(tab<=i)){
		
		//demande si plat ou boisson (si 0 stop la commande
		printf("1 : PLAT | 2 : BOISSON | 0 ARRET DE LA COMMANDE\n");
		scanf("%d",&type);
		while(type != 0){
			if((type==2)||(type==1)){
				//demande de l'id de larticle
				printf("ID DE L'ARTICLE : \n");
				scanf("%d",&id);
				//appel de la fonction d'ajout � une commande.
				ajoutart(tab,type,id,pcourant, bcourant,tablecourant);
				printf("1 : PLAT | 2 : BOISSON | 0 ARRET DE LA COMMANDE \n");
				scanf("%d",&type);
				
			}
			//entree non valide, le rpogramme previens et repose la question. 
			
			else{
				printf("Entrez une donnee valide ! \n1 : PLAT | 2 : BOISSON | 0 ARRET DE LA COMMANDE \n");
				scanf("%d",&type);
			}
		}
		
		printf("FIN DE COMMANDE.");
	}
	else{
		printf("TABLE INNEXISTANTE.\n");
		return;
	}
}



void ajoutart(int tab, int type, int id, listePlats *pcourant, listeBoissons *bcourant, table *tablecourant){
	listePlats *pdeb, *psuivant;
	listeBoissons *bdeb, *bsuivant;
	table *tabledeb, *tablesuivant;
	
	pdeb = pcourant;
	bdeb = bcourant; 
	tabledeb = tablecourant;
	
	i=0;
	printf("%2d %2d\n",tablecourant->num,tab);
	//recherche de la table concern�e. Sortie de boucle s'il trouve la table ou si la table arrive a NULL
	while((tablecourant != NULL)&&(tablecourant->num != tab)){
		tablecourant = tablecourant->suivant;
		
	}
	
	//s'il la boucle n'a pas trouv� la table alors la table n'est pas dans le restaurant.
	if(tablecourant == NULL){
		printf("Cette table n'est pas dans le restaurant.\n");
		return;
	}
	//Si l'article est un plat
	if(type ==1){
		
		//recherche du bon plat :
		while((pcourant != NULL)&&(id != pcourant->id)){
			pcourant = pcourant->suivant;
			
		}
		
		//Si la boucle n'a pas trouv� le plat :
		if(pcourant == NULL){
			printf("Ce plat n'existe pas dans le menu.\n");
			return;
		}
		tablecourant->ticket.nbplats++;
		
		//ajout des informations sur le ticket de la table.
		tablecourant->ticket.plats[tablecourant->ticket.nbplats].id = pcourant->id;
		strcpy(tablecourant->ticket.plats[tablecourant->ticket.nbplats].nom,pcourant->nom);
		tablecourant->ticket.plats[tablecourant->ticket.nbplats].prix = pcourant->prix;
		tablecourant->ticket.prixPlats += pcourant->prix;
		
			
	}
	
	//si l'article est une boisson.
	if(type ==2){
		
		//recherche du bon plat :
		while((bcourant != NULL)&&(id != bcourant->id)){
			bcourant = bcourant->suivant;
			
		}
		
		//Si la boucle n'a pas trouv� le plat :
		if(bcourant == NULL){
			printf("Cette boisson n'existe pas dans le menu.\n");
			return;
		}
		tablecourant->ticket.nbboissons++;
		
		//ajout des informations sur le ticket de la table.
		tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].id = bcourant->id;
		strcpy(tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].nom,bcourant->nom);
		tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].prix = bcourant->prix;
		tablecourant->ticket.prixBoissons += bcourant->prix;	
	}
	
}
		
void imprimerTicket(table *tcourant,int idemploye){
	table *tdeb, *tsuivant;
	FILE*fdirect,*fcaisse;
	fdirect = fopen("VoiturierPlasschaertTicketCli.res","w");
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","a");
	int numTab;
	printf("Entrez la table a imprimer : \n" );
	
	scanf("%d",&numTab);
	//Fonction qui affiche la date et l'heure du ticket
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
	
	//parcourt de la liste pour trouver la bonne table.
	while((tcourant->num != numTab)&&(tcourant != NULL)){
		tcourant = tcourant->suivant;
	}
	if(tcourant ==NULL){
		printf("Cette table n'existe pas.");
		return;
	}
	
    tm_info = localtime(&timer);
    //impression en-t�te
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(fdirect,"                  %s \n                      Chez ClaCla\n                      Table n�%-3d\n                   Servis par n�%3d\n--------------------------------------------------------------\n",buffer,tcourant->num,idemploye);
	fprintf(fcaisse,"                  %s \n                      Chez ClaCla\n                      Table n�%-3d\n                   Servis par n�%3d\n--------------------------------------------------------------\n",buffer,tcourant->num,idemploye);
	
	
	//ecriture du ticket de caisse client et restaurant
	//Affichage de tout les plats 
	for(i=1;i<=tcourant->ticket.nbplats;i++){
		
		fprintf(fdirect,"   %-51s %5.2f�\n",tcourant->ticket.plats[i].nom,tcourant->ticket.plats[i].prix,(tcourant->ticket.plats[i].prix)/100*21);
		fprintf(fcaisse,"   %-51s %5.2f�\n",tcourant->ticket.plats[i].nom,tcourant->ticket.plats[i].prix,(tcourant->ticket.plats[i].prix)/100*21);
	}
	for(i=1;i<=tcourant->ticket.nbboissons;i++){
		fprintf(fdirect,"   %-51s %5.2f�\n",tcourant->ticket.boissons[i].nom,tcourant->ticket.boissons[i].prix,(tcourant->ticket.boissons[i].prix)/100*21);
		fprintf(fcaisse,"   %-51s %5.2f�\n",tcourant->ticket.boissons[i].nom,tcourant->ticket.boissons[i].prix,(tcourant->ticket.boissons[i].prix)/100*21);
	}
	//impression dans le fichier caisse.
	if(tcourant->ticket.nbplats >0){
	
		fprintf(fcaisse,"\nTotal HTVA 6%%  :                                    %8.2f�\n",(tcourant->ticket.prixPlats-(tcourant->ticket.prixPlats/100*6)));
		fprintf(fcaisse,"TVA        6%%  :                                    %8.2f�\n",(tcourant->ticket.prixPlats/100*6));
		fprintf(fcaisse,"Total TTC      :                                    %8.2f�\n",(tcourant->ticket.prixPlats));
	}
	if(tcourant->ticket.nbboissons >0){
	
		fprintf(fcaisse,"\nTotal HTVA 21%% :                                    %8.2f�\n",(tcourant->ticket.prixBoissons-(tcourant->ticket.prixBoissons/100*21)));
		fprintf(fcaisse,"TVA        21%% :                                    %8.2f�\n",(tcourant->ticket.prixBoissons/100*21));
		fprintf(fcaisse,"Total TTC      :                                    %8.2f�\n",tcourant->ticket.prixBoissons);
	}
	fprintf(fcaisse,"\n--------------------------------------------------------------\n");
	float total = tcourant->ticket.prixPlats + tcourant->ticket.prixBoissons;
	fprintf(fcaisse,"Total          :                                    %8.2f�\n\n\n",total);
	fprintf(fcaisse,"===================================================================\n\n\n");
	//impression client
	if(tcourant->ticket.nbplats >0){
		fprintf(fdirect,"\nTotal HTVA 6%%  :                                    %8.2f�\n",(tcourant->ticket.prixPlats-(tcourant->ticket.prixPlats/100*6)));
		fprintf(fdirect,"TVA        6%%  :                                    %8.2f�\n",(tcourant->ticket.prixPlats/100*6));
		fprintf(fdirect,"Total TTC      :                                    %8.2f�\n",(tcourant->ticket.prixPlats));
	}
	if(tcourant->ticket.nbboissons>0){
		fprintf(fdirect,"\nTotal HTVA 21%% :                                    %8.2f�\n",(tcourant->ticket.prixBoissons-(tcourant->ticket.prixBoissons/100*21)));
		fprintf(fdirect,"TVA        21%% :                                    %8.2f�\n",(tcourant->ticket.prixBoissons/100*21));
		fprintf(fdirect,"Total TTC      :                                    %8.2f�\n",tcourant->ticket.prixBoissons);
	}
	fprintf(fdirect,"\n--------------------------------------------------------------\n");
	total = tcourant->ticket.prixPlats + tcourant->ticket.prixBoissons;
	fprintf(fdirect,"Total          :                                    %8.2f�\n",total);
	
	
	//mise a 0 du ticket imprim�
	//Pour les plats
	for(i=1;i<=tcourant->ticket.nbplats;i++){
		tcourant->ticket.plats[i].id = 0;
		strcpy(tcourant->ticket.plats[i].nom,"");
		tcourant->ticket.plats[i].prix = 0;
		tcourant->ticket.prixPlats =0;		
	}
	//Pour les boissons
	for(i=1;i<=tcourant->ticket.nbboissons;i++){
		tcourant->ticket.boissons[i].id = 0;
		strcpy(tcourant->ticket.boissons[i].nom,"");
		tcourant->ticket.boissons[i].prix = 0;
		tcourant->ticket.prixBoissons =0;		
	}
	fclose(fdirect);
	fclose(fcaisse);
	
	
	
}

void nettoyerCaisse(){
	FILE*fcaisse;
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","w");
	printf("Caisse vide.\n");
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
	if(matricule == 0)
		return 0;
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

    for (i = 0; i < 10; i++){
        if (jour[i] == '\0'){
            break;
        }
        jour[i] = toupper(jour[i]);
    }

    //Initialise le vecteur comprenant chaque jours de la semaine
    for (i = 1; i <= 7; i++){
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
        for (i = 0; i < 10; i++){
            if (jour[i] == '\0'){
                break;
            }
            jour[i] = toupper(jour[i]);
        }

        //Série de test pour voir si le jour est OK
        for (i = 1; i <= 7; i++){
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
    for (i = 1; i <= 7; i++){
        fscanf(fdat, "%9s", jours[i]);
        if (strcmp(jours[i], jour) == 0){
            fscanf(fdat, "%2d", &nbTablesRes);
            nbTablesResEcriture[i] = nbTablesRes;
            for (j = 0; j < nbTablesRes; j++){
                fscanf(fdat, "%2d", &tablesRes[j]);
                tablesResEcriture[i][j] = tablesRes[j];
            }
        }else{
            fscanf(fdat, "%2d", &nbTablesResEcriture[i]);
            for (j = 0; j < nbTablesRes; j++){
                fscanf(fdat, "%2d", &tablesResEcriture[i][j]);
            }
        }
    }

    //Parcours la liste de des tables a la recherche d'une table assez grande et regarde si elle est déjà prise
    while(courant->suivant != NULL){
        int reservee = 0;
        for (i = 0; i < nbTablesRes; i++){
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
        for (i = 1; i <= 7; i++){
            printf("%-9s %02d ", jours[i], nbTablesResEcriture[i]);
            for (j = 0; j < nbTablesResEcriture[i]; j++){
                printf("%02d ", tablesResEcriture[i][j]);
            }
            printf("\n");
        }

        fclose(fdat);
        fres = fopen("VoiturierPlasschaertReservations.res", "w");

        for (i = 1; i <= 7; i++){
            if(strcmp(jour, jours[i]) == 0){

                fprintf(fres, "%-9s %02d ", jours[i], nbTablesResEcriture[i] + 1);
            }else{
                fprintf(fres, "%-9s %02d ", jours[i], nbTablesResEcriture[i]);
            }

            for (j = 0; j < nbTablesResEcriture[i]; j++){
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
    for (i = 0; i < 10; i++){
        if (jour[i] == '\0'){
            break;
        }
        jour[i] = toupper(jour[i]);
    }

    //Check si le jour existe
    for (i = 1; i <= 7; i++){
        fscanf(fjours, "%9s", jours[i]);

        if (strcmp(jour, jours[i]) == 0){
            existe = i;
        }
    }

    //Redemande le jour jusqu'a ce qu'il soit bon
    while (existe == 0){
        printf("\n!! CE JOUR N'EXISTE PAS !!\nJour de la réservation à annuler: ");
        scanf("%9s", jour);

        for (i = 0; i < 10; i++){
            if (jour[i] == '\0'){
                break;
            }
            jour[i] = toupper(jour[i]);
        }

        for (i = 1; i <= 7; i++){
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
    for (i = 1; i <= 7; i++){
        fscanf(freservR, "%9s %2d", tmp, &nbTablesRes[i]);
        printf("%-9s %2d ", jours[i], nbTablesRes[i]);
        for (j = 0; j < nbTablesRes[i]; j++){
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
    for (i = 1; i <= 7; i++){

        //Si le jour = celui choisi et que le numéro de table à annuler existe, alors on ecrit le nouveau nombre de table
        if (strcmp(jours[i], jour) == 0 && numTableAnnuler != 0){
            fprintf(freservW, "%-9s %02d ", jours[i], nvNbTables);
        }else{
            fprintf(freservW, "%-9s %02d ", jours[i], nbTablesRes[i]);
        }
        for (j = 0; j < nbTablesRes[i]; j++){
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





int main()
{
    //Ouverture des fichiers
    FILE *ftab, *fmenu, *fboi, *fpersonnel, *fhoraire;
    int numEmploye;
    //Déclaration des fonctions et variables;
    int running = 1, identification(), jourSemaine(int, int, int);
    void reservation(table*), annulerReservation(), ajouterPersonnel(), afficherPersonnel(personnel*);
    table *tdeb, *tcourant;
    personnel *pcourant, *pdeb;
    listeBoissons *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	listePlats *platcourant, *platdeb,*platsuivant;
	platcourant = lecturePlat();
    table * lectureTable();
    personnel * lecturePersonnel();
    
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();
	tdeb = tcourant;
	
	
	
	
	
	
	
	
	
    //Si la personne s'identifie bien, on rentre dans la boucle, sinon one ne rentre pas dedans
    running = -1;
	while(running ==-1){
		running = identification();
		numEmploye = running;
    //Si c'est le gérant -> menu admin
    if (running == 999){
        running = 1;
        while (running == 1)
        {
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 3: PERSONNEL | 4: IMPRIMMER TICKET | 5: REENITIALISER CAISSE | AUTRE: QUITTER)\n");
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
				faireCommande(platcourant,bcourant,tdeb);
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
            }
			else if(option == 4){
				imprimerTicket(tcourant,numEmploye);
			}
			else if(option == 5){
				nettoyerCaisse();
			}
			else{
                break;
            }
        }
    //Si ce n'est qu'un simple employé -> menu employé 
    }else if (running > 0){
        running = 1;
        while (running == 1)
        {
            
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 3: IMPRIMMER TICKET | AUTRE: QUITTER)\n");
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
				faireCommande(platcourant, bcourant,tcourant);
			
            //L'utilisateur veut quitter le programme
            }
			else if(option == 3){
				imprimerTicket(tcourant,numEmploye);
			}
			else{
                break;
            }
        }
        
    }
    if(running == 0)
    	break;
	running = identification();
    
    }

    printf("\n** FIN DU PROGRAMME **\n");
}



















