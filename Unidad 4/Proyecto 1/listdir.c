#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
int main(int argc, char *argv[])
{
    DIR *streamp;
    DIR *streampaux;
    char Copia[30];
    struct dirent *dep;
    struct dirent *depaux;
    if (argc != 2)
    {
        printf("Error en argumentos\n");
        exit(1);
    }
    streamp = opendir(argv[1]);
    errno = 0;
    strcpy(Copia, argv[1]);
    strcat(Copia, "/");
    while ((dep = readdir(streamp)) != NULL)
    {
        printf("Archivo encontrado: %s \n, Tipo: %d\n", dep->d_name, dep->d_type);
        if (dep->d_type == 4)
        {
            strcat(Copia, dep->d_name);
            streampaux = opendir(Copia);
            while((depaux = readdir(streampaux))!=NULL){
                printf("Subarchivo %s, encontrado en directorio: %s \n",depaux->d_name,Copia);
            }
            strcpy(Copia, argv[1]);
            strcat(Copia, "/");
        }
    }
    if (errno != 0)
    {
        unix_error("ReadDir error \n");
    }
    closedir(streamp);
    exit(0);
}
