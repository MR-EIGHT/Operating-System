#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main((int argc, char **argv)) {
if (argc != 2){
    printf("Wrong number of parameters!");
    return 1;
}

int number = atoi(argv[1]);

    pid_t pid;
    pid = fork();
    
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed");
        return 1;
    
    } else if (pid == 0) {

        printf("%d",number);
        while (number != 1)
        {
            if (number % 2 == 0){
                number /= 2 ;
            }
            else{
                number = (number*3) + 1;
            }

        printf(",%d",number);

        }
        

        exit(0);
        
    } else { 

    }

    return 0;
}


