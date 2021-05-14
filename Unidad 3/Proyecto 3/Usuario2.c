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
sem_t *semf1;
sem_t *semf2;
sem_t *semf3;
sem_t *semf4;
void *mapeo1;
void *mapeo2;

int shm_fd1 = 0;
int shm_fd2 = 0;



void reservarmemoria()
{                                             
    shm_fd1 = shm_open("shm1", O_RDWR, 0600); 
    if (shm_fd1 < 0)
    {
        shm_fd1 = shm_open("shm1", O_CREAT | O_RDWR, 0600);
        if (shm_fd1 < 0)
        {
            perror("Error memoria en  USER2");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd1, SIZE * sizeof(char)) < 0)
        {
            perror("Fallo en la trucation USER2");
            exit(EXIT_FAILURE);
        }
    }

    shm_fd2 = shm_open("shm2", O_RDWR, 0600); 
    if (shm_fd2 < 0)                          
    {
        shm_fd2 = shm_open("shm2", O_CREAT | O_RDWR, 0600); 
        if (shm_fd2 < 0)                                    
        {
            perror("Error memoria en USER1");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd2, SIZE * sizeof(char)) < 0)
        {
            perror("Fallo en la trucation USER1");
            exit(EXIT_FAILURE);
        }
    }
}
void cerrarmemoria()
{
    if (close(shm_fd2) < 1)
    {
        perror("Error al cerrar memoria");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink("shm2") < 0)
    { //Cerramos el link del archivo
        perror("FALLO EN EL UNLINK DEL SHM2");
        exit(EXIT_FAILURE);
    }
}
void encender()
{ 

    
    semf1 = sem_open("semaforo1", 0);
    while (semf1 == SEM_FAILED)
    {
        sleep(1); 
        semf1 = sem_open("semaforo1", 0);
    }
    semf2 = sem_open("semaforo2", 0);
    if (semf2 == SEM_FAILED)
    {
        
        mode_t permisos = 0666;
        int banderas = O_CREAT;
        unsigned int modo = 0;
        semf2 = sem_open("semaforo2", banderas, permisos, modo); 
        if (semf2 == SEM_FAILED)
        {
            perror("FALLO SEMAFORO 2 USER 2 ");
            exit(EXIT_FAILURE);
        }
    }
    semf3 = sem_open("semaforo3", 0);
    while (semf3 == SEM_FAILED)
    {
        sleep(1);
        semf3 = sem_open("semaforo3", 0);
    }
    semf4 = sem_open("semaforo4", 0);
    if (semf4 == SEM_FAILED)
    {

        mode_t permisos = 0666;
        int banderas = O_CREAT;
        unsigned int modo = 0;
        semf4 = sem_open("semaforo4", banderas, permisos, modo);
        if (semf4 == SEM_FAILED)
        {
            perror("USUARIO 2 FALLO EN SEMF4 ");
            exit(EXIT_FAILURE);
        }
    }
}

void apagar()
{
    //APAGAMOS EL SEMAFORO 2-4 QUE SON LOS DEL USER 2 Y HACEMOS EL UNLINK DE ELLOS
    if (sem_close(semf2) == -1)
    {
        perror("user2 sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    if (sem_close(semf4) == -1)
    {
        perror("user2 sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    //Destruimos el semaforo 2
    if (sem_unlink("semaforo2") == -1)
    {
        perror("user2 sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("semaforo4") == -1)
    {
        perror("user2 sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
}



void *msgleer()
{

    char *msgbuf;
    while (1)
    {
        if (sem_wait(semf1) == -1)
        {
            perror("sem_wait error en semaforo 2 USER1");
            exit(EXIT_SUCCESS);
        }

        mapeo1 = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd1, 0);
        if (mapeo1 == MAP_FAILED)
        {
            perror("ERROR EN EL MAPEO LECTURA USER 1");
            exit(EXIT_SUCCESS);
        }
        msgbuf = (char *)mapeo1;
        if (mapeo1 == NULL)
        {
            return NULL;
        }
        fprintf(stdout, "Pelao poco serio dice: %s", msgbuf);

        //UNMAPEAMOS
        if (munmap(msgbuf, SIZE) < 0)
        {
            perror("Error en el unmapeo de lectura USER1");
            exit(EXIT_SUCCESS);
        }
        if (sem_post(semf3) == -1)
        {
            perror("Error en sempost lectura SEM4 user1");
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
void *msgescribir()
{
    char *msgbuf;
    char buf[SIZE];
    mapeo2 = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shm_fd2, 0);
    if (mapeo2 == MAP_FAILED)
    {
        perror("Errorsito en el mapeo 1 ESCRITURA");
        exit(EXIT_FAILURE);
    }
    while (1)
    {

        msgbuf = (char *)mapeo2;
        if (fgets(buf, SIZE, stdin) == NULL)
        {
            break;
        }
        for (int i = 0; i < SIZE; i++)
        {
            msgbuf[i] = buf[i];
        }

        //SE ABRE EL SEMAFORO 2 DEL USER 2
        if (sem_post(semf2) == -1)
        {
            perror("sem_post error en escritura SEMAFORO 2");
            exit(EXIT_SUCCESS);
        }

        //CERRAMOS EL SEMAFORO 4 DEL USER 2
        if (sem_wait(semf4) == -1)
        {
            perror("sem_WAIT error en escritura SEMAFORO 4");
            exit(EXIT_SUCCESS);
        }
    }
    apagar();
    cerrarmemoria();
    return 0;
}
int main(void)
{

    pthread_t hilo1;
    pthread_t hilo2;

    encender();
    reservarmemoria();

    pthread_create(&hilo1, NULL, &msgescribir, NULL);
    pthread_create(&hilo2, NULL, &msgleer, NULL);

    pthread_join(hilo1, NULL);
    exit(EXIT_SUCCESS);
}
