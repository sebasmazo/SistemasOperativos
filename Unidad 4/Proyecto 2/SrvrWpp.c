#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6666
#define BUF_SIZE 128
struct client_t
{
    int socket;
    int rxState;
    char Nombre[20];
    int contadoraux;
};
int cupos[10];
int cont=0;
pthread_t *rxThreadId;
struct client_t *clientaux;
void *readThread(void *arg)
{
    struct client_t *client = ((struct client_t *)arg); //Cliente actual
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    char Nombre[20];
    int status;
    int idName = 0;

    while (1)
    {
        numOfBytes = read(client->socket, buf, BUF_SIZE);
        if (0 == numOfBytes)
        {
            printf("client closed the socket end\n");
            break;
        }
        else if (-1 == numOfBytes)
        {
            perror("ReadThread read() fails: ");
            break;
        }
        else if(cupos[client->contadoraux-1]==1)
        {
            //printf("from client: %s\n", buf);
            if(idName==0){
                idName=1;
                strcpy(Nombre,buf);
                strcpy(client->Nombre,Nombre);
                strcat(buf,", Bienvenido al chat!\n");
            }
            for (int i = 1; i <= 10; i++)
            {
                if (client->contadoraux != clientaux[i - 1].contadoraux && cupos[i - 1] != 0)
                {
                    // printf("%d\n", client->num);
                    status = write(clientaux[i - 1].socket, buf, strlen(buf) + 1);
                    if (-1 == status)
                    {
                        perror("Server write to client fails: ");
                        break;
                    }
                }
            }
        }
    }
    strcpy(buf, Nombre);
    strcat(buf, " se desconecto\n");
    printf("%s ", buf);
    for (int i = 1; i <= 10; i++)
    {
        if (client->contadoraux != clientaux[i - 1].contadoraux && cupos[i - 1] != 0)
        {
            // printf("%d\n", client->num);
            status = write(clientaux[i - 1].socket, buf, strlen(buf) + 1);
            if (-1 == status)
            {
                perror("Server write to client fails: ");
                break;
            }
        }
    }
    idName = 0;
    client->rxState = 0;
    cupos[client->contadoraux - 1] = 0;
    close(client->socket);
    cont--;
    return NULL;
}
void *Comandos(){
    
    char comand[20];
    
    printf("Comandos: Show (Muestra los clientes conectados), rmv (Desconectar usuarios), msg mandar un mensaje a todos\n");
    while(1){
        scanf("%s", comand);
        if(strcmp(comand,"Show") == 0){
            printf("\n");
            for (int i = 0; i < 10; i++)
            {
                if(cupos[i] == 1){
                    printf("Username: %s \n",clientaux[i].Nombre);
                }
            }
        }
        else if(strcmp(comand,"msg") == 0){
            char buf[BUF_SIZE];
            char texto[100];
            int status;
            printf("Ingrese el mensaje a continuación: \n");
            scanf("%s", texto);
            strcpy(buf,texto);
            for (int i = 0; i < 10; i++)
            {
                status = write(clientaux[i].socket, buf, strlen(buf) + 1);
                if (-1 == status)
                {
                    perror("Server write to client fails: ");
                    break;
                }
            }
            
        }
        else if (strcmp(comand, "rmv") == 0)
        {
            char buf[BUF_SIZE];
            char texto[100];
            printf("Ingrese el usuario a continuación: \n");
            scanf("%s", texto);
            strcpy(buf, texto);
            for (int i = 0; i < 10; i++){
                    if (strcmp(buf, clientaux[i].Nombre) == 0)
                    {
                        int status;
                        strcpy(buf, "Desconectado del servidor\n");
                        status = write(clientaux[i].socket, buf, strlen(buf) + 1);
                        if (-1 == status)
                        {
                            perror("Server write to client fails: ");
                            break;
                        }
                        clientaux[i].rxState = 0;
                        cupos[i] = 0;
                        close(clientaux[i].socket);
                        printf("Desconectado\n");
                        cont--;
                        break;
                    }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    int status;
    int enable = 1;
    int server_sd;
    int client_sd;
    rxThreadId = malloc(sizeof(pthread_t) * 10);
    pthread_t *comandThreadId;
    clientaux = malloc(sizeof(struct client_t) * 10);
    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1)
    {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, (int *)&enable, sizeof(enable));
    if (-1 == status)
    {
        perror("setsockopt error: ");
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    status = bind(server_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == status)
    {
        perror("Bind fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    status = listen(server_sd, 1);

    if (-1 == status)
    {
        perror("Listen fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Server encendido\n");
    status = pthread_create(&comandThreadId, NULL, &Comandos, NULL);
    if (-1 == status)
    {
        perror("Pthread read fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        int cupo = 0;
        client_sd = accept(server_sd,NULL,NULL);
        if(cont < 10){
            cont++;
            printf("Cliente #%d conectado\n", cont);
            if (-1 == client_sd)
            {
                perror("Accept fails: ");
                close(server_sd);
                exit(EXIT_FAILURE);
            }
            for (int i = 1; i <= 10; i++)
            {
                if (cupos[i - 1] == 0)
                {
                    cupos[i - 1] = 1;
                    cupo = i;
                    break;
                }
            }
            
            clientaux[cupo - 1].socket = client_sd;
            clientaux[cupo - 1].rxState = 1;
            clientaux[cupo - 1].contadoraux = cupo;
            status = pthread_create(&(rxThreadId[cupo - 1]), NULL, &readThread, &(clientaux[cupo - 1]));
            if (-1 == status)
            {
                perror("Pthread read fails: ");
                close(server_sd);
                exit(EXIT_FAILURE);
            }
        }else{
            char buf[BUF_SIZE];
            int status;
            strcpy(buf, "Servidor lleno\n");
            status = write(client_sd, buf, strlen(buf) + 1);
            if (-1 == status)
            {
                perror("Server write to client fails: ");
                break;
            }
            close(client_sd);
        }
        
    }
    free(clientaux);
    free(rxThreadId);
    return 0;
}
