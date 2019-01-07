/***************************************************************************************************
****** Fichier qui contient les fonctions qui permettent a supprimer ou afficher les information ******
******  	concernant les medicaments rechercher soit a partir un nom ou a partir du nom 		******
**********************************************************************************************/

/* Fonction qui compare deux chaines de caractères passé en paramètre :
	- Retourne 0 si'il sont identique a 100% ou au moins l'une des deux chaine est terminé et tout les caractères de cette chaine sont égaux
	- Retourne -1 cas contraire */
	
#define Color_Red "\33[0:31m\\]"
#define Color_end "\33[0m\\]"	
	
	
	
int string_compare(char str1[], char str2[])
{
    int ctr=0;

    while(toupper(str1[ctr])==toupper(str2[ctr]))
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' || str2[ctr]=='\0')
        return 0;
    else
        return -1;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


/* Fonction qui permet a l'utilisateur de chercher un médicament a partir d'une sous-chaine a condition que ce medicament commence par cette sous-chaine */
void afficherMedicamentQuiCommence (Medicament *MedTab, int n){
	char recherche[100];
	int i=0;
	printf("Donner le/les medicament(s) rechercher : ");
	fflush(stdin);
	gets(recherche);
	
	printf ("\n----------------------------------------------------------------------------------------\n");
	printf("Num\tNom\tLab\tRefLot\tDatePréemption\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{
			if(string_compare(MedTab[i].nom,recherche) == 0){
				printf ("%d\t%s\t%s\t%s\t%d/%d/%d\t%.3f\t%d\n",MedTab[i].num,MedTab[i].nom,MedTab[i].laboratoire,MedTab[i].lot.reference,MedTab[i].lot.datePreemption.jour,MedTab[i].lot.datePreemption.mois,MedTab[i].lot.datePreemption.annee,MedTab[i].prix,MedTab[i].quantiteStock);
			}	
		}
		printf("\n\n");
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


//fonction qui permet à l'utilisateur de retournée le numero et tout les informatios du medicament en tapant son nom
void numMedCorresp(Medicament *MedTab,int n)
{
	char medicamentRecherche[100];
	int i=0;
	
	printf("Donner le nom du medicament : ");
	fflush(stdin);
	gets(medicamentRecherche);
	
	printf ("\n----------------------------------------------------------------------------------------\n");
	printf("Num\tNom\tLab\tRefLot\tDatePréemption\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++){
		if(strcmp(MedTab[i].nom,medicamentRecherche)==0)
		{
			printf ("%d\t%s\t%s\t%s\t%d/%d/%d\t%.3f\t%d\n",MedTab[i].num,MedTab[i].nom,MedTab[i].laboratoire,MedTab[i].lot.reference,MedTab[i].lot.datePreemption.jour,MedTab[i].lot.datePreemption.mois,MedTab[i].lot.datePreemption.annee,MedTab[i].prix,MedTab[i].quantiteStock);
		}
	}
}



/* --------------------------------------------------------------------------------------------------------------------------------------------*/



// cette fonction cherche la quantité d'un medicament à partir de son nom
void QauntiteMedic(Medicament *MedTab,int n){
	char medicamentRecherche[100];
	fflush(stdin);
	printf("Donner le nom du medicament : ");
	gets(medicamentRecherche);
	int i;
	int trouve=0;
	printf ("----------------------------------------------------------------------------------------\n");
	printf(" Num\tNom\tLab\tRefLot\tDatePréemption\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{	if(string_compare(MedTab[i].nom,medicamentRecherche)==0){
			
			printf ("%d\t%s\t%s\t%s\t%d/%d/%d\t%.3f\t%d\n",MedTab[i].num,MedTab[i].nom,MedTab[i].laboratoire,MedTab[i].lot.reference,MedTab[i].lot.datePreemption.jour,MedTab[i].lot.datePreemption.mois,MedTab[i].lot.datePreemption.annee,MedTab[i].prix,MedTab[i].quantiteStock);
			trouve=1;
			}	
		}
	if (trouve==0){
		printf("\nMedicament inconnu!\n");
	}

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/



//fonction qui efface un medicament si il est périmé ou a une quantité null
void suppMedic(Medicament *MedTab , int *n)
{
	char reference[100];
	fflush(stdin);
	printf("\nDonner une reference : ");
	gets(reference);
	int i;
	int j;
	int trouve = 0;
	
	for(i=0;i<*n;i++)
	{
		
		if(strcmp(MedTab[i].lot.reference,reference)==0){
			
			if((MedTab[i].quantiteStock==0)||(medicPerimeControl(&MedTab[i].lot)==1))
			{
				for(j=i;j<*n;j++)
				{
					MedTab[j]=MedTab[j+1];
				}
				*n=*n-1;
				printf("\nSuppression effectuer ! \n");
			}
			else{
				printf("Impossible de supprimer le medicament %s de reference %s \n",MedTab[i].nom,MedTab[i].lot.reference);
				printf("Quantite restante est : %d \n",MedTab[i].quantiteStock);
			}
			trouve = 1;
		}	
	}
	if (trouve == 0){
		printf("\nReference introuvable!\n");
	}
		
	FILE *FMed = fopen("FMed.txt","wb");
	if(FMed == NULL){
	printf("\nERREUR: Impossible d ouvrir le fichier.");
	exit(1);}
	
	fwrite (MedTab, sizeof(Medicament),*n, FMed );
	fclose(FMed);
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/
