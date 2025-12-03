/******************************************
Herman Vanstapel
2017 Basé sur Fichiers
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "LibSerAR.h"

// include pour les fonctions entrees sortie
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static struct termios old, new;

//clrscr() function definition
// #include <stdlib.h>
void ClrScr(void){
	system("clear");
}


void Gotoxy(int x,int y)    {
	printf("%c[%d;%df",0x1B,y,x);
}


/* Initialize new terminal i/o settings */
// #include <stdio.h>
// #include <stdlib.h>
void initTermios(int echo) {
	tcgetattr(0, &old); //grab old terminal i/o settings
	new = old; //make new settings same as old settings
	new.c_lflag &= ~ICANON; //disable buffered i/o
	new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
	tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}


/* Restore old terminal i/o settings */
void resetTermios(void) {
	tcsetattr(0, TCSANOW, &old);
}


/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}


/* 
Read 1 character without echo 
getch() function definition.
*/
char Getch(void) {
	return getch_(0);
}


/* 
Read 1 character with echo 
getche() function definition.
*/
char GetchE(void) {
	return getch_(1);
}


// permet de supprimer le cr qui placé dans la chaine lors d'un fgets
void DelNewLine(char *Chaine){
	Chaine[strlen(Chaine)-1] = 0;
}


void MonPrintf(char* tempo, int espace,int taille ){
	int Count;
	printf("%s",tempo); 
	Count = espace-taille;
	while ( Count>0 ){
		printf(" ");
		Count--;
	}
}


void AfficheEnteteVehiculeAR (){
	char Tampon[80];
	sprintf(Tampon,"%s","Ref" );MonPrintf(Tampon,4,strlen(Tampon));
	sprintf(Tampon,"%s","Constructeur");    MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%s","Modele");    MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%s","Quantite"); MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%s","Motorisation"); MonPrintf(Tampon,6,strlen(Tampon));
	printf("\n");
}


void AfficheVehiculeAR (struct VehiculeAR    *UnRecord){
	char Tampon[80];

	sprintf(Tampon,"%d",UnRecord->Reference );  MonPrintf(Tampon,4,strlen(Tampon));
	sprintf(Tampon,"%s",UnRecord->Constructeur );    MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%s",UnRecord->Modele );    MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%d",UnRecord->Quantite ); MonPrintf(Tampon,30,strlen(Tampon));
	sprintf(Tampon,"%d",UnRecord->Motorisation ); MonPrintf(Tampon,6,strlen(Tampon));
	printf("\n");
}


void SaiSieVehiculeAR (int Reference, struct VehiculeAR  *UnRecord ){
	char Tampon[80];

	printf("Reference :%d \n",Reference);
	UnRecord->Reference = Reference; 
	printf("Saisie Constructeur :");
	fgets(UnRecord->Constructeur ,sizeof UnRecord->Constructeur ,stdin );
	printf("Saisie Modele :");
	fgets(UnRecord->Modele ,sizeof UnRecord->Modele ,stdin );
	printf("Saisie Quantite :");
	fgets(Tampon,sizeof Tampon,stdin );
	UnRecord -> Quantite = atoi(Tampon);
	printf("Saisie Motorisation :");
	fgets(Tampon,sizeof Tampon,stdin );
	UnRecord -> Motorisation = atoi(Tampon);

	DelNewLine(UnRecord->Constructeur);
	DelNewLine(UnRecord->Modele);
	AfficheEnteteVehiculeAR ();
	AfficheVehiculeAR (UnRecord);
	printf("-----------------------\n");
	return;
}


int NombreVehiculesAR (char *NomFichier){
	int fd;
	int taille;
	fd = open(NomFichier, O_RDONLY); /* On ouvre le fichier en Lecture */
	if ( fd == -1 ){
		fprintf(stderr,"Pas de fichier\n");
		return 0;
	}
	else
		fprintf(stderr,"Ouverture reussie \n");
	taille = lseek(fd, 0, SEEK_END );
	close(fd);
	return ( taille / sizeof(struct VehiculeAR  ));
}


void CreationAjoutVehiculeAR (char *NomFichier,struct VehiculeAR  *UnRecord ){
	char Redo;
	int nbr;
	int fd;
	int taille;

	fd =open(NomFichier, O_WRONLY | O_APPEND | O_CREAT, 0666 );
	if ( fd == -1 ){
		fprintf(stderr,"Echec Ouverture\n");
		exit(0);
	}
	else
		fprintf(stderr,"Ouverture reussie \n");

	taille = lseek(fd, 0, SEEK_END );
	printf("Position actuelle dans le fichier %ld\n",taille );
	UnRecord-> Supprime = 0;

	nbr = write (fd, UnRecord,sizeof(struct VehiculeAR ) );;

	close(fd);
}


