#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>

#define PORT 6666
#define BUF_SIZE 128
struct client_t
{
    int socket;
    int rxState;
};

void *readThread(void *arg)
{
    struct client_t *client = ((struct client_t *)arg);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];

    while (1)
    {
        numOfBytes = read(client->socket, buf, BUF_SIZE);
        if (0 == numOfBytes)
        {
            printf("Server closed the socket end\n");
            break;
        }
        else if (-1 == numOfBytes)
        {
            perror("ReadThread read() fails: ");
            break;
        }
        else
        {
            printf("%s\n", buf);
            if (strcmp(buf, "El servidor te desconecto\n") == 0)
                break;
        }
    }
    printf("Terminate Pthread for reading\n");
    client->rxState = 0;
    return NULL;
}

int main(int argc, char *argv[])
{

    char name[20];
    char buf[BUF_SIZE];
    int status;
    int server_sd;
    char msg[BUF_SIZE];
    char a = 0;
    printf("Ingrese su nombre de usuario por favor\n");
    scanf("%s", msg);
    scanf("%c", &a);
    strcpy(name, msg);
    strcat(msg, ": ");
    pthread_t rxThreadId;
    struct client_t client;

    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1)
    {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");

    //3. Connect to the server 127.0.0.1:PORT
    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    status = connect(server_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == status)
    {
        perror("Connect fails\n");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server connected\n");

    // 4. Create a thread for receiving messages from client
    client.socket = server_sd;
    client.rxState = 1;
    printf("Create Pthread for reading\n");

    status = pthread_create(&rxThreadId, NULL, &readThread, &client);
    if (-1 == status)
    {
        perror("Pthread read fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    status = write(client.socket, name, strlen(name) + 1);
    if (-1 == status)
    {
        perror("Server write to client fails: ");
    }

    while (1)
    {
        char send[BUF_SIZE];
        strcpy(send, msg);
        if (0 == client.rxState)
        {
            printf("Server closed the socket\n");
            break;
        }

        if (fgets(buf, BUF_SIZE, stdin) == NULL)
        {
            printf("Fgets NULL\n");
        }
        if (0 == strncmp(buf, ":exit", strlen(":exit")))
        {
            printf("Client exit\n");
            break;
        }

        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        strcat(send, buf);
        status = write(client.socket, send, strlen(send) + 1);
        if (-1 == status)
        {
            perror("Server write to client fails: ");
            break;
        }
    }
    close(client.socket);
    exit(EXIT_SUCCESS);
}