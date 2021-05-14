#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#define SIZE 40
sem_t *semaforo1;
sem_t *semaforo2;
sem_t *semaforo3;
sem_t *semaforo4;

void *map1;
void *map2;

int shm_fd1 = 0;
int shm_fd2 = 0;
void cerrarmemoria() //Función para cerrar la memoria compartida
{
    if (close(shm_fd1) < 0)
    {
        perror("Error al cerrar memoria");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink("shm1") < 0)
    { //desconectamos del archivo
        perror("unlink failed");
        exit(EXIT_FAILURE);
    }
}
void reservarmemoria()
{ //Reservar espacio de memoria
    shm_fd1 = shm_open("shm1", O_RDWR, 0600);
    if (shm_fd1 < 0)
    {
        shm_fd1 = shm_open("shm1", O_CREAT | O_RDWR, 0600);
        if (shm_fd1 < 0)
        {
            perror("Error memoria USER1");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd1, SIZE * sizeof(char)) < 0)
        {
            perror("Fallo trucation USER1");
            exit(EXIT_FAILURE);
        }
    }
    shm_fd2 = shm_open("shm2", O_RDWR, 0600); 
    if (shm_fd2 < 0)                          
    {
        shm_fd2 = shm_open("shm2", O_CREAT | O_RDWR, 0600);
        if (shm_fd2 < 0)
        {
            perror("Error memoria USER1");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd2, SIZE * sizeof(char)) < 0)
        {
            perror("Fallo trucation USER1");
            exit(EXIT_FAILURE);
        }
    }
}
void encender() //Iniciar semaforos
{ 

    semaforo1 = sem_open("semaforo1", 0);
    if (semaforo1 == SEM_FAILED)
    { //Si falla entonces lo creamos
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value = 0;
        semaforo1 = sem_open("semaforo1", flags, perms, value); //creamos el semaforo
        if (semaforo1 == SEM_FAILED)
        {
            perror("Usuario1 sem1_open: ");
            exit(EXIT_FAILURE); 
        }
    }
    semaforo2 = sem_open("semaforo2", 0);
    while (semaforo2 == SEM_FAILED)
    {
        sleep(1); 
        semaforo2 = sem_open("semaforo2", 0);
    }
    semaforo3 = sem_open("semaforo3", 0);
    if (semaforo3 == SEM_FAILED)
    {
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value = 0;
        semaforo3 = sem_open("semaforo3", flags, perms, value);
        if (semaforo3 == SEM_FAILED)
        {
            perror("Error en el semaforo 3");
            exit(EXIT_FAILURE);
        }
    }
    semaforo4 = sem_open("semaforo4", 0);
    while (semaforo4 == SEM_FAILED)
    {
        sleep(1);
        semaforo4 = sem_open("semaforo4", 0);
    }
}
void apagar()
{ 

    //Apagamos lectura y escritura
    if (sem_close(semaforo1) == -1)
    {
        perror("FALLO EN EL CLOSE DEL SEM1");
        exit(EXIT_FAILURE);
    }
    if (sem_close(semaforo3) == -1)
    {
        perror("FALLO EN EL CLOSE DEL SEM3");
        exit(EXIT_FAILURE);
    }
    //HACEMOS EL UNLINK DE LOS SEMAFORITOS
    if (sem_unlink("semaforo1") == -1)
    {
        perror("FALLO EN EL UNLINK SEM DEL SEMAFORO1");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("semaforo3") == -1)
    {
        perror("FALLO EN EL UNLINK DEL SEMAFORO3");
        exit(EXIT_FAILURE);
    }
}

void *msgescribir()
{

    char *msgbuf;
    char buf[SIZE];
    map1 = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shm_fd1, 0);
    if (map1 == MAP_FAILED)
    {
        perror("Error en mapeo 1 ESCRITURA");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        

        msgbuf = (char *)map1;
        if (fgets(buf, SIZE, stdin) == NULL)
        {
            break;
        }
        for (size_t i = 0; i < SIZE; i++)
        {
            msgbuf[i] = buf[i];
        }

        if (sem_post(semaforo1) == -1) //Semaforo 1 Abierto
        {
            perror("sem_post error en escritura SEMAFORO 1");
            exit(EXIT_SUCCESS);
        }

        if (sem_wait(semaforo3) == -1) //Semaforo 3 Cerrado
        {
            perror("sem_WAIT error en escritura SEMAFORO 3");
            exit(EXIT_SUCCESS);
        }
    }
    apagar();
    cerrarmemoria();
    return 0;
}
void *msgleer()
{
    map2 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd2, 0);
    if (map2 == MAP_FAILED)
    {
        perror("ERROR EN EL MAPEO LECTURA USER 1");
        exit(EXIT_SUCCESS);
    }
    char *msgbuf;
    while (1)
    {
        if (sem_wait(semaforo2) == -1)
        {
            perror("sem_wait error en semaforo 2 USER1");
            exit(EXIT_SUCCESS);
        }

        
        msgbuf = (char *)map2;
        if (map2 == NULL)
        {
            return NULL;
        }
        fprintf(stdout, "Pelao serio dice: %s", msgbuf);

        //UNMAPEAMOS
        if (munmap(msgbuf, SIZE) < 0)
        {
            perror("Error en el unmapeo de lectura USER1");
            exit(EXIT_SUCCESS);
        }
        if (sem_post(semaforo4) == -1) //Abrimos el semaforo 4 que es el del otro usuario para avisarle
        {
            perror("Error en sempost lectura SEM4 user1");
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
int main(void)
{

    pthread_t h1;
    pthread_t h2;

    //Funciones principales
    encender();
    reservarmemoria();

    //HILOS PARA GARANTIZAR PROCESO DE LECTURA Y ESCRITURA
    pthread_create(&h1, NULL, &msgescribir, NULL); 
    pthread_create(&h2, NULL, &msgleer, NULL);

    pthread_join(h1, NULL);
    exit(EXIT_SUCCESS);
}
