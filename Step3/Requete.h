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

void AfficheRequete(struct Requete R ) { 
   fprintf(stderr,">TypeRequete %d \n", R.Type ); 
   fprintf(stderr,">NumeroFacture %d \n", R.NumeroFacture ); 
   fprintf(stderr,">Reference %d \n", R.Reference ); 
   fprintf(stderr,">Quantite %d \n", R.Quantite ); 
   fprintf(stderr,">Motorisation %d \n", R.Motorisation );
   fprintf(stderr,">Prix %d \n", R.Prix ); 
   fprintf(stderr,">Constructeur %s \n", R.Constructeur ); 
   fprintf(stderr,">Modele %s \n", R.Modele );  
   fprintf(stderr,">Client %s \n\n", R.NomClient ); 
   return; 
} 