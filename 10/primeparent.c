#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    const int SIZE = 4096;
    int shm_fd;
    void *ptr;
    if (argc < 3)
    {
        printf("Error: not passing M and N in command line\n");
        exit(0);
    }
    pid = fork();
    if (pid == 0)
    {
        execlp("./prime", "prime", argv[1], argv[2], NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nPARENT: child completed\n");
        shm_fd = shm_open("OS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("Parent printing:\n");
        printf("%s", (char *)ptr);
        shm_unlink("OS");
    }
    return 0;
}

