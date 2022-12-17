#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int i,j; //declaration general pour les compteurs
//structure table 


typedef struct platticket{
	int id; //id du plats
	char nom[35]; //nom du plat
	float prix; //prix du menu
}platticket;


typedef struct boissonticket{
	int id; //id de la boisson
	char nom[35]; //nom de la boisson
	float prix; //prix de la boisson
}boissonticket;


typedef struct ticket{
	int id,nbplat,nbboisson,tab; 	//id de la commande,nombre de plat, nombre de boisson,table concern�e
	float prixtotal;			//prix total de la commande
	struct platticket plat[60]; 		//boisson command�e
	struct boissonticket boisson[60];       //plat command�
					
}ticket;
typedef struct table{
    int num;                    //Numéro de la table
    int nbPersonnes;            //Nombre de personnes pouvant être à cette table
    struct table *suivant;      //Table suivant de la liste chainée
    struct ticket ticket;
}table;


//structure de boisson
typedef struct boisson{
	int id; //id de la boisson
	char nom[35]; //nom de la boisson
	float prix; //prix de la boisson
	struct boisson *suivant;
}boisson;




typedef struct plat{
	int id; //id du plats
	char nom[35]; //nom du plat
	float prix; //prix du menu
	struct plat *suivant; 
}plat;





void ecriturelisteBoi(boisson *bcourant){
	
	boisson *bdeb, *bsuivant;
	
	while (bcourant!=NULL){       
        printf("%2d %s %5.2f\n",bcourant->id, bcourant->nom,bcourant->prix);
        
        bcourant = bcourant->suivant;
        
        
    }
}



boisson * lectureBoisson(){
	//ouverture des fichiers
	int i;
	FILE *fboisson;
	fboisson = fopen("VoiturierPlasschaertBoisson.dat","r");
	boisson *bdeb, *bcourant, *bsuivant;

    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    bcourant = malloc(sizeof(boisson));
    bdeb = bcourant;
    
    
    fscanf(fboisson, "%2d", &bcourant->id);
    
    i=0;
    //Commencement de la boucle de lecture
    while (!feof(fboisson)){       
        fscanf(fboisson, "%s %f", &bcourant->nom,&bcourant->prix);
        
        bsuivant = malloc(sizeof(boisson));
        bcourant->suivant = bsuivant;
		i++;
        bcourant = bsuivant;
        fscanf(fboisson, "%2d", &bcourant->id);
        
    }
    //mise Null dans le dernier element;
    bcourant = bdeb;
    for(j=1;j<i;j++){
    	bcourant = bcourant->suivant;}
	bcourant->suivant =NULL;
    //affectation de la premiere structure de la liste à bcourant
    

    return bdeb;
	
	
	
}




plat * lecturePlat(){
	//ouverture des fichiers
	
	FILE *fplat;
	fplat = fopen("VoiturierPlasschaertMenu.dat","r");
	plat *pdeb, *pcourant, *psuivant;




    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    pcourant = malloc(sizeof(plat));
    pdeb = pcourant;
    fscanf(fplat, "%2d", &pcourant->id);
    i=0;
    
    //Commencement de la boucle de lecture
    while (!feof(fplat)){       
        fscanf(fplat, "%s %f", &pcourant->nom,&pcourant->prix);
        psuivant = malloc(sizeof(plat));
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

void faireCommande(plat *pcourant, boisson *bcourant, table *tcourant){
	int tab, type, id,comsui=0;
	
	boisson *bdeb,*bsuivant;
	plat  *pdeb,*psuivant;
	table *tdeb,*suivant;
	void ajoutart(int, int , int, plat*, boisson*,table*);



	//demande de la table.
	printf("Veillez entrer la table concernee :  \n");
	scanf("%2d",&tab);
	
	//todo lire fichier table pour le nombre de table 
	if((tab>=1)&&(tab<=10)){
		
		//demande si plat ou boisson (si 0 stop la commande
		printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
		scanf("%2d",&type);
		while(type != 0){
			if((type==2)||(type==1)){
				//demande de l'id de larticle
				printf("Entrez l'id de l'article : \n");
				scanf("%d",&id);
				//appel de la fonction d'ajout � une commande.
				ajoutart(tab,type,id, pcourant,bcourant,tcourant);
				
				printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%d",&type);
			}
			else{
				printf("Entrez une donnee valide ! \nTapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%d",&type);
			}
		}
		
		printf("Merci.");
	}
}


void ajoutart(int tab, int type, int id, plat *pcourant, boisson *bcourant, table *tcourant){
	int taille;
	plat *psuivant, *pdeb;
	boisson *bsuivant,*bdeb;
	pdeb = pcourant;
	bdeb = bcourant;
	
	while(tcourant->num != tab){
		tcourant = tcourant->suivant;
		
	}
	
	if(type ==1){
		while(pcourant->id != id){
			pcourant = pcourant->suivant;
		}
		tcourant->ticket.nbplat ++;
		tcourant->ticket.plat[tcourant->ticket.nbplat].id = pcourant->id;
		strcpy(tcourant->ticket.plat[tcourant->ticket.nbplat].nom,pcourant->nom);
		tcourant->ticket.plat[tcourant->ticket.nbplat].prix = pcourant->prix;
		tcourant->ticket.prixtotal += pcourant->prix;
		
		printf("%2d %5.2f %s %5.2f",tcourant->ticket.plat[tcourant->ticket.nbplat].id,tcourant->ticket.plat[tcourant->ticket.nbplat].nom, tcourant->ticket.plat[tcourant->ticket.nbplat].prix, tcourant->ticket.prixtotal);
		//todo je vais faire un gros dodo 
	}
	
	
}

void faireTicket(table*table ){
	//ouverture des fichiers.
	FILE*fdirect, *fcaisse;
	fdirect = fopen("VoiturierPlasschaertTicketCli.res","w");
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","a");
	//decla des variables
	
	
	
	//Fonction qui affiche la date et l'heure du ticket
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(fdirect,"      %s ",buffer);
	
	
	
	
	
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
    for (i = 0; i < n; i++){
        tcourant = tcourant->suivant;
    }
    tcourant->suivant = NULL;

    return tdeb;
}



main(){
	void faireTicket(table *table);
	boisson *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	plat *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
	table *tcourant,*tdeb,*tsuivant;
	tcourant = lectureTable();
	
    

    
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
	
	faireCommande(pcourant, bcourant,tcourant);
    
    
    
    
	
	
}

















