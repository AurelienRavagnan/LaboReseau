#include "LibSerHV.h"

void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;
}


int RechercheHV(char* NomFichier, int Reference, struct VehiculeHV *UnRecord){
    FILE* fd;
    int bytesRead;
    int trouve;

    printf("RechercheHV<\n");

    fd = fopen(NomFichier, "rb");
    if ( fd == NULL ){
        printf("Ouverture reussie VehiculesHV\n");
        exit(-1);
    }
    else
        printf("Ouverture reussie VehiculesHV\n");
        trouve = 0 ;

    while ((bytesRead = fread(UnRecord, sizeof(struct VehiculeHV), 1, fd)) == 1){
        if ( UnRecord->Reference == Reference ){
            trouve = 1;
            break;
        }
        printf("Reference lue %d et position  actuelle dans le fichier %d\n", UnRecord->Reference, ftell(fd));
    }
    fclose(fd);
    printf("RechercheHV>\n");
    return trouve;
}