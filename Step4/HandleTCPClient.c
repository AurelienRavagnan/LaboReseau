#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "LibSerAR.h"
#include "Requete.h"
#include "data.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */


void HandleTCPClient(int clntSocket){
	int recvMsgSize, received = 1; /* Size of received message */
	struct Requete UneRequete ;
	struct VehiculeAR UnRecord;
	/* Receive message from client */
	if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof (struct Requete), 0)) < 0)
		DieWithError("recv() failed"); 

	printf("Bytes received : %d\n", recvMsgSize);
	AfficheRequete(stdout, UneRequete);  

	while(received != 0){
		switch(UneRequete.Type){
			case Question:
				received = RechercheAR("VehiculesAR", UneRequete.Reference, &UnRecord);
				fprintf(stderr, "res : %d Reference : %s %s\n", received, UnRecord.Constructeur, UnRecord.Modele);
				memset(&UneRequete, 0, sizeof(struct Requete));
				if(received == 1){
					UneRequete.Type = OK;
					UneRequete.Reference = UnRecord.Reference;
					UneRequete.Motorisation = UnRecord.Motorisation;
					strcpy(UneRequete.Constructeur, UnRecord.Constructeur);
					strcpy(UneRequete.Modele, UnRecord.Modele);
					AfficheRequete(stdout, UneRequete);
				}
				else
					UneRequete.Type = Fail;
				received = send(clntSocket, &UneRequete, sizeof(struct Requete), 0);
				if(received == -1)
					perror("send() failed");
				else
					printf("Bytes sent : %d\n", sizeof(struct Requete));
				break;
			default:
				fprintf(stderr, "Type de requete inconnu\n");
		}

		if((received = recv(clntSocket, &UneRequete, sizeof(struct Requete), 0)) < 0){
			DieWithError("recv() failed");
		}
		else if (received != 0){
			printf("Bytes received : %d\n", received);
		}	
		else
			printf("Fermeture de la connexion\n");
	}

	printf("Connexion Closed\n");
	close(clntSocket);    /* Close client socket */
}
