/*
 * serveurTCP-02.c
 *
 * Frédéric LEFEVRE <fred.lefevre@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h> /* exit, atoi */
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h> /* socket, bind, listen, accept, recv */
#include <unistd.h> /* close */
#include <string.h> /* memset */
#include <arpa/inet.h> /* htons, htonl */

#define NB_CLIENT_ATTENTE 3

#define TAILLE_MAX 1024

int main(int argc, char *argv[])
{
    /* Descripteur de la socket d'écoute */
    int socSrv;
    
    /* Descripteur de la socket de communication */
    int socCom;
    
    /* Port du serveur */
    uint16_t srvPort;
    
    /* Point local */
    struct sockaddr_in srvLoc;

    /* Point distant */
    struct sockaddr_in cliDist;
    
    /* Longueur d'une adresse de point */
    socklen_t longueurAddr = sizeof(struct sockaddr_in);

    /* Texte reçu */
    char msg[TAILLE_MAX];
    
    /* Nombre d'octets reçus */
    ssize_t nb_octet;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Récupération des arguments */
    srvPort = atoi(argv[1]);
    
    /* Préparation de l'identification de la socket */
    /* Initialisation */
    memset(&srvLoc, 0, sizeof(srvLoc));
    /* Internet Protocol v4 */
    srvLoc.sin_family = AF_INET;
    /* Toutes les adresses IP sont acceptées */
    srvLoc.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Port du serveur */
    srvLoc.sin_port = htons(srvPort);

    /* Création de la socket */
    socSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socSrv == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    /* Liaison avec le port local */
    if (bind(socSrv,(struct sockaddr *) &srvLoc, sizeof(srvLoc)) == -1)
    {
        perror("bind");
        close(socSrv);
        exit(EXIT_FAILURE);
    }
    
    /* Mise en écoute de la socket */
    if (listen(socSrv, NB_CLIENT_ATTENTE) == -1)
    {
        perror("listen");
        close(socSrv);
        exit(EXIT_FAILURE);
    }
    
    while (1)
    {
        /* Acceptation d'une demande de connexion */
        socCom = accept(socSrv, (struct sockaddr *) &cliDist, &longueurAddr);
        if (socCom == -1)
        {
            perror("accept");
            close(socSrv);
            exit(EXIT_FAILURE);
        }
        
        /* Reception de données */
        nb_octet = recv(socCom, msg, TAILLE_MAX - 1, 0);
        if (nb_octet <= 0) {
            perror("recv");
            close(socCom);
            close(socSrv);
            exit(EXIT_FAILURE);
        }
        
        /* Ajout de la fin de chaîne de caractères */
        msg[nb_octet] = '\0';
        
        /* Affichage des données reçues */
        printf("%ld octets : %s\n", nb_octet, msg);
        
        if (send(socCom, msg, strlen(msg), 0) <= 0)
        {
            perror("send");
            close(socCom);
            close(socSrv);
            exit(EXIT_FAILURE);
        }

        /* Fermeture de la socket de communication */
        if (close(socCom) == -1)
        {
            perror("close socCom");
            exit(EXIT_FAILURE);
        }
    }

    /* Fermeture de la socket d'écoute */
    if (close(socSrv) == -1)
    {
        perror("close socSrv");
        exit(EXIT_FAILURE);
    }
    
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}
