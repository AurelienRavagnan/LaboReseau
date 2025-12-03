#include "LibSerAR.h"

void AProposServeurAR(char *Version,char *Nom1,char* Nom2){
    printf("Version : %s \n",Version );
    printf("Nom1 : %s \n",Nom1 );
    printf("Nom2 : %s \n",Nom2 );
}


int RechercheAR(char* NomFichier, int Reference, struct VehiculeAR *UnRecord){
    FILE* fd;
    int bytesRead;
    int trouve; 

    printf("RechercheAR<\n");

    fd = fopen(NomFichier, "rb");
    if ( fd == NULL ){
        printf("Ouverture reussie VehiculesAR\n");
        exit(-1);
    }
    else
        printf("Ouverture reussie VehiculesAR\n");
        trouve = 0 ;

    while ((bytesRead = fread(UnRecord, sizeof(struct VehiculeAR), 1, fd)) == 1){
        if ( UnRecord->Reference == Reference ){
            trouve = 1;
            break;
        }
        printf("Reference lue %d et position  actuelle dans le fichier %d\n", UnRecord->Reference, ftell(fd));
    }
    fclose(fd);
    printf("RechercheAR>\n");
    return trouve;
}