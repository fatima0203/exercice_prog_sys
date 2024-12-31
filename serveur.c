#include "common.h"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Usage: %s <IP_ADDRESS> <PORT>\n", argv[0]);
        return 0;
    }

    int server_fd, new_socket;
    struct sockaddr_in address;
    int taille_adrr = sizeof(address);
    Message mess= {0};


    const char* adresse_ip = argv[1];
    int port = atoi(argv[2]);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Echec de creation du Socket");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);


    if (inet_pton(AF_INET, adresse_ip, &address.sin_addr) <= 0) {
        perror("Adresse IP invalide");
        return 0;
    }

    if (bind(server_fd, (struct sockaddr*)&address, taille_adrr) < 0) {
        perror("Echec de lancement de Bind");
        return 0;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Erreur d'ecoute");
        return 0;
    }

    printf("Serveur en attente de connexion sur %s:%d\n", adresse_ip, port);

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&taille_adrr)) < 0) {
        perror("Erreur d'acceptation");
        return 0;
    }

    while (1) {
        send(new_socket, &mess, sizeof(mess), 0);
        printf("Envoyé au client: %d\n", mess.compteur);

        read(new_socket, &mess, sizeof(mess));
        printf("Reçu du client: %d\n", mess.compteur);

        mess.compteur++;
        sleep(1);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
