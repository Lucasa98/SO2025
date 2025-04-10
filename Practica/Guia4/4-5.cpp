#include <pthread.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct param {
    int hi;
    int x;
};

void* calcular_factores(void* arg) {
    param* p = (param*)arg;
    int x = p->x;
    vector<int>* v = new vector<int>();

    int i = 2;
    while(x>1){
        while(x%i == 0){
            x = x/i;
            v->push_back(i);
        }
        ++i;
    }

    // mostrar ni bien terminan
    cout << "(hilo h[" << setfill('0') << setw(2) << p->hi << "] id: " << pthread_self() << ") " << p->x << ": ";
    for(vector<int>::iterator it=v->begin(); it != v->end(); ++it){
        cout << *it << ' ';
    }
    cout << endl;

    return (void*) v;
}

int main() {
    // cantidad de numeros
    int N;
    cout << "cuanto hilos -> "; cin >> N;

    // inicializar
    srand(time(0));
    param* p = new param[N];
    pthread_t* h = new pthread_t[N];
    pthread_attr_t* attr = new pthread_attr_t[N];

    // crear hilos
    for(int i=0; i<N; ++i) {
        // numero aleatorios entre 10000 y 10999
        p[i].hi = i;
        p[i].x = rand()%1000 + 10000000000;
        pthread_attr_init(attr+i);
        pthread_create(h+i, attr+i, calcular_factores, (void*)(p+i));
    }

    // recuperar valores
    for(int i=0; i<N; ++i) {
        pthread_join(h[i], NULL);
    }

    return 0;
}