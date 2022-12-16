#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
	boisson boisson[20]; 		//boisson commandée
	plat plat[18];
	struct commande *suivante;
	
					//plat commandé
}commande;



typedef struct ticket{
	int id;						//id du ticket
	commande commande[15];		//vecteur avec les commandes du ticket

}ticket;


boisson * lectureBoisson(){
	//ouverture des fichiers
	
	FILE *fboisson;
	fboisson = fopen("VoiturierPlasschaertBoisson.dat","r");
	boisson *bdeb, *bcourant, *bsuivant;

    //Lecture du fichier et affectation des differentes valeurs lues dans les variables de la structure table
    bcourant = malloc(sizeof(boisson));
    bdeb = bcourant;
    
    
    fscanf(fboisson, "%2d", &bcourant->id);
    
    
    //Commencement de la boucle de lecture
    while (!feof(fboisson)){       
        fscanf(fboisson, "%s %f", &bcourant->nom,&bcourant->prix);
        
        bsuivant = malloc(sizeof(boisson));
        bcourant->suivant = bsuivant;
        bcourant = bsuivant;
        fscanf(fboisson, "%2d", &bcourant->id);
        
    }
    //affectation de la premiere structure de la liste Ã  bcourant
    bcourant = bdeb;

    return bcourant;
	
	
	
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
    
    
    //Commencement de la boucle de lecture
    while (!feof(fplat)){       
        fscanf(fplat, "%s %f", &pcourant->nom,&pcourant->prix);
        
        psuivant = malloc(sizeof(plat));
        pcourant->suivant = psuivant;
        pcourant = psuivant;
        fscanf(fplat, "%2d", &pcourant->id);
        
    }
    //affectation de la premiere structure de la liste Ã  bcourant
    pcourant = pdeb;

    return pcourant;
	
	
	
}

commande *faireCommande(){
	//declaration des variables 
	int contu,id,tab;
	
	//Demande de la table concernée
	printf("Entrez la table concernée:\n");
	scanf("%2d",&tab);
	//boucle tantque l'utilisateur n'interomp pas
	contu = 1;
	while(contu >=1){
		//demande des données du plats/boisson
		printf("Entrez 1 pour les plats, 2 pour les boissons\n");
		scanf("%2d",&contu);
		
		//id du plat
		printf("Entrez l'id:");
		scanf("%2d",&id);
		//ajout de l'article dans la commande
		ajoutart(contu,id,tab);
		}
		//fin
		printf("Commande finie.");
			
}

void ajoutart(int type, int id, int tab){
	//decla variable;
	boisson *bcourant,*bdeb;
	bcourant = lectureBoisson();
	plat *pcourant, *pdeb;
	pcourant = lecturePlat();
	commande *ccourant, cdeb;
	
	
	//creation de la commande
	ccourant = malloc(sizeof(commande));
    cdeb = ccourant;
    //ajout de la table concernee 
    ccourant->id = tab;
    ccourant->nbboisson =0;
    ccourant->nbplat = 0;
    
    
    
    //ajout du plat
    if(type == 1){
    	
    	while(id != pcourant->id){
    		pcourant->suivant = psuivant;
        	pcourant = psuivant;
		}
		ccourant->nbplat +=1;
		ccourant->plat[nbplat] = pcourant->plat;
		
		
	}
	if(type == 2){
    	
    	while(id != bcourant->id){
    		bcourant->suivant = bsuivant;
        	bcourant = bsuivant;
		}
		ccourant->nbboisson +=1;
		ccourant->boisson[nbboisson] = bcourant->boisson;
		
		
		
	}
    
    
    

	
	
	
}
void faireTicket(commande []commande){
	FILE*fdirect, fsoiree;
	fdirect = fopen("VoiturierPlasschaertTicketCli.res","w");
	fcaisse = fopen("VoiturierPlasschaertTicketCaisse.res","a");
	
	
}







main(){
	
	
	int i;
	boisson *bcourant,*bdeb;
	
	bcourant = lectureBoisson();
	plat *pcourant,*pdeb;
	pcourant = lecturePlat(); 
	faireCommande();
    
    
    
    


}
