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
    int num;                    //Numero de la table
    int nbPersonnes;		//Nombre de personnes pouvant etre a  cette table
	struct ticket ticket;            
    struct table *suivant;      //Client suivant de la liste chainee
}table;

typedef struct reservation{
    char date[11];
    int nbtables;
    int jour;
    int mois;
    int annee;
    int tables[50];
    struct reservation *suivant;
}reservation;





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

// ----------------------------------------- LIT LE FICHIER BOISSON  -------------------------------------------
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

// ----------------------------------------- LIT LE FICHIER MENU -------------------------------------------
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

// ----------------------------------------- FAIT LA COMMANDE -------------------------------------------
void faireCommande(listePlats *pcourant, listeBoissons *bcourant,table *tablecourant){
	int tab, type, id;
	
	listeBoissons *bdeb,*bsuivant;
	listePlats  *pdeb,*psuivant;
	table *tabledeb, *tablesuivant;
	tabledeb = tablecourant;
	bdeb = bcourant;
	pdeb = pcourant;
	void ajoutart(int, int , int, listePlats*, listeBoissons*,table*);
	i=0;
	while(tablecourant != NULL){
		tablecourant = tablecourant->suivant;
		i++;
	}
	i--;
	tablecourant = tabledeb;
	//demande de la table.
	printf("TABLE NUM :");
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
				//appel de la fonction d'ajout à une commande.
				ajoutart(tab,type,id,pdeb, bdeb,tabledeb);
				printf("1 : PLAT | 2 : BOISSON | 0 ARRET DE LA COMMANDE \n");
				scanf("%d",&type);
				
			}
			//entree non valide, le rpogramme previens et repose la question. 
			
			else{
				printf("!! Entrez une donnee valide !! \n1 : PLAT | 2 : BOISSON | 0 ARRET DE LA COMMANDE \n");
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


// ---------------------------- AJOUTE UN ARTICLE A L'ADDITION DE LA TABLE -------------------------------------------
void ajoutart(int tab, int type, int id, listePlats *pcourant, listeBoissons *bcourant, table *tablecourant){
	listePlats *pdeb, *psuivant;
	listeBoissons *bdeb, *bsuivant;
	table *tabledeb, *tablesuivant;
	
	pdeb = pcourant;
	bdeb = bcourant; 
	tabledeb = tablecourant;
	
	i=0;
	
	//recherche de la table concernée. Sortie de boucle s'il trouve la table ou si la table arrive a NULL
	while((tablecourant != NULL)&&(tablecourant->num != tab)){
		tablecourant = tablecourant->suivant;
		
	}
	
	//s'il la boucle n'a pas trouvé la table alors la table n'est pas dans le restaurant.
	if(tablecourant == NULL){
		printf("Cette table n'est pas dans le restaurant.\n");
		return;
	}
	//Si l'article est un plat
	if(type ==1){
		
		
		pcourant = pdeb;
		
		//recherche du bon plat :
		while((pcourant != NULL)&&(id != pcourant->id)){
			pcourant = pcourant->suivant;
			
		}
		//Si la boucle n'a pas trouvé le plat :
		if(pcourant == NULL){
			printf("Ce plat n'existe pas dans le menu.\n");
			return;
		}
		tablecourant->ticket.nbplats++;
		printf("Le plat suivant à été ajouté : %s %5.2f\n",pcourant->nom,pcourant->prix);
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
		
		//Si la boucle n'a pas trouvé le plat :
		if(bcourant == NULL){
			printf("Cette boisson n'existe pas dans le menu.\n");
			return;
		}
		tablecourant->ticket.nbboissons++;
		printf("La boisson suivante à été ajoutée / %s %5.2f\n",bcourant->nom,bcourant->prix);
		//ajout des informations sur le ticket de la table.
		tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].id = bcourant->id;
		strcpy(tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].nom,bcourant->nom);
		tablecourant->ticket.boissons[tablecourant->ticket.nbboissons].prix = bcourant->prix;
		tablecourant->ticket.prixBoissons += bcourant->prix;	
	}
	
}

