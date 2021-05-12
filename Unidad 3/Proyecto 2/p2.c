#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define PERMISOS 0644 //DEfinimos los permisos

struct msgbuf
{
    long mtype;
    char msg[200];
};

struct param
{
    int msqid;
};

//Debemos dividir el proceso en 2 hilos, uno cual reciba y otro cual envie, y por eso necesitamos 2 funciones de enviar y recibir

void *recibirmsg(void *param)
{ //FUNCION RECIBIR MENSAJE
    struct msgbuf buf;
    struct param *p = (struct param *)param;
    int holder;

    for (;;)
    {
        if (msgrcv(p->msqid, &buf, sizeof(buf.msg), 0, 0) == -1)
        {
            perror("error en msgrecieve");
            exit(8);
        }
        printf("Valencia:  %s \n", buf.msg);
        holder = strcmp(buf.msg, "XD");
        if (holder == 0)
        {
            break;
        }
    }
    printf("Conexion finalizada");

    exit(8);
}

void *enviarmsg(void *param)
{ //FUNCION ENVIAR MENSAJE
    struct msgbuf buf;
    struct param *p = (struct param *)param;
    int lenght;

    printf("Listo para enviar o recibir mensajes \n");
    printf("Ingresa mensaje\n");

    buf.mtype = 1;

    while (fgets(buf.msg, sizeof buf.msg, stdin) != NULL)
    {
        lenght = strlen(buf.msg);
        if (buf.msg[lenght - 1] == '\n')
        {
            buf.msg[lenght - 1] = '\0';
        }
        if (msgsnd(p->msqid, &buf, lenght + 1, 0) == -1)
        {
            perror("error  msgsnd");
        }
    }

    if (msgctl(p->msqid, IPC_RMID, NULL) == -1)
    {
        perror("error  msctl");
        exit(8);
    }
    exit(8);

} //FIN FUNCION ENVIAR

int main(void)
{

    int msqid1;
    int msqid2;
    key_t key1;
    key_t key2;
    pthread_t henvia;
    pthread_t hrecibe;

    if ((key1 = ftok("cola1.txt", 'B')) == -1)
    {
        perror("Error FTOK");
        exit(1);
    }

    if ((msqid1 = msgget(key1, PERMISOS | IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    if ((key2 = ftok("cola2.txt", 'B')) == -1)
    {
        perror("Error  FTOK");
        exit(1);
    }

    if ((msqid2 = msgget(key2, PERMISOS | IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    struct param paramh1;
    struct param paramh2;

    paramh1.msqid = msqid1;
    paramh2.msqid = msqid2;

    pthread_create(&henvia, NULL, &enviarmsg, &paramh2);
    pthread_create(&hrecibe, NULL, &recibirmsg, &paramh1);

    pthread_join(henvia, NULL);
    pthread_join(hrecibe, NULL);

    exit(1);
}
