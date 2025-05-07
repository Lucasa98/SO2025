#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

using namespace std;

#define SHMKEY 0X70

int main() {
    // definiciones
    int shmid, N;
    int* n;
    while(1) {
        // leer hasta que haya algo en memoria compartida
        shmid = shmget(SHMKEY, sizeof(int), 0);
        if(shmid < 0) {
            cout << "todavia nada en shm..." << endl;
            sleep(1);
        } else {
            // leer datos en shm
            n = (int*)shmat(shmid,0,0);

            cout << "<< Lectura de memoria (SHMKEY=" << SHMKEY << ") completa. N = " << *n << endl;
            break;
        }
    }
    shmdt((void*)n);

    return 0;
}