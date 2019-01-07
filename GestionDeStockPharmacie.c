/***************************************************************************************
* Projet:  MINI-PROJET – GESTION DE STOCK D’UNE PHARMACIE
* Fonction: Application qui permet au pharmacien d'ajouter supprimer rechercher
*			et afficher tout les informations concernant ces médicaments
* Objet :  
****************************************************************************************
* Auteur:   Mahfoudh Houssem & Cherif Malek
* Niveau:   CYCLE INGENIEUR
****************************************************************************************
* Copyright 2018 by Houssem & Malek
* **************************************************************************************/

#include "gestionPharmacie.h"
#include "ajouterMedicament.c"
#include "servirOrdonnance.c"
#include "afficherMedRechercher.c"
#include "afficheMedPerim.c"





void ajouterNouveauMedicament();
void afficherMedicamentQuiCommence();
void afficheMedPerim();
void ajouterFournisseur();
void ajouterLot();
void ajouterNouveauMedicament();
void dateControle();
void medicamentRupture();
int medicPerimeControl();
void numMedCorresp();
void QauntiteMedic();
int rechercheReference();
int rechercherMedicamentOrd();
void servirOrdonnance();
int string_compare();
void suppMedic();

/********************* Définitions des fonctions : *********************/

//--------------------- Programme Principal ---------------------------
int main(){
	int numElements,n,i=0; /* variables locales de main */
	Medicament tabMedicament[taille];
	
	/* Ouverture du fichier FMed.txt qui contient les informations des médicament */
	FILE *FMed = fopen("FMed.txt","rb");
	if(FMed == NULL){
		printf("\nERREUR: Impossible d ouvrir le fichier.");
		exit(1);
	}
	
	/* Chargement des informations dans un tableau tabMedicament */
	fread(&tabMedicament,sizeof(tabMedicament) , 1 , FMed);
	fclose(FMed);
	
	/* Boucle qui permet de calculer le nombre des medicament enregistré */
	while(strcmp(tabMedicament[i].nom,"")){
		i++;
	}
	
	numElements = i;
	
	while(1){
		int choix;
		printf("\t\t\t\t _______________________________________________\n");
		printf("\t\t\t\t| -------- Base de donnees de pharmacie --------| \n");
		printf("\t\t\t\t| 1  : Afficher la liste des medicaments        | \n");
		printf("\t\t\t\t| 2  : Ajouter medicament                       | \n");
		printf("\t\t\t\t| 3  : Consulter la quantite d'un medicament    | \n");
		printf("\t\t\t\t| 4  : Consulter les fournisseur d'un medicament| \n");
		printf("\t\t\t\t| 5  : Consulter les medicaments perimes        | \n");
		printf("\t\t\t\t| 6  : Servir une ordonnace                     | \n");
		printf("\t\t\t\t| 7  : Supprimer un medicament du stock         | \n");
		printf("\t\t\t\t| 8  : Consulter les Medicaments en rupture     | \n");
		printf("\t\t\t\t| 9  : Chercher un medicament                   | \n");
		printf("\t\t\t\t| 10 : Chercher le numero du medicament         | \n");
		printf("\t\t\t\t| 0  : Quitter la base de donnes                | \n");
		printf("\t\t\t\t|_______________________________________________| \n");
		printf("\n");
	do{
		printf("Donner votre choix : ");
		scanf("%d",&choix);
		printf("\n");
	}while(choix<0 || choix >10);	
	
	switch(choix){
			case 1: 
				affichMedicament(tabMedicament,numElements);
				break;
			case 2: 
				ajouterNouveauMedicament(tabMedicament, &numElements);
				break;
			case 3:
				QauntiteMedic(tabMedicament,numElements);
				break; 
			case 4:
				affichFournisseurMedic(tabMedicament,numElements);
				break;
			case 5:
				afficheMedPerim(tabMedicament,numElements);
				break;
			case 6:
				servirOrdonnance(tabMedicament,numElements);
				break;
			case 7:
				suppMedic(tabMedicament,&numElements);
				break;
			case 8:
				medicamentRupture(tabMedicament,numElements);
				break;
			case 9:
				afficherMedicamentQuiCommence(tabMedicament, numElements);
				break;
			case 10:
				numMedCorresp(tabMedicament, numElements);
				break;
			case 0: 
				exit(0);
		}
	}

	system("pause");
	return 0;

}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/









/* Fonction qui permet d'afficher tout les informations du médicament en stock (quantite > 0) */
void affichMedicament(Medicament *Medtab, int n)
{ 
	int i,j;  

	printf ("---------------------------------------------------------------------------------------------------------------\n");
	printf("  Num\t\tNom\t\tLab\t\tRefLot\t\tDatePreemption\t\tPrix\t\tQuantite\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{
			if(Medtab[i].quantiteStock != 0){
				printf ("%3d\t\t%s\t\t%s\t\t%s\t\t%d/%d/%d\t\t%-5.3f\t\t%d\n",Medtab[i].num,Medtab[i].nom,Medtab[i].laboratoire,Medtab[i].lot.reference,Medtab[i].lot.datePreemption.jour,Medtab[i].lot.datePreemption.mois,Medtab[i].lot.datePreemption.annee,Medtab[i].prix,Medtab[i].quantiteStock);	
			}
		}
		
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/



// cette fonction cherche dans le tableau des medicaments les quantités null pour afficher les medicaments en rupture
void medicamentRupture(Medicament *MedTab,int n){
	int i;
	int trouve=0;
	printf ("----------------------------------------------------------------------------------------\n");
	printf("Num\tNom\tLab\tRefLot\tDatePréemption\tPrix\tQuantite\n");
	printf("-----------------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{	if(MedTab[i].quantiteStock==0){
			printf ("%d\t%s\t%s\t%s\t%d/%d/%d\t%.3f\t%d\n",MedTab[i].num,MedTab[i].nom,MedTab[i].laboratoire,MedTab[i].lot.reference,MedTab[i].lot.datePreemption.jour,MedTab[i].lot.datePreemption.mois,MedTab[i].lot.datePreemption.annee,MedTab[i].prix,MedTab[i].quantiteStock);
			trouve=1;
		}	
		}
	if (trouve==0){
		printf("\nAucun medicament en rupture.\n");
	}
}


/* --------------------------------------------------------------------------------------------------------------------------------------------*/




// cette fonction affiche le /les fournisseur/s d'un medicament donné par son nom
void affichFournisseurMedic(Medicament *MedTab,int n){
	int num;
	do{
		printf("Donner le numero du medicament : ");
		scanf("%d",&num);
	}while(num<=0);
	int i;
	int j;
	int trouve=0;
	printf ("------------------------------------------------------------------------\n");
	printf("  Num_Medicament\tNom\t\tAdresse\t\tTelephone\n");
	printf("-------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{	
			if(MedTab[i].num==num){
				for(j=0;j<MedTab[i].nombreFournisseur;j++){
					printf("\t%d \t\t%s \t\t%s \t%d\n",MedTab[i].num,MedTab[i].listeFournisseur[j].nom,MedTab[i].listeFournisseur[j].adresse,MedTab[i].listeFournisseur[j].telephone);
					trouve=1;
				}	
			}	
		}
		printf("\n\n");	
		
	if (trouve==0){
		printf("\nMedicament inconnu!\n");
	}
}

/* --------------------------------------------------------------------------------------------------------------------------------------------*/


