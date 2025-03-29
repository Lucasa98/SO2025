#include <stdio.h>
#include <sys/wait.h>

int main() {
    int i, pid;
    for(i=0; i<3; ++i) {
        pid = fork();
        printf("\n");
        execlp("ls", "ls", "-l", NULL);
        wait(NULL);
    }
    return 0;
}