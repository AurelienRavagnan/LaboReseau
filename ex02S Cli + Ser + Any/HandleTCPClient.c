#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "LibSer.h"
#include "Requete.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */


void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
    struct Requete UneRequete;
    int totalBytesRead = 0;             /* Total bytes read */
    int totalBytesWritten = 0;          /* Total bytes written */

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof(struct Requete), 0)) < 0)
        DieWithError("recv() failed");

    while (recvMsgSize > 0)
    {
        totalBytesRead += recvMsgSize;
        printf("#%s\n", UneRequete.Chaine);
        printf("Bytes read this iteration: %d, Total bytes read: %d\n", recvMsgSize, totalBytesRead);

        /* Echo message back to client */
        int bytesWritten = write(clntSocket, &UneRequete, recvMsgSize);
        if (bytesWritten != recvMsgSize)
            DieWithError("send() failed");

        totalBytesWritten += bytesWritten;
        printf("Bytes written this iteration: %d, Total bytes written: %d\n", bytesWritten, totalBytesWritten);

        /* See if there is more data to receive */
        if ((recvMsgSize = read(clntSocket, &UneRequete, sizeof(struct Requete))) < 0)
            DieWithError("recv() failed");
    }

    printf("Connexion Closed\n");
    close(clntSocket);    /* Close client socket */
}
