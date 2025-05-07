#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace std;

#define SHMKEY 0X70

int main() {
    // definiciones
    srand(time(0));
    int shmid, cant = 10;
    int* v;

    // solicitar memoria compartida
    shmid = shmget(SHMKEY, cant * sizeof(int), 0777 | IPC_CREAT);

    // apuntar v a shm
    v = (int*)shmat(shmid, 0, 0);

    // cargar datos
    for(int i=0; i<10; ++i)
        v[i] = rand()%100;

    // imprimir datos cargados
    for(int i=0; i<10; ++i)
        cout << v[i] << ' ';
    cout << endl;

    cout << ">> Escritura en memoria (SHMKEY=" << SHMKEY << ")" << endl;

    // detach
    shmdt((void*)v);

    return 0;
}