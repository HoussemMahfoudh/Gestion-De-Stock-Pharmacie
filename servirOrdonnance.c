/***************************************************************************************
****** Fichier qui contient les fonctions qui permettent a servir une ordonnance ******
****************************************************************************************/


int medicPerimeControl2(Lot *lot){
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



/* Fonction qui prend en paramètre le numero du médicament a chercher et qui :
	- Retourne -1 si aucun medicament trouvé
	- Retourne la quantité en stock du médicament trouvé  */
int rechercherMedicamentOrd(Medicament *medTab, int n, int medicNum, int *indice){
	int numEl = n, i = 0;
	
	
	if(medicNum>medTab[numEl-1].num || medicNum <medTab[0].num){
		return -1;
	}else{
		while((medTab[i].num != medicNum) && (i < n)){
			i++;
		}
		if (i > (numEl-1)){
			return -1;
		}else if(medicPerimeControl2(&medTab[i].lot) == 1 ){
			return -2;
		}else{
			*indice = i;
			return medTab[i].quantiteStock;
		}	
	}
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/



/* Fonction qui permet a l'utilisateur de saisir la liste des médicaments a vendre et qui affiche les informations
	des médicaments et calcul et affiche le total */
void servirOrdonnance (Medicament *MedTab, int n){
	int i,ord,quantite,resultatRecherche,compteur=0;
	int tabNumMedicament[100];
	int tabQuantiteMedicament[100];
	float total;
	int indice;
	
	do{
		printf("\nDonner le(s) numero(s) du medicament a acheter ou -1 pour terminer l ordonnace : ");
		scanf("%d",&ord);
		resultatRecherche = rechercherMedicamentOrd(&*MedTab,n,ord,&indice); /* Appel de la fonction rechercherMedicamentOrd et stockage du variable retourné dans resultatRecherche */
		if(ord != -1){
			if(resultatRecherche != -1){
				if(resultatRecherche == -2){ /* Test si la date du medicament choisit est périmée */ 
					printf("\nImpossible de servir ce medicament : Medicament perimees !");
				}else if(resultatRecherche == 0){
					printf("\nMedicament Hors Stock !");
				}else{
					tabNumMedicament[compteur]=indice; /* Sauvegarde du numero de la case du medicament dans tabNumMedicament  */
					do{
						printf("Donner la quantite du medicament a acheter : ");
						fflush(stdin);
						scanf("%d",&quantite);
						
					}while(quantite > resultatRecherche || quantite <= 0);
					tabQuantiteMedicament[compteur]=quantite; /* Sauvegarde de la quantité du medicament acheter dans tabQuantiteMedicament   */
					compteur++;
				}
				
			
			}else{
				printf("Medicament introuvable ! s il vous plait saisir un numero valide.");
			}
		}
		
	}while(ord != -1);
	printf("\n-------------------Ordonnance-----------------------");
	printf("\nNum\tNom\tQuantite\tPrix Unitaire");
	printf("\n----------------------------------------------------");
	total = 0;
	for(i=0;i<compteur;i++){
		printf("\n%6d\t%s\t%6d\t%.3f",MedTab[tabNumMedicament[i]].num,MedTab[tabNumMedicament[i]].nom,tabQuantiteMedicament[i],MedTab[tabNumMedicament[i]].prix);
		total += MedTab[tabNumMedicament[i]].prix * tabQuantiteMedicament[i]; /* Calcul du Total de l'ordannace */
		MedTab[tabNumMedicament[i]].quantiteStock = MedTab[tabNumMedicament[i]].quantiteStock - tabQuantiteMedicament[i]; /* Soustraction du quantité acheter de la quantité en stock */
	}
	printf("\n\t\t\t---------------------");
	printf("\n\t\tTOTAL : \t %.3f \tTND",total);
	printf("\n\n");
	
	
	FILE *FMed = fopen("FMed.txt","wb");
	if(FMed == NULL){
	printf("\nERREUR: Impossible d ouvrir le fichier.");
	exit(1);}
	
	fwrite (MedTab, sizeof(Medicament),n, FMed );
	fclose(FMed);
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/

