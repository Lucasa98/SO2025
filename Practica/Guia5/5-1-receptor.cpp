#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace std;

#define SHMKEY 0X70

int main() {
    // definiciones
    int shmid, cant = 10;
    int* v;

    // solicitar memoria compartida
    shmid = shmget(SHMKEY, cant * sizeof(int), 0777 | IPC_CREAT);

    if(shmid < 0) {
        cerr << "Region de memoria SHMKEY=" << SHMKEY << " no disponible" << endl;
        return 1;
    }

    // apuntar v a shm
    v = (int*)shmat(shmid, 0, 0);

    // imprimir datos de memoria compartida
    for(int i=0; i<10; ++i)
        cout << v[i] << ' ';
    cout << endl;

    cout << "<< Lectura de memoria (SHMKEY=" << SHMKEY << ")" << endl;

    // detach
    shmdt((void*)v);

    return 0;
}