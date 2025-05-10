#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t sem;
long int acum;

void* mult(void* arg) {
    pair<int,int> *p = (pair<int,int>*)arg;

    int tid = pthread_self();
    int m = 1;
    for(int i=p->first; i<=p->second; ++i) {
        cout << '[' << tid << "] " << i << endl;
        m *= i;
    }

    cout << '[' << tid << "] " << "m = " << m << endl;
    sem_wait(&sem);
    acum *= m;
    sem_post(&sem);

    return NULL;
}

int main() {
    pthread_t th[2];
    pthread_attr_t attr[2];
    sem_init(&sem,0,1);
    int ini, fin, medio;
    acum = 1;

    // Ingresar limites
    cout << "Ingrese ini: "; cin >> ini;
    cout << "Ingrese fin: "; cin >> fin;
    medio = (fin+ini)/2;

    // Preparar hilos
    pthread_attr_init(attr);
    pthread_attr_init(attr+1);
    pair<int,int> *primero = new pair(ini,medio),
                  *segundo = new pair(medio+1, fin);

    pthread_create(th,attr,mult,(void*)primero);
    pthread_create(th+1,attr+1,mult,(void*)segundo);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);

    cout << ini << '*' << ini+1 << '*' << ini+2 << "*...*" << fin << " = " << acum << endl;

    delete primero, segundo;

    return 0;
}