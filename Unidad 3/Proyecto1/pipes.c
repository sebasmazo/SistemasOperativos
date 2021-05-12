#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 20

int main(int argc, char const *argv[])
{
    int pfd[2];
    int pfd2[2];
    char buf[BUF_SIZE];
    char msg[BUF_SIZE];
    ssize_t numRead;

    while (1)
    {
        if (pipe(pfd) == -1)
        { /* Create the pipe */
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        if (pipe(pfd2) == -1)
        { /* Create the pipe */
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: /* Child  - reads from pipe */
        //lECTURA
            if (close(pfd[1]) == -1)
            { /* Write end is unused */
                perror("close - child");
                exit(EXIT_FAILURE);
            }
            for (;;)
            { /* Read data from pipe, echo on stdout */
                numRead = read(pfd[0], buf, BUF_SIZE);
                if (numRead == -1)
                {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (numRead == 0){
                    break; /* End-of-file */
                }
            }
            for (int i = 0; i < strlen(buf); i++)
            {//MINUSCULAS
                buf[i] = buf[i] - 32;
            }
            if (close(pfd[0]) == -1)
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
            //ESCRITURA
            if (close(pfd2[0]) == -1)
            { /* Read end is unused */
                perror("close - child");
                exit(EXIT_FAILURE);
            }
            if (write(pfd2[1], buf, strlen(buf)) != strlen(buf))
            {
                perror("child - partial/failed write");
                exit(EXIT_FAILURE);
            }
            if (close(pfd2[1]) == -1)
            { /* Parent will see EOF */
                perror("close");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
            
        default: /* Parent - writes to pipe */
            if (close(pfd[0]) == -1)
            { /* Read end is unused */
                perror("close - parent");
                exit(EXIT_FAILURE);
            }

            scanf("%s", msg);

            if (write(pfd[1], msg, strlen(msg)) != strlen(msg))
            {
                perror("parent - partial/failed write");
                exit(EXIT_FAILURE);
            }
            if (close(pfd[1]) == -1)
            { /* Child will see EOF */
                perror("close");
                exit(EXIT_FAILURE);
            }

            ///////CODIGO LECTURA
            if (close(pfd2[1]) == -1)
            { /* Write end is unused */
                perror("close - parent");
                exit(EXIT_FAILURE);
            }
            for (;;)
            { /* Read data from pipe, echo on stdout */
                numRead = read(pfd2[0], buf, BUF_SIZE);
                if (numRead == -1)
                {
                    perror("read");
                    exit(EXIT_FAILURE);
                }

                if (numRead == 0)
                {
                    break; /* End-of-file */
                }
                printf("Mensaje hijo: \n");
                if (write(STDOUT_FILENO, buf, numRead) != numRead)
                {
                    perror("parent - partial/failed write");
                    exit(EXIT_FAILURE);
                }
            }
            write(STDOUT_FILENO, "\n", 1);
            if (close(pfd2[0]) == -1)
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
            wait(NULL); /* Wait for child to finish */
        }
    }
}
