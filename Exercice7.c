#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEBUT_PORT 0
#define FIN_PORT 9000

int main(int argc , char* argv[])
{
    if(argc != 2)
    {
         printf("Usage: %s <ADRESSE IP>\n", argv[0]);
        return 0;
    }

    char* adresse_ip = argv[1];
    int sock;
    struct sockaddr_in target;

      printf("Scanner les ports  de %d a %d de  %s...\n", DEBUT_PORT, FIN_PORT,  adresse_ip);

      for(int port= DEBUT_PORT ;port <=FIN_PORT ;port++)
      {

          sock = socket(AF_INET ,SOCK_STREAM ,0);

          if (sock ==  -1)
         {
            perror(" Echec de creation de Socket\n ");
            return -1;
          }

        target.sin_family = AF_INET;
        target.sin_port = htons(port);

          if(inet_pton(AF_INET ,adresse_ip, &target.sin_addr) == -1)
          {
            perror("Erreur par rapport a la  configuration de l'adresse ip\n");
            close(sock);
            return -1;
          }

        if( connect(sock ,(struct sockaddr*)&target , sizeof(target)) == 0)

            printf("Port %d est ouvert !\n", port);


          close(sock);

      }

         printf(" Le scan est complet!\n");


    return 0;
}
