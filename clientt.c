/*
 * clientTCP-02.c
 *
 * Frédéric LEFEVRE <fred.lefevre@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h> /* exit, atoi */
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h> /* socket */
#include <unistd.h> /* close */
#include <string.h> /* strncpy, memset, strlen */
#include <arpa/inet.h> /* inet_pton, htons */

#define TAILLE_MAX 1024

int main(int argc, char *argv[])
{
    /* Descripteur de la socket */
    int sd;

    /* Adresse IP du serveur */
    char srvIp[16];

    /* Port du serveur */
    uint16_t srvPort;

    /* Point distant */
    struct sockaddr_in srvDist;

    /* Texte à envoyer */
    char *txt;

    char msg[TAILLE_MAX];
    
    
    ssize_t nb_octet;
    /* Nombre de fois où le texte doit être envoyé */
    int nb_envoi;

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s ip_serveur port_serveur texte nb_envoi\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Récupération des arguments */
    strncpy(srvIp, argv[1], 15);
    srvPort = atoi(argv[2]);
    txt = argv[3];
    nb_envoi = atoi(argv[4]);

    /* Préparation de l'identification de la socket */
    /* Initialisation */
    memset(&srvDist, 0, sizeof(srvDist));
    /* Internet Protocol v4 */
    srvDist.sin_family = AF_INET;
    /* Convertion en network byte order */
    if (inet_pton(AF_INET, srvIp, &srvDist.sin_addr.s_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    /* Port du serveur */
    srvDist.sin_port = htons(srvPort);

    /* Création de la socket */
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Connexion à la socket distante */
    if (connect(sd, (struct sockaddr *) &srvDist, sizeof(srvDist)) == -1)
    {
        perror("connect");
        close(sd);
        exit(EXIT_FAILURE);
    }

    /* Emission des données */
    while (nb_envoi--) {
        if (send(sd, txt, strlen(txt), 0) <= 0)
        {
            perror("send");
            close(sd);
            exit(EXIT_FAILURE);
        }

    
    
    nb_octet = recv(sd, msg, TAILLE_MAX - 1, 0);

    
    msg[nb_octet] = '\0';
    printf("%ld octets : %s\n", nb_octet, msg);

	}
    /* Fermeture de la socket */
    if (close(sd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    printf("Bye\n");
    exit(EXIT_SUCCESS);
}
