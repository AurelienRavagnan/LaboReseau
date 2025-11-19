#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "LibSerHV.h"
#include "Requete.h"
#include "data.h"
 
#define RCVBUFSIZE 32   /* Size of receive buffer */


void HandleTCPClient(int clntSocket)
{
    int recvMsgSize, rc;                    /* Size of received message */
    struct Requete UneRequete ;
    struct VehiculeHV UnRecord;
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof (struct Requete), 0)) < 0)
        DieWithError("recv() failed"); 
    while(recvMsgSize>0) 
    {   
      printf("Bytes received : %d\n", recvMsgSize);
      AfficheRequete(UneRequete);  

      rc = RechercheHV("VehiculesHV", UneRequete.Reference, &UnRecord);
      if(rc){
        UneRequete.Type = OK;
        UneRequete.Motorisation = UnRecord.Motorisation;
        strcpy(UneRequete.Constructeur, UnRecord.Constructeur);
        strcpy(UneRequete.Modele, UnRecord.Modele);
        UneRequete.Prix = UnRecord.Motorisation;
        printf("res : %d, Vehicule : %s %s\n", rc, UnRecord.Constructeur, UnRecord.Modele);
      }
      else
        UneRequete.Type = Fail;

    /* Echo message back to client */
    if (write(clntSocket, &UneRequete, recvMsgSize) != recvMsgSize)
            DieWithError("send() failed");
    
    printf("Bytes sent : %d\n", sizeof(struct Requete));

    /* See if there is more data to receive */
    if ((recvMsgSize = read(clntSocket, &UneRequete, sizeof (struct Requete))) < 0)
            DieWithError("recv() failed");
    }

    printf("Connexion Closed\n")  ;
    close(clntSocket);    /* Close client socket */
}
