// Anton Shepelev U28654378
// Programming HomeWork #1 - COP 6611 Spring 2022
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
 
int main(int argc, char* argv[]) {
    // Stuff for shared memory
    const int SIZE = 4096;
    const char* name = "antoxa ebt)";
    void* mainptr;
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    mainptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (argc == 2 || argc == 1)
    {
        //char* num = argv[1];
        int n = atoi(argv[1]);
        if (n > 0 && n < 40) {
            pid_t pid = fork();
            if (pid < 0)
            {
                printf("Error. Can not fork!");
                return 1;
            }
            else if (pid > 0)   // Parent proccess
            {
                wait();
            }
            else if (pid == 0) // Child process
            {
                sprintf(mainptr, "%d", n);
                mainptr += sizeof(n);
                printf("From Child 1 init n = %d \n", n);
                //int temp = n;
                while (n != 1) {
                    // Is even?
                    if (n % 2 == 0)
                        n = n / 2;
                    // Odd
                    else
                        n = n * 3 + 1;
                    // Output and increment pointer
                    printf("From Child 1 n = %d \n", n);
                    sprintf(mainptr, "%d", n);
                    mainptr += sizeof(n);
                }
            }
        }
        else {
            printf("Invalid input. Input should be an int within (0;40) interval.\n");
        }
    }
    // Unlink shared memory
    shm_unlink(name);
    return 0;
}