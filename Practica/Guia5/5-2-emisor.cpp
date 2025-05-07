#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace std;

#define SHMKEY 0X70

int main() {
    // definiciones
    int shmid, N;
    int* n;

    cout << "Ingrese un numero: "; cin >> N;

    // solicitar memoria compartida
    shmid = shmget(SHMKEY, sizeof(int), 0777 | IPC_CREAT);

    // apuntar v a shm
    n = (int*)shmat(shmid, 0, 0);

    // cargar datos
    *n = N;

    cout << ">> Escritura en memoria (SHMKEY=" << SHMKEY << ") completa" << endl;

    // detach
    shmdt((void*)n);

    return 0;
}