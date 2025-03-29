#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 3;

    for(int i=0; i<n; ++i)
        fork();

    printf("FICH\n");
    sleep(5);
    return 0;
}