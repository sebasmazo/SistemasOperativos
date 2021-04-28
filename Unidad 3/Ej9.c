#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 20
int main(int argc, char const *argv[])
{
    int pfd[2],n_Bytes;
    pid_t pid_hijo;
    char buf[BUF_SIZE];
    if(argc!=3){
        printf("Sintaxis comando: %s mensajePadre mensajeHijo",argv[0]);
        exit(EXIT_FAILURE);
    }
    if(pipe(pfd)<0){
        printf("Error en el pipe");
        return 0;
    }
    pid_hijo = fork();
    if(pid_hijo == 0){
        printf("Proceso hijo, mensaje: %s \n", argv[2]);
        n_Bytes= read(pfd[0],buf,BUF_SIZE);
        if(n_Bytes>0){
            printf("Mensaje de mi padre, mensaje: %s \n");
        }
        else{
            return 0;
        }
        close(pfd[0]);
        write(pfd[1],argv[2],BUF_SIZE);
        close(pfd[1]);
        return 0;
    }else{
        printf("Proceso padre, mensaje: %s\n",argv[1]);
        write(pfd[1],argv[1],BUF_SIZE);
        close(pfd[1]);
        wait(NULL);
        n_Bytes = read(pfd[0], buf, BUF_SIZE);
        if (n_Bytes > 0)
            printf("Mensaje de mi hijo, mensaje: %s\n", buf);
        else
            return 0;
        close(pfd[0]);
        return 0;
    }
    return 0;
}
