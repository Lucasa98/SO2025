#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Parametros
#define SIZE 5          // tamaño del deposito
#define MAX 10          // El maximo de veces que se puede producir

// Deposito (RECURSOS COMPARTIDOS)
int deposito[SIZE];     // vector donde producir o consumir. Min 0, Max 99
int producidos = 0;     // cant actual de items producidos
int consumidos = 0;     // cant actual de items consumidos
int i_prod = 0;
int i_cons = 0;

sem_t sem_vacio, sem_lleno;
pthread_mutex_t m;

void* productor(void *p) {
    int index = *(int*) p;
    int item;
    cout << "\033[;94m[P" << index << "] produciendo...\033[0m" << endl;
    while(1) {
        usleep(5000+rand()%10000);   // trabajando...

        sem_wait(&sem_vacio);
        item = rand()%100;

        // producir
        pthread_mutex_lock(&m);
        if(producidos >= MAX) {
            pthread_mutex_unlock(&m);
            break;
        }
        deposito[i_prod] = item;
        cout << "\033[;94m[P" << index << "] deposito[" << i_prod << "] <-" << setw(2) << right << item << "\033[0m" << endl;
        i_prod = (i_prod+1)%SIZE;

        ++producidos;
        pthread_mutex_unlock(&m);

        sem_post(&sem_lleno);
    }

    return NULL;
}

void* consumidor(void *p) {
    int index = *(int*) p;
    int item;
    cout << "\033[;92m[C" << index << "] consumiendo...\033[0m" << endl;
    while(1) {
        usleep(5000+rand()%10000);   // trabajando...
        sem_wait(&sem_lleno);
        // consumir
        pthread_mutex_lock(&m);
        if(consumidos >= MAX) {
            pthread_mutex_unlock(&m);
            break;
        }
        item = deposito[i_cons];
        cout << "\033[;92m[C" << index << "] deposito[" << i_cons << "]-> " << setw(2) << right << item << "\033[0m" << endl;
        i_cons = (i_cons+1)%SIZE;
        ++consumidos;
        pthread_mutex_unlock(&m);

        sem_post(&sem_vacio);
    }

    return NULL;
}

int main() {
    srand(time(0));

    // Consumidores y productores
    int C, P;
    cout << "N° de consumidores: "; cin >> C;
    cout << "N° de productores: "; cin >> P;
    int* indexs = new int[C+P];
    pthread_t* h = new pthread_t[C+P];

    pthread_mutex_init(&m, NULL);
    sem_init(&sem_vacio, 0, SIZE);  // se mantiene abierto mientras haya depositos vacios
    sem_init(&sem_lleno, 0, 0);

    // Iniciar consumidores y productores
    for(int i=0; i<C; ++i) {
        indexs[i] = i;
        pthread_create(h+i, NULL, consumidor, (void*)(indexs+i));
    }
    for(int i=0; i<P; ++i) {
        indexs[i+C] = i;
        pthread_create(h+C+i, NULL, productor, (void*)(indexs+C+i));
    }

    // Finalizar
    for(int i=0; i<P+C; ++i) {
        pthread_join(h[i], NULL);
    }

    pthread_mutex_destroy(&m);
    delete[] indexs, h;

    return 0;
}