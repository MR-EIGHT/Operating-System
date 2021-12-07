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

int main((int argc, char **argv)) {
    const int SIZE = 4096;
    const char *name = "OS";

    int fd;

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);


    pid_t pid;

    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {

        void* mapm = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        struct timeval start;
        gettimeofday(&start, NULL);

        memcpy(mapm, &start, sizeof(start));

        execvp(argv[1], &argv[1]);
        exit(0)
        
    } else { 

        wait(NULL);

        void* mapm = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        struct timeval end;
        gettimeofday(&end, NULL);

        struct timeval * start = (struct timeval *) mapm;
        printf("%ld.%ld", (&end)->tv_sec - start->tv_sec,(&end)->tv_usec - start->tv_usec);
        shm_unlink(name);

    }

    return 0;
}


