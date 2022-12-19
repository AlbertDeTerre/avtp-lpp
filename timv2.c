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

//Structure table
typedef struct table{
    int num;                    //NumÃ©ro de la table
    int nbPersonnes;		//Nombre de personnes pouvant Ãªtre Ã  cette table
	struct ticket ticket;            
    struct table *suivant;      //Client suivant de la liste chainÃ©e
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
	//demande de la table.
	printf("Veillez entrer la table concernee :  \n");
	scanf("%d",&tab);
	if((tab>=1)&&(tab<=i)){
		
		//demande si plat ou boisson (si 0 stop la commande
		printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
		scanf("%d",&type);
		while(type != 0){
			if((type==2)||(type==1)){
				//demande de l'id de larticle
				printf("Entrez l'id de l'article : \n");
				scanf("%d",&id);
				//appel de la fonction d'ajout à une commande.
				ajoutart(tab,type,id,pcourant, bcourant,tablecourant);
				printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%d",&type);
				
			}
			//entree non valide, le rpogramme previens et repose la question. 
			
			else{
				printf("Entrez une donnee valide ! \nTapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%d",&type);
			}
		}
		
		printf("Merci.");
	}
	else{
		printf("Cette table n'existe pas.\n");
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
	//recherche de la table concernée. Sortie de boucle s'il trouve la table ou si la table arrive a NULL
	while((tablecourant != NULL)&&(tablecourant->num != tab)){
		tablecourant = tablecourant->suivant;
		
	}
	
	//s'il la boucle n'a pas trouvé la table alors la table n'est pas dans le restaurant.
	if(tablecourant->suivant == NULL){
		printf("Cette table n'est pas dans le restaurant.\n");
		return;
	}
	printf("test");
	//Si l'article est un plat
	if(type ==1){
		
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

void nettoyerCaisse(){
	FILE*fcaisse;
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","w");
}










main(){
	listeBoissons *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	listePlats *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
    table *tablecourant,*tabledeb, tablesuivant;
    tablecourant = lectureTable();
    tabledeb = tablecourant;
    
    
    
    faireCommande(pcourant, bcourant, tablecourant);
    
    imprimerTicket(tabledeb,123);
    
    
    
    
    
//    while(tablecourant != NULL){
//    	printf("%2d %2d\n", tablecourant->num,tablecourant->nbPersonnes);
//    	for(i=1; i<= tablecourant->ticket.nbplats;i++){
//    		printf("%2d %s %5.2f\n",tablecourant->ticket.plats[i].id,tablecourant->ticket.plats[i].nom,tablecourant->ticket.plats[i].prix);
//		}
//    	tablecourant = tablecourant->suivant;
//    	
//	}
	
    
//    while (bcourant!=NULL){       
//        
//        printf("%2d %s %5.2f\n",bcourant->id, bcourant->nom,bcourant->prix);
//        bcourant = bcourant->suivant;
//        
//    }
//    
//    while (pcourant!=NULL){       
//        printf("%2d %s %5.2f\n",pcourant->id, pcourant->nom,pcourant->prix);
//        pcourant = pcourant->suivant;
//        
//        
//    }
    
    
    
    
	
	
}

















