#include <stdio.h>
#include <unistd.h>

int Programa1() {
    unsigned int i, j, a, v[50000];
    for(i=0; i<50000; ++i)
        v[i] = i*i;

    printf("\nInicio\n");
    for(i=0; i<50000-1; ++i) {
        for(j=i+1; j<50000; ++j) {
            a = v[i];
            v[i] = v[j];
            v[j] = a;
        }
    }
    printf("\nOrdenamiento terminado!\n\n");
    execlp("/bin/ls", "ls", NULL);
    return 0;
}

int Programa2() {
    int pid;
    unsigned int i, j, a, v[50000];

    for(i=0; i<50000; ++i)
        v[i] = i * i;
    
    pid = fork();
    if (pid == 0) {
        printf("\nInicio\n");
        for(i=0; i<50000-1; ++i) {
            for(j=i+1; j<50000; ++j) {
                if(v[i] < v[j]) {
                    a = v[i];
                    v[i] = v[j];
                    v[j] = a;
                }
            }
        }
        printf("\nOrdenamiento terminado!\n\n");
        return 0;
    } else {
        execlp("/bin/ls", "ls", NULL);
        return 0;
    }
}

int main() {
    //return Programa1();
    return Programa2();
}