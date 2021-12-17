#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    const int SIZE = 4096;
    const char *name = "OS";

    int fd;
    int number = atoi(argv[1]);
    
    if (argc != 2) {
        printf("Wrong number of parameters!");
        return 1;
    }

    if (number < 1) {
        printf("Positive integer required!");
        return 1;
    }

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);


    pid_t pid;

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;

    } else if (pid == 0) {

        int *mapm = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


        while (number != 1) {
            *mapm = number;
            mapm++;
            if (number % 2 == 0) {
                number /= 2;
            } else {
                number = (number * 3) + 1;
            }
        }
        *mapm = number;

        exit(0);

    } else {

        wait(NULL);

        int *mapm = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        while (*mapm != 1) {
            printf("%d, ", *mapm);
            mapm++;
        }
        printf("1 \n");

        shm_unlink(name);

    }

    return 0;
}