// -------------------------- IMPRIME LE TICKET CLIENT ET AJOUTE LE TICKET A LA CAISSE  -------------------------------------------		
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
    //impression en-tête
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(fdirect,"                  %s \n                      Chez ClaCla\n                      Table n°%-3d\n                   Servis par n°%3d\n--------------------------------------------------------------\n",buffer,tcourant->num,idemploye);
	fprintf(fcaisse,"                  %s \n                      Chez ClaCla\n                      Table n°%-3d\n                   Servis par n°%3d\n--------------------------------------------------------------\n",buffer,tcourant->num,idemploye);
	
	
	//ecriture du ticket de caisse client et restaurant
	//Affichage de tout les plats 
	for(i=1;i<=tcourant->ticket.nbplats;i++){
		
		fprintf(fdirect,"   %-51s %5.2f€\n",tcourant->ticket.plats[i].nom,tcourant->ticket.plats[i].prix,(tcourant->ticket.plats[i].prix)/100*21);
		fprintf(fcaisse,"   %-51s %5.2f€\n",tcourant->ticket.plats[i].nom,tcourant->ticket.plats[i].prix,(tcourant->ticket.plats[i].prix)/100*21);
	}
	for(i=1;i<=tcourant->ticket.nbboissons;i++){
		fprintf(fdirect,"   %-51s %5.2f€\n",tcourant->ticket.boissons[i].nom,tcourant->ticket.boissons[i].prix,(tcourant->ticket.boissons[i].prix)/100*21);
		fprintf(fcaisse,"   %-51s %5.2f€\n",tcourant->ticket.boissons[i].nom,tcourant->ticket.boissons[i].prix,(tcourant->ticket.boissons[i].prix)/100*21);
	}
	//impression dans le fichier caisse.
	if(tcourant->ticket.nbplats >0){
	
		fprintf(fcaisse,"\nTotal HTVA 6%%  :                                    %8.2f€\n",(tcourant->ticket.prixPlats-(tcourant->ticket.prixPlats/100*6)));
		fprintf(fcaisse,"TVA        6%%  :                                    %8.2f€\n",(tcourant->ticket.prixPlats/100*6));
		fprintf(fcaisse,"Total TTC      :                                    %8.2f€\n",(tcourant->ticket.prixPlats));
	}
	if(tcourant->ticket.nbboissons >0){
	
		fprintf(fcaisse,"\nTotal HTVA 21%% :                                    %8.2f€\n",(tcourant->ticket.prixBoissons-(tcourant->ticket.prixBoissons/100*21)));
		fprintf(fcaisse,"TVA        21%% :                                    %8.2f€\n",(tcourant->ticket.prixBoissons/100*21));
		fprintf(fcaisse,"Total TTC      :                                    %8.2f€\n",tcourant->ticket.prixBoissons);
	}
	fprintf(fcaisse,"\n--------------------------------------------------------------\n");
	float total = tcourant->ticket.prixPlats + tcourant->ticket.prixBoissons;
	fprintf(fcaisse,"Total          :                                    %8.2f€\n\n\n",total);
	fprintf(fcaisse,"===================================================================\n\n\n");
	//impression client
	if(tcourant->ticket.nbplats >0){
		fprintf(fdirect,"\nTotal HTVA 6%%  :                                    %8.2f€\n",(tcourant->ticket.prixPlats-(tcourant->ticket.prixPlats/100*6)));
		fprintf(fdirect,"TVA        6%%  :                                    %8.2f€\n",(tcourant->ticket.prixPlats/100*6));
		fprintf(fdirect,"Total TTC      :                                    %8.2f€\n",(tcourant->ticket.prixPlats));
	}
	if(tcourant->ticket.nbboissons>0){
		fprintf(fdirect,"\nTotal HTVA 21%% :                                    %8.2f€\n",(tcourant->ticket.prixBoissons-(tcourant->ticket.prixBoissons/100*21)));
		fprintf(fdirect,"TVA        21%% :                                    %8.2f€\n",(tcourant->ticket.prixBoissons/100*21));
		fprintf(fdirect,"Total TTC      :                                    %8.2f€\n",tcourant->ticket.prixBoissons);
	}
	fprintf(fdirect,"\n--------------------------------------------------------------\n");
	total = tcourant->ticket.prixPlats + tcourant->ticket.prixBoissons;
	fprintf(fdirect,"Total          :                                    %8.2f€\n",total);
	
	
	//mise a 0 du ticket imprimé
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

// ----------------------------------------- SUPPRIME TOUT LES TICKET ENREGISTRE -------------------------------------------
void nettoyerCaisse(){
	FILE*fcaisse;
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","w");
}


// ----------------------------------------- AJOUTE UN EMPLOYE -------------------------------------------

