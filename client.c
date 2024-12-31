#include "common.h"
int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Usage: %s <IP_ADDRESS> <PORT>\n", argv[0]);
        return -1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    Message mess;

    // Récupérer l'adresse IP et le port depuis la ligne de commande
    const char* adresse_ip= argv[1];
    int port = atoi(argv[2]);

    // Créer le socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erreur de création du socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convertir l'adresse IP en format binaire
    if (inet_pton(AF_INET, adresse_ip, &serv_addr.sin_addr) <= 0) {
        printf("Adresse IP invalide\n");
        return -1;
    }

    // Connecter au serveur
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Échec de connexion\n");
        return -1;
    }

    while (1) {
        // Recevoir le compteur du serveur
        read(sock, &mess, sizeof(mess));
        printf("Reçu du serveur: %d\n", mess.compteur);

        // Incrémenter le compteur et attendre une seconde
        mess.compteur++;
        sleep(1);

        // Envoyer le compteur incrémenté au serveur
        send(sock, &mess, sizeof(mess), 0);
        printf("Envoyé au serveur: %d\n", mess.compteur);
    }

    close(sock);
    return 0;
}
