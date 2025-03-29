#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    printf("Inicio\n");
    for(i=0; i<4; ++i) {
        if(fork() != 0)
            break;
    }
    sleep(30);
    return 0;
}