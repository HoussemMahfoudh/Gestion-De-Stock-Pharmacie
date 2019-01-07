/***************************************************************************************
****** Fichier qui contient les fonctions qui permettent a afficher les information ******
****** 					concernant les medicaments périmées 						******
**********************************************************************************************/



//fonction qui indique les medicaments perimées en comparant la date de préemption de chaque medicament avec la date du systeme 
int medicPerimeControl(Lot *lot){
	//Lot *lot;
	//int correctP=0;
	time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);

  
    int yearSys=instant.tm_year+1900;  /* pour obtenir l'annee ,le mois et le jour du systeme on a utilisé la structure tm prédifinie dans <time.h>*/
    int monthSys= instant.tm_mon+1;
    int daySys= instant.tm_mday;
    
    	
    	if (yearSys<lot->datePreemption.annee)
       	return -1;

    	else if (yearSys>lot->datePreemption.annee){
    		return 1;	
		}

    	if (yearSys == lot->datePreemption.annee)
    	{
	        if (monthSys<lot->datePreemption.mois)
	            return -1;
	        else if (monthSys>lot->datePreemption.mois){
	        	return 1;
	        	
			}
	        else if (daySys<lot->datePreemption.jour)
	            return -1;
	        else if(daySys>lot->datePreemption.jour){
	        	return 1;
	        	
			}   
	        else{
	        	return 0;
			}
    	}
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/

//fonction qui affiche les medicaments périmés
void afficheMedPerim(Medicament *MedTab , int n){
	int i;
	printf ("\n------------------------------------------------------------------------\n");
	printf("Nom\tRefLot\tSecteur de Stockage\tQantite\n");
	printf("-------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		if(medicPerimeControl(&MedTab[i].lot)==1){
			printf("%s\t%s\t%10d\t\t%5d",MedTab[i].nom,MedTab[i].lot.reference,MedTab[i].secteurStockage,MedTab[i].quantiteStock);
		}	
	}
	printf("\n\n");
	
	FILE *FMed = fopen("FMed.txt","wb");
	if(FMed == NULL){
	printf("\nERREUR: Impossible d ouvrir le fichier.");
	exit(1);}
	
	fwrite (MedTab, sizeof(Medicament),n, FMed );
	fclose(FMed);
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/
