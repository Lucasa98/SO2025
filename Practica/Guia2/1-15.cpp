#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int i = 0;
    int nivel = 0;
    printf("Padre supremo %d\n", getpid());
    for(i=0; i<3; ++i) {
        if(fork() != 0) {
            for(int j=0; j<nivel; ++j)
                printf("--");
            printf("Proceso %d hijo de %d\n", getpid(), getppid());
            wait(NULL);
        } else {
            ++nivel;
        }
    }
    return 0;
}