void AfficheFacture(struct FactureAR *UneFacture){
	char Tampon[80];
	sprintf(Tampon,"%d",UneFacture->NumeroFacturation ); MonPrintf(Tampon,4,strlen(Tampon));
	sprintf(Tampon,"%s",UneFacture->Acheteur ); MonPrintf(Tampon,60,strlen(Tampon));
	sprintf(Tampon,"%d",UneFacture->Quantite  ); MonPrintf(Tampon,4,strlen(Tampon));
	sprintf(Tampon,"%d",UneFacture->Reference); MonPrintf(Tampon,4,strlen(Tampon));

	printf("\n");
}


void ListingVehiculesAR (char *NomFichier){
	struct VehiculeAR   UnRecord;
	char Tampon[80];
	int bytesRead;
	int fd;

	fd = open(NomFichier, O_RDONLY );
	if ( fd == -1 ){
		fprintf(stderr,"Echec Ouverture\n");
		exit(0);
	}
	else
		fprintf(stderr,"Ouverture reussie \n");

	AfficheEnteteVehiculeAR ();
	bytesRead= read (fd, &UnRecord,sizeof(UnRecord));

	while ( bytesRead ){
		fprintf(stderr,"Record lu %d Bytes \n",bytesRead);
		AfficheVehiculeAR ( &UnRecord);
		bytesRead =read (fd, &UnRecord,sizeof(UnRecord));
	}
	close(fd);
}


void ListingFacturesAR(char *NomFichier){
	struct FactureAR UneFacture;
	char Tampon[80];
	int  fd;
	int bytesRead;
	long pos;
			fprintf(stderr,"Echec Ouverture\n");
			exit(0);
	fd = open(NomFichier, O_RDONLY );
	if ( fd == -1 ){
		fprintf(stderr,"Echec Ouverture\n");
		exit(0);
	}
	else{		
		fprintf(stderr,"Echec Ouverture\n");
		exit(0);
	}
	// sizeof(struct FactureLM)

	bytesRead= read (fd, &UneFacture,sizeof(struct FactureAR));
	while ( bytesRead ){
			pos = lseek(fd, 0, SEEK_CUR ); 
			fprintf(stderr,"Record lu %d bytes et Position actuelle dans le fichier %ld\n", bytesRead ,pos );
			AfficheFacture( &UneFacture);
			bytesRead= read (fd, &UneFacture,sizeof(struct FactureAR));
	}
	close(fd);
}


int main(){
	char Choix;
	char Tampon[80];
	int res;
	struct VehiculeAR  UnRecord;
	int Numero;
	while(1){
		printf("-------2022-----------\n");
		printf("1) Ajout              \n");
		printf("2) Vehicule           \n"); 
		printf("4) Recherche          \n");   
		printf("5) Achat              \n");  
		printf("6) Factures           \n");
		printf("7) A propos           \n");
		printf("8) exit               \n"); 
		printf("----------------------\n"); 
		printf(">>"); Choix=GetchE(); printf("\n");
		switch(Choix){
			case '1': {
				struct VehiculeAR   UnRecord;
				FILE *sortie;
				char Redo;
				Redo='y';
				while ( Redo=='Y' || Redo=='y'){ 
					int Nombre;
					Nombre= NombreVehiculesAR ("VehiculesAR");
					SaiSieVehiculeAR (Nombre+1, &UnRecord );
					CreationAjoutVehiculeAR ("VehiculesAR",&UnRecord); 
					printf("Encoder un autre (Y/N) ?)");
					printf(">>"); Redo=GetchE(); printf("\n");
				}
				break;	
			}
			case '2': 
				ListingVehiculesAR ("VehiculesAR");
				break;
			case '4': { 
				struct VehiculeAR UnRecord;
				int reference, res;
				printf("Reference :");
				fgets(Tampon,sizeof Tampon,stdin);
				reference = atoi(Tampon);
				res = RechercheAR("VehiculesAR",reference,&UnRecord);
				if(res){
					AfficheEnteteVehiculeAR();
					AfficheVehiculeAR(&UnRecord);
				}
				else	
					printf("Reference %d non trouvée\n", reference);
				break;
			}
			case '6': 
				ListingFacturesAR("FactureAR");
				break;
			case '7': 
				AProposServeurAR("V 1.0","Aurelien","Ravagnan");
				break;
			case '8': 
				exit(0); 
			default: 
				printf("Choix invalide\n");
		}
	}
}
