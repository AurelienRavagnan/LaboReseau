#ifndef DATAH
#define DATAH
#include <time.h>
// 2024 , interdit de modifier les champs existants

struct VehiculeAR { 
	int  Supprime;
	int  Reference;
	char Constructeur[30];
	char Modele[30];
	int  Quantite;
	int  Motorisation;
};

struct FactureAR{
	int NumeroFacturation;
	char Acheteur[40];
	time_t DateFacturation;
	int Quantite;
	int Reference;
};  	

#endif
