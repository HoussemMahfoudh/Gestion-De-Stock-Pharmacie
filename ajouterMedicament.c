/***************************************************************************************
*** Fichier qui contient les fonctions qui permettent a ajouter un medicament valide ***
****************************************************************************************/





/* Fonction qui permet d'ajouter un nouveau fournisseur a liste des fournisseurs correspondante */

void ajouterFournisseur(Medicament *med){
	int nbFour,i;
	Fournisseur fournisseur;
	
	/* Boucle pour permette au utilisateur d'ajouter au max 3 fournisseurs et au min 1 */
	do{
		printf("Donner le nombre des fournisseurs a ajouter : ");
		scanf("%d",&nbFour);
	}while(nbFour < 1 || nbFour >3);
	
	for(i=0;i<nbFour;i++){
		printf("Donner le nom du fournisseur %d : ", i+1);
		fflush(stdin);
		gets(fournisseur.nom);
		printf("Donner l adresse du fournisseur : ");
		fflush(stdin);
		gets(fournisseur.adresse);
		printf("Donner le numero du fournisseur : ");
		scanf("%d",&fournisseur.telephone);
		med->listeFournisseur[i]=fournisseur; /* Sauvegarde du fournisseur saisit dans la case correspondate du tableau listeFournisseur */ 
	}
	med->nombreFournisseur = nbFour; /* Sauvegarde du nombre des fournisseurs saisient dans la variable nombreFournisseur du medicament */
	printf("\nFournisseur ajouter avec succes\n");
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


/* Fonction qui permet de rechercher la reference d'un medicament passé en paramètre dans la liste : 
	- Retourne 0 si aucune reference trouvé
	- Retourne 1 cas contraire */
	
int rechercheReference(Medicament *MedTab, int *n, char ref[100]){
	int i=0;
	
	while(strcmp(MedTab[i].lot.reference,ref)!=0 && i<=*n){
		i++;
	}
	
	if(i>*n){
		return 0;
	}else{
		return 1;
	}
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/



/* Fonction qui permet la controle de saisie des date:
	* Condition d'acception : 
		- Date de fabrication valide
		- Date de preemption valide et plus grande que la date de fabrication */
void dateControle(Lot *lot){
	int correct=1;
	
	do{
	
		printf("Donner le jour du fabrication : ");
		scanf("%d",&lot->dateFabrication.jour);
		printf("Donner le mois du fabrication : ");
		scanf("%d",&lot->dateFabrication.mois);
		printf("Donner l'annee du fabrication : ");
		scanf("%d",&lot->dateFabrication.annee);
		
		switch(lot->dateFabrication.mois)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 12:
			if(lot->dateFabrication.jour>31){
				correct=0;
			}else{
				correct=1;
			}
			break;
			
			case 4:
			case 6:
			case 9:
			case 10:
			case 11:
				if(lot->dateFabrication.jour>30)
				{
					correct=0;
				}else{
					correct=1;
				}	
				
			break;
			
		case 2 :
		
   			if(((lot->dateFabrication.annee/4==0)&&(lot->dateFabrication.annee/100!=0))||((lot->dateFabrication.annee/400)==0)){
   				if(lot->dateFabrication.jour>29){
   					correct=0;
				}else{
					correct = 1;
				}  
			}
			else{
				if(lot->dateFabrication.jour>28){
					correct=0;
				}else{
					correct = 1;
				}
			}	
		break;
		default:
			correct=0;		
		}
		
	}while(correct==0);
	
	int correctP=1;
	int correctPDat=1;

	do{
		printf("Donner le jour du preemption : ");
		scanf("%d",&lot->datePreemption.jour);
		printf("Donner le mois du preemption : ");
		scanf("%d",&lot->datePreemption.mois);
		printf("Donner l annee du preemption : ");
		scanf("%d",&lot->datePreemption.annee);	
		
		switch(lot->datePreemption.mois)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 12:
			if(lot->datePreemption.jour>31){
				correctPDat=0;
			}else{
				correctPDat=1;
			}
			break;
			
			case 4:
			case 6:
			case 9:
			case 10:
			case 11:
				if(lot->datePreemption.jour>30)
				{
					correctPDat=0;
				}else{
					correctPDat=1;
				}	
				
			break;
			
			case 2 :
				
	   			if(((lot->datePreemption.annee/4==0)&&(lot->datePreemption.annee/100!=0))||((lot->datePreemption.annee/400)==0)){
	   				if(lot->datePreemption.jour>29){
	   					correctPDat=0;
					}
					else {
						correctPDat = 1;
					}  
				}
				
				else if (lot->datePreemption.jour>28){
						correctPDat=0;
						
				}else{
					correctPDat = 1;		
				}
					
			break;	
			default:
				correctPDat=0;		
		}           
		
		if (lot->dateFabrication.annee<lot->datePreemption.annee)
       		correctP=1;

    	else if (lot->dateFabrication.annee > lot->datePreemption.annee)
       		correctP=-1;

    	if (lot->dateFabrication.annee == lot->datePreemption.annee)
    	{
	         if (lot->dateFabrication.mois<lot->datePreemption.mois)
	              correctP=1;
	         else if (lot->dateFabrication.mois>lot->datePreemption.mois)
	             correctP=-1;
	         else if (lot->dateFabrication.jour<lot->datePreemption.jour)
	              correctP=1;
	         else if(lot->dateFabrication.jour>lot->datePreemption.jour)
	              correctP=-1;
	         else
	               correctP=0;
    	}

		
	} while((correctP==-1)||(correctP==0)||(correctPDat == 0));
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/

/* Fonction qui permet l'ajout des informations du lot du médicament qui est en cours d'ajout */
void ajouterLot(Medicament *med,Medicament *MedTab, int *n){
	Lot lot;
	if(*n == 0 ){ /* Si c est le premier médicament a ajouter il est inutile de chercher la reference si'il est valide ou non */
		printf("Donner le lot du medicament : ");
		fflush(stdin);
		gets(lot.reference);
		dateControle(&lot); /* Appel de la fonction dateControle() */
	}else{
		do{
			printf("Donner le lot du medicament : ");
			fflush(stdin);
			gets(lot.reference);
		}while(rechercheReference(&*MedTab,n,lot.reference)!=0); /* Appel de la fonction rechercheReference() */
		dateControle(&lot); /* Appel de la fonction dateControle() */
	}
	
	printf("\nLot ajouter avec succes\n");
	med->lot=lot;
	
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/




/* Fonction qui permet l'ajout d'un nouveau medicament */
void ajouterNouveauMedicament(Medicament *MedTab,int *n){
	Medicament med;
	int i;
	/* Ouverture du fichier FMed.txt en mode ecriture binaire */
	FILE * FMed = fopen("FMed.txt","wb");
	if(FMed == NULL){
		printf("\nERREUR : Impossible d ouvrir le fichier.");
		exit(1);
	}

		if(*n == 0){
			med.num=*n+1;
		}else{
			med.num=MedTab[*n-1].num+1;
	
		}
		
	
		printf("Donner le nom du medicament : ");
		fflush(stdin);
		gets(med.nom);
		printf("Donner le laboratoire du medicament : ");
		gets(med.laboratoire);	
		
		ajouterLot(&med,&*MedTab,n); /* Appel de la fonction ajouterLot */ 
		
		printf("Donner le prix du medicament : ");
		scanf("%f",&med.prix);
		printf("Donner la quantite en stock du medicament : ");
		scanf("%d",&med.quantiteStock);
		
		ajouterFournisseur(&med); /* Appel de la fonction ajouterFournisseur */
		do{
			printf("Donner le secteur de stockage du medicament : ");
			scanf("%d",&med.secteurStockage);
		}while(med.secteurStockage<1 || med.secteurStockage > 5);
		
	
		MedTab[*n]=med; /* Sauvegarde du médicament dans la case correspondante  */ 
		*n=*n+1;

	printf("\nMedicament ajouter avec succees\n");
	fwrite (MedTab, sizeof(Medicament),*n, FMed ); /* Sauvegrade des informations de tout les medicaments dans le ficher FMed.txt */
	fclose(FMed);

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