void ajouterPersonnel(personnel * courant){
    int fonction = 0, mat;
    char nom[21], foncstr[21];

    FILE *fres;
    fres = fopen("VoiturierPlasschaertPersonnel.dat", "w");

    personnel *intercale, *deb;

    //Demande le type d'employe a  ajouter
    printf("\nType d'employe: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
    scanf("%d", &fonction);

    while (!(fonction == 1 || fonction == 2 || fonction == 3)){
        printf("\nType d'employe: (1: GERANT | 2: CUISINIER | 3: SERVEUR)\n");
        scanf("%d", &fonction);
    }

    //Demande le prenom de l'employe a  ajouter
    printf("\nPrenom du nouvel employe: ");
    scanf("%20s", nom);

    deb = courant;
    intercale = malloc(sizeof(personnel));
    while(courant->suivant != NULL){
        //Si ce test est vrai, alors l'element courant est de meme type que celui qu'on ajoute
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

    fclose(fres);
}

// -------------------------------- SUPPRIME UN EMPLOYE -------------------------------------
void supprimerPersonnel(personnel * courant){
    
    int matPers, existe = 0;
    personnel *deb;

    deb = courant;
    while (existe == 0){
        printf("\nMatricule du membre du personnel a  supprimer: ");
        scanf("%3d", &matPers);
        while(courant->suivant != NULL){
            if (courant->matricule == matPers){
                existe = 1;
            }
            courant = courant->suivant;
        }
    }
    
    


}

// ---------------------------------- AFFICHE LA LISTE DES EMPLOYES ----------------------------------
void afficherPersonnel(personnel * courant){
    personnel *deb;
    deb = courant;
    char tmpfonc[21] = "";

    while(courant->suivant != NULL){
        if (strcmp(tmpfonc, courant->fonction) != 0){
            strcpy(tmpfonc, courant->fonction);
            printf("\n%-20s\n=========================================\n", tmpfonc);
        }

        printf("    Matricule: %03d - Prenom: %-20s\n", courant->matricule, courant->prenom);
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
        for(i = 0; i < courant->nbtables; i++){
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

    //Variables utile pour recuperer la date du jour
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
    //Demande d'entrer une date a  l'utilisateur
    printf("\nDate de la reservation: (FORMAT: JJ-MM-AAAA)\n");
    scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
    
    //Verifie si la date entree est correcte
    int existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    while(existe != 1){
        printf("!! DATE NON EXISTANTE !!\nDate de la reservation: (FORMAT: JJ-MM-AAAA)\n");
        scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
        existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    }

    char dateRes[11];
    sprintf(dateRes, "%02d-%02d-%04d", jourRes, moisRes, anneeRes);


    int nbPersonnes, min = 999999, tableChoisie = 999, existeRes = 0;
    //Demande du nombre de personnes
    printf("Nombre de personnes: ");
    scanf("%d", &nbPersonnes);

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
        //Lecture des reservations
        courant = lectureReservations();
        deb = courant;

        //On parcours la liste des reservations
        while(courant->suivant != NULL){
            //Si la date est deja  presente
            if (strcmp(courant->date, dateRes) == 0){
                existeRes = 1;
            }
            courant = courant->suivant;
        }

        courant = deb;
        
        //Si la reservation existe
        if (existeRes == 1){
            //Si la reservation existe, on ouvre le fichier en mode 'w'
            fres = fopen("VoiturierPlasschaertReservations.dat", "w");
            //On parcours la liste des reservations
            while(courant->suivant != NULL){
                //Une fois que la reservation est la bonne, on va faire les tests
                if (strcmp(courant->date, dateRes) == 0){
                    //On reprend la liste de tables au tout debut
                    tcourant = tdeb;
                    //On parcourt la liste des tables
                    while (tcourant->suivant != NULL){
                        //Si la table peut acceuillir le nombre de personne voulu
                        if (tcourant->nbPersonnes >= nbPersonnes && min >= nbPersonnes){
                            min = nbPersonnes;
                            tableChoisie = tcourant->num;
                        }
                        

                        //On parcourt les tables reservees pour la date donnee
                        for(i = 0; i < courant->nbtables; i++){
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
                        for (i = 0; i < courant->nbtables; i++){
                            fprintf(fres, "%02d ", courant->tables[i]);
                        }
                        return;
                    //Si une table est dispo
                    }else{
                        fprintf(fres, "%-10s %02d ", dateRes, courant->nbtables + 1);
                        for (i = 0; i < courant->nbtables; i++){
                            fprintf(fres, "%02d ", courant->tables[i]);
                        }
                        fprintf(fres, "%02d\n", tableChoisie);
                    }
                //Si la reservation n'est pas la bonne, on la print simplement
                }else{
                    fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables);
                    for (i = 0; i < courant->nbtables; i++){
                        fprintf(fres, "%02d ", courant->tables[i]);
                    }
                    fprintf(fres, "\n");
                }
                courant = courant->suivant;
            }
            fclose(fres);
        
        //Si la reservation n'existe pas
        }else{
            //On ouvre le fichier en mode "append" pour pouvoir ajouter a  la suite de celui ci
            tcourant = tdeb;
            //Fait les tests pour trouver une table adequate
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

            //Si aucune table n'est adequate
            if (tableChoisie == 999){
                printf("\nLe restaurant n'a pas de table disponible pour autant de personnes !");
                return;
            //SI une table est adequate;
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

    //Variables utile pour recuperer la date du jour
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
    //Demande d'entrer une date a  l'utilisateur
    printf("\nDate de la reservation: (FORMAT: JJ-MM-AAAA)\n");
    scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
    
    //Verifie si la date entree est correcte
    int existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    while(existe != 1){
        printf("!! DATE NON EXISTANTE !!\nDate de la reservation: (FORMAT: JJ-MM-AAAA)\n");
        scanf("%2d-%2d-%4d", &jourRes, &moisRes, &anneeRes);
        existe = jourExiste(jourRes, moisRes, anneeRes, anneeAuj, moisAuj, jourAuj);
    }

    reservation *courant, *deb;
    courant = lectureReservations();
    deb = courant;

    int resExiste = 0, numTable;

    char dateRes[11];
    sprintf(dateRes, "%02d-%02d-%04d", jourRes, moisRes, anneeRes);

    printf("Table a annuler: ");
    scanf("\n%2d", &numTable);

    //On parcourt la liste des reservation
    while (courant->suivant != NULL){
        //On regarde si la date entree est presente
        if(strcmp(dateRes, courant->date) == 0){
            for (i = 0; i < courant->nbtables; i++){
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

    //Si la reservation voulue n'existe pas
    if (resExiste == 0){
        printf("\n!! CETTE TABLE N'EST PAS RESERVE POUR LE JOUR SUIVANT: %-10s !!\n", dateRes);
        return;
    }

    fres = fopen("VoiturierPlasschaertReservations.dat", "w");
    //Si la reservation existe, on la retire
    courant = deb;
    while (courant->suivant != NULL){
        //Si c'est la ligne qu'on cherche a changer
        if(strcmp(dateRes, courant->date) == 0){
            //Si le nb de table == 1 alors il n'y en restera plus apra¨s suppresion donc on supp la ligne entia¨re
            if(courant->nbtables == 1){
                fprintf(fres, "");
            //SINON on print seulement les tables qu'on garde
            }else{
                fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables - 1);
                for (i = 0; i < courant->nbtables; i++){
                    if (courant->tables[i] != numTable){
                        fprintf(fres, "%02d ", courant->tables[i]);
                    }
                }
                fprintf(fres, "\n");
            }
        //Si c'est pas la ligne a changer, on print tout
        }else{
            fprintf(fres, "%-10s %02d ", courant->date, courant->nbtables);
            for (i = 0; i < courant->nbtables; i++){
                fprintf(fres, "%02d ", courant->tables[i]);
            }
            fprintf(fres, "\n");
        }
        courant = courant->suivant;
    }
    fclose(fres);
}
// ----------------------------------------- AFFICHER LES RESERVATIONS ------------------------------------
void afficherReservations(){
    FILE *fdat, *fres;
    fdat = fopen("VoiturierPlasschaertReservations.dat", "r");
    reservation * lectureReservations();
    //Variables utile pour recuperer la date du jour
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
            for (i = 0; i < courant->nbtables; i++){
                printf("| %02d ", courant->tables[i]);
            }
            printf("\n");
        }
        courant = courant->suivant;
    }
    printf("=====================================================\n");

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

// ----------------------------------------- LECTURE FICHIER PERSONNEL -------------------------------------------
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

// ----------------------------------------- INDENTIFICATION -------------------------------------------
int identification(){

    //Declaration des variables ainsi que du fichier
    int matricule, matEmp;
    char prenom[21];
    FILE *fdat = fopen("VoiturierPlasschaertPersonnel.dat", "r");

    //Demande le numero de matricule de l'utilisateur pour qu'il s'identifie
    printf("Entrez votre matricule: ");
    scanf("%3d", &matricule);
	
	if(matricule == 0){
		return 0;
	}
    //Parcours la liste des utilisateurs pour voir si la personne a entre un bon matricule
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
	
    //Si le test entre les deux matricule echoue
    printf("\n!! IDENTIFICATION ECHOUEE  !!\n");
    fclose(fdat);
    return -1;
}


// ----------------------------------------- JOUR DE LA SEMAINE -------------------------------------------
int jourSemaine(int jour, int mois, int annee){
    int joursemaine = (jour += mois < 3 ? annee-- : annee - 2, 23*mois/9 + jour + 4 + annee/4- annee/100 + annee/400)%7; 
    if (joursemaine == 0){
        joursemaine = 7; 
    }
    return joursemaine;
}



// ----------------------------------------- PROGRAMME PRINCIPAL -------------------------------------------
int main()
{
    //Ouverture des fichiers
    FILE *ftab, *fmenu, *fboi, *fpersonnel, *fhoraire;
    int numEmploye;
    //Declaration des fonctions et variables;
    int running = 1, identification(), jourSemaine(int, int, int);
   
    table *tdeb, *tcourant;
    personnel *pcourant, *pdeb;
    listeBoissons *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	listePlats *platcourant, *platdeb,*platsuivant;
	platcourant = lecturePlat();
    
    
    //Lecture du fichiers reprenant les tables dans la fonction lectureTable()
    tcourant = lectureTable();
    pcourant = lecturePersonnel();
	tdeb = tcourant;
	platdeb = platcourant;
	bdeb = bcourant;
	
	
	
	
	
	
	
	
	
    //Si la personne s'identifie bien, on rentre dans la boucle, sinon one ne rentre pas dedans
    running = -1;
	while(running !=0){
		running = identification();
		numEmploye = running;
    //Si c'est le gerant -> menu admin
    
    if ((running == 999)||((running/100)==1)){
        running = 1;
        while (running == 1)
        {
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 3: PERSONNEL | 4: IMPRIMMER TICKET | 5: VIDER CAISSE | AUTRE: QUITTER)\n");
            scanf("%d", &option);

            //L'utilisateur veut encoder une reservation
            if(option == 1){
                printf("1: AJOUTER UNE RESERVATION | 2: ANNULER UNE RESERVATION | 3: AFFICHER UNE RESERVATION | AUTRE: QUITTER\n");
                scanf("%2d", &option);
                if (option == 1){
                    reserver(tdeb);
                }else if (option == 2){
                    annulerReservation();
                }
                else if(option == 3){
                	afficherReservations();
				}

            //L'utilisateur veut encoder une commande
            }else if(option == 2){
				faireCommande(platdeb,bdeb,tdeb);
            //L'utilisateur veut changer le personnel;
            }else if(option == 3){
                printf("1: AJOUTER UN EMPLOYER | 2: LISTE DES EMPLOYES\n");
                scanf("%d", &option);
                if (option == 1){
                    ajouterPersonnel(pdeb);
                }else if(option == 2){
                    afficherPersonnel(pdeb);
                }
            //L'utilisateur veut quitter le prog
            }
			else if(option == 4){
				imprimerTicket(tdeb,numEmploye);
			}
			else if(option == 5){
				nettoyerCaisse();
			}
			else{
                break;
            }
        }
    //Si ce n'est qu'un simple employe -> menu employe 
    }else if (running > 0){
        running = 1;
        while (running == 1)
        {
            
            int option = 3;
            printf("\nQue voulez vous faire ? (1: RESERVATION | 2: COMMANDE | 3: IMPRIMMER TICKET | AUTRE: QUITTER)\n");
            scanf("%d", &option);

            //L'utilisateur veut encoder une reservation
            if(option == 1){
                printf("1: AJOUTER UNE RESERVATION | 2: ANNULER UNE RESERVATION | 3: AFFICHER UNE RESERVATION | AUTRE: QUITTER\n");
                scanf("%2d", &option);
                if (option == 1){
                    reserver(tdeb);
                }else if (option == 2){
                    annulerReservation();
                }
                else if(option == 3){
                	afficherReservations();
				}

            //L'utilisateur veut encoder une commande
            }else if(option == 2){
				faireCommande(platdeb, bdeb,tdeb);
			
            
            }
            //imprime le ticket
			else if(option == 3){
				imprimerTicket(tdeb,numEmploye);
			}
			//L'utilisateur veut quitter le programme
			else{
                break;
            }
        }
        
    }
		if(numEmploye == 0){
			break;
		}
        	
    }

    printf("\n** FIN DU PROGRAMME **\n");
}

