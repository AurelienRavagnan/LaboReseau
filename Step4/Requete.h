enum TypeRequete { 
   Question = 1, 
   Achat  = 2, 
   Livraison= 3, 
   OK  = 4, 
   Fail = 5  
}; 

struct Requete {
   enum TypeRequete Type; 
   int NumeroFacture; 
   int Reference; // la référence du film 
   int Quantite; 
   int Motorisation;
   int Prix; 
   char Constructeur[30]; 
   char Modele[30]; 
   char NomClient[80];  

};  

#include <stdio.h>  

void AfficheRequete(FILE *fp, struct Requete R ) { 
   fprintf(fp,">TypeRequete %d \n", R.Type ); 
   fprintf(fp,">NumeroFacture %d \n", R.NumeroFacture ); 
   fprintf(fp,">Reference %d \n", R.Reference ); 
   fprintf(fp,">Quantite %d \n", R.Quantite ); 
   fprintf(fp,">Motorisation %d \n", R.Motorisation );
   fprintf(fp,">Prix %d \n", R.Prix ); 
   fprintf(fp,">Constructeur %s \n", R.Constructeur ); 
   fprintf(fp,">Modele %s \n", R.Modele );  
   fprintf(fp,">Client %s \n\n", R.NomClient ); 
   return; 
} 