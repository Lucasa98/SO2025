#include <stdio.h>
#include <unistd.h>
#include <thread>

using namespace std;

/**
 * thread en vez de pthread
 * Funcion lambda (C++11) en lugar de puntero a funcion
 */
int main() {
    thread h[8];
    for(int i=0; i<8; ++i) {
        h[i] = thread([]() {
            printf("Sistemas Operativos\n");
            sleep(10);
        });
    }
    for(int i=0; i<8; ++i) {
        h[i].join();
    }

    return 0;
}
