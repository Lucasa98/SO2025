#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

using namespace std;

sem_t sem_B, sem_A, sem_C, sem_F;

void *A(void *) {
    while(1) {
        sem_wait(&sem_A);
        cout << "A";
        sem_post(&sem_F);   // A destraba C y B
    }
}

void *B(void *) {
    while(1) {
        sem_wait(&sem_B);   // cerrojo destrabado por C
        sem_wait(&sem_F);   // cerrojo destrabado por A
        cout << " B";
        sem_post(&sem_C);   // B destraba C
        sem_post(&sem_A);   // B destraba A
    }
}

void *C(void *) {
    while(1) {
        sem_wait(&sem_C);   // cerrojo destrabado por B
        sem_wait(&sem_F);   // cerrojo destrabado por A
        cout << "C";
        sem_post(&sem_B);   // C destraba B
        sem_post(&sem_A);   // C destraba A otra vez
    }
}

int main() {
    pthread_t th[3];
    pthread_attr_t attr[3];

    for(int i=0; i<3; ++i) {
        pthread_attr_init(attr+i);
    }

    sem_init(&sem_A,0,0);
    sem_init(&sem_B,0,1);   // empezamos por B
    sem_init(&sem_C,0,0);
    sem_init(&sem_F,0,1);   // destraba B para empezar

    pthread_create(th+0,attr+0,A,NULL);
    pthread_create(th+1,attr+1,B,NULL);
    pthread_create(th+2,attr+2,C,NULL);

    for(int i=0; i<3; ++i) {
        pthread_join(th[i],NULL);
    }

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    sem_destroy(&sem_F);

    return 0;
}
