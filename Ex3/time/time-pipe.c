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

    pid_t pid;
    int pipe_fd[2];

    pipe(pipe_fd);

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;

    } else if (pid == 0) {


        close(pipe_fd[0]);

        struct timeval start;
        gettimeofday(&start, NULL);

        write(pipe_fd[1], &start, sizeof(start));

        execvp(argv[1], &argv[1]);
        exit(0);

    } else {

        wait(NULL);

        struct timeval end;
        gettimeofday(&end, NULL);

        close(pipe_fd[1]);

        struct timeval start;
        read(pipe_fd[0], &start, sizeof(start));

        printf("Elapsed time: %f",
               ((&end)->tv_sec - (&start)->tv_sec) + (((&end)->tv_usec - (&start)->tv_usec) / 1000000.0));

    }

    return 0;
}


