#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int i,j; //declaration general pour les compteurs
//structure table 
typedef struct table{
    int num;                    //NumÃ©ro de la table
    int nbPersonnes;            //Nombre de personnes pouvant Ãªtre Ã  cette table
    struct table *suivant;      //Table suivant de la liste chainÃ©e
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

typedef struct commande{
	int id,nbplat,nbboisson; 	//id de la commande,nombre de plat, nombre de boisson
	table table;				//table concernée
	float prixtotal;			//prix total de la commande
	struct boisson *boisson[20]; 		//boisson commandée
	struct plat *plat[18];
	struct commande *suivante;
	
					//plat commandé
}commande;


typedef struct ticket{
	int id;						//id du ticket
	commande commande[15];		//vecteur avec les commandes du ticket

}ticket;


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
    //affectation de la premiere structure de la liste Ã  bcourant
    

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
    for(j=0;j<i;j++){
    	pcourant = pcourant->suivant;
	}
	pcourant->suivant = NULL;
    return pcourant;
	
}



void faireCommande(boisson *bcouranrt, plat *pcourant, commande *ccourant){
	//declaration des variables 
	int contu,id,tab;
	void ajoutart(int, int,int,boisson *, plat *, commande *);
	
	//Demande de la table concernée
	printf("Entrez la table concernée:\n");
	scanf("%2d",&tab);
	//boucle tantque l'utilisateur n'interomp pas
	contu = 1;
	while(contu >=1){
		//demande des données du plats/boisson
		printf("Entrez 1 pour les plats, 2 pour les boissons\n");
		scanf("%2d",&contu);
		if((contu>=1)){
			//id du plat
			printf("Entrez l'id:");
			scanf("%2d",&id);
			
			
			
			//ajout de l'article dans la commande
			ajoutart(contu,id,tab,&bcourant, &pcourant, &ccourant);
			
			
		}
		}
		//fin
		printf("Commande finie.");
		
}





void ajoutart(int type, int id, int tab,boisson *bcourant,plat *pcourant, commande *ccourant){

	//decla variable puis remise au premier therme.
	boisson *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	bcourant = bdeb;
	plat *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
	pcourant = pdeb;
	commande *ccourant, *cdeb,*csuivant;
	int taille; 
	printf("%2d",pcourant->id);
	//creation de la commande
	ccourant = malloc(sizeof(commande));
    cdeb = ccourant;
    
    //ajout de la table concernee 
    ccourant->id = tab;
    ccourant->nbboisson =0;
    ccourant->nbplat = 0;
    
    //ajout du plat
    if(type == 1){
    	//boucle pour connaitre la taille de la chaine
	    while(pcourant->suivant != NULL){
			pcourant = pcourant->suivant;
			printf("%2d %s %5.2f\n",pcourant->id, pcourant->nom, pcourant->prix);
			
		}
		
		taille = pcourant->id;
		pcourant = pdeb;
		printf("%3d",taille);
		
    	//verification que le plat existe
    	if(id<=taille){
    		
	    	//boucle qui recherche le bon plat.
	    	while(id != pcourant->id){
	        	pcourant = pcourant->suivant;
	        	printf("%2d",pcourant->id);
			}
			
			//ajout du plat dans la commande
			ccourant->nbplat +=1;
			ccourant->plat[ccourant->nbplat] = pcourant;
		}
		
		//si le plat n'existe pas 
	else{
		printf("Ce plat n'existe pas.\n");
	}
	}
	else if(type == 2){
		
		//boucle pour connaitre la taille de la chaine
	    while(bcourant != NULL){
			bcourant = bcourant->suivant;	
		}
		taille = bcourant->id;
		bcourant = bdeb;
		printf("%3d",taille);
		
		if(id <=taille){
			
		
	    	while(id != bcourant->id){
	    		
	        	bcourant = bcourant->suivant;
			}
			ccourant->nbboisson +=1;
			ccourant->boisson[ccourant->nbboisson] = bcourant;
		}
		else{
			printf("Cette boisson n'existe pas\n");
		}
	}
	else{
		printf("erreur\n");
	}
    
    
}







void faireTicket(int tab){
	FILE*fdirect, *fcaisse;
	fdirect = fopen("VoiturierPlasschaertTicketCli.res","w");
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","a");
	boisson *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	plat *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
	commande *ccourant, *cdeb,*csuivant;
	//Fonction qui affiche la date et l'heure du ticket
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(fdirect,"      %s ",buffer);
	
	bcourant = bdeb;
	while (sizeof(boisson)){
	       
        printf("%2d %s %f",bcourant->id,bcourant->nom,bcourant->prix);
        
        bcourant->suivant = bsuivant;
        bcourant = bsuivant;
        
    }
}







main(){
	boisson *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	plat *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
	commande *ccourant, *cdeb,*csuivant;
	
	//ecriturelisteBoi(bcourant);
	faireCommande(&bcourant,&pcourant,&,ccourant);
	faireTicket();
	
	//TODO faire id des plats 
	
    
    
    


}
