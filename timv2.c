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

void faireCommande(plat *pcourant, boisson *bcourant, commande ccourant){
	int tab, type, id;
	
	//demande de la table.
	printf("Veillez entrer la table concernee :  \n");
	scanf("%2d",&tab);
	if((tab>=1)&&(tab<=10){
		
		//demande si plat ou boisson (si 0 stop la commande
		printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
		scanf("%2d",&type);
		while(type != 0){
			if((type==2)||(type==1)){
				//demande de l'id de larticle
				printf("Entrez l'id de l'article : \n");
				scanf("%2d",&id);
				//appel de la fonction d'ajout à une commande.
				ajoutart(tab, type,id, &pcourant,&bcourant,&ccourant);
				printf("Tapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%2d",&type);
			}
			else{
				printf("Entrez une donnee valide ! \nTapez 1 pour un plat, 2 pour une boisson et 0 pour arreter l'encodage: \n");
				scanf("%2d",&type);
			}
		}
		
		
		
		
		
	}
	
	
}


main(){
	boisson *bcourant,*bdeb,*bsuivant;
	bcourant = lectureBoisson();
	plat *pcourant, *pdeb,*psuivant;
	pcourant = lecturePlat();
	commande *ccourant, *cdeb,*csuivant;
	
}

















