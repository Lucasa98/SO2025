#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int i;

    pid = fork();
    pid = fork();

    if (pid ==0) {
        for (i=0; i<10; ++i) {
            printf("Hijo: %d (%d)\n", i, getpid());
            sleep(1);
        }
        return 0;
    } else if (pid > 0) {
        for (i=0; i<10; ++i) {
            printf("Padre: %d (%d)\n", i, getpid());
            sleep(1);
        }
        return 0;
    } else {
        printf("No se ha podido bifurcar");
    }

    return 0;
}