/* */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define taille 100
#define listeF 3


typedef struct Date{
	int jour;
	int mois;
	int annee;
}Date;

typedef struct Lot{
	char reference[taille];
	struct Date dateFabrication;
	struct Date datePreemption;
}Lot;

typedef struct Fournisseur{
	char nom[taille];
	char adresse[taille];
	int telephone;
}Fournisseur;

typedef struct Medicament{
	int num;
	char nom[taille];
	char laboratoire[taille];
	Lot lot;
	float prix;
	int quantiteStock;
	Fournisseur listeFournisseur[listeF];
	int nombreFournisseur;
	int secteurStockage;
}Medicament;
