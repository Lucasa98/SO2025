#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

sem_t sem1, sem2;

void* H1(void* arg) {
    sem_wait(&sem1);
    for(int i=0; i<=5; ++i) {
        sleep(rand()%2);
        cout << i << ' ' << flush;
    }
    sem_post(&sem2);

    return NULL;
}

void* H2(void* arg) {
    sem_wait(&sem2);
    for(int i=6; i<=10; ++i) {
        sleep(rand()%2);
        cout << i << ' ' << flush;
    }

    return NULL;
}

int main() {
    srand(time(0));
    pthread_t th[2];
    pthread_attr_t attr[2];

    pthread_attr_init(attr);
    pthread_attr_init(attr+1);
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    // ejecutamos primero H2 para asegurarnos que el orden no se debe al orden de creacion
    pthread_create(th+1,attr+1,H2,NULL);
    pthread_create(th,attr,H1,NULL);

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    for(int i=11; i<=15; ++i)
        cout << i << ' ';

    cout << endl;

    sem_close(&sem1);
    sem_close(&sem2);

    return 0;
}