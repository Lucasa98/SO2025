#include <pthread.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void* calcular_factores(void* arg) {
    int x = *(int*)arg;
    printf("%d\n", x);
    vector<int>* v = new vector<int>();

    int i = 2;
    while(x>1){
        while(x%i == 0){
            x = x/i;
            v->push_back(i);
        }
        ++i;
    }

    return (void*) v;
}

int main() {
    // inicializar
    int x[2];
    cout << "x1: "; cin >> x[0];
    cout << "x2: "; cin >> x[1];
    pthread_t h[2];
    pthread_attr_t attr[2];

    // crear hilos
    for(int i=0; i<2; ++i) {
        pthread_attr_init(attr+i);
        pthread_create(h+i, attr+i, calcular_factores, (void*)(x+i));
    }

    // recuperar valores
    vector<int> *v1, *v2;
    pthread_join(h[0], (void**)&v1);
    pthread_join(h[1], (void**)&v2);

    // mostrar
    for(int j=0; j<v1->size(); ++j)
        cout << (*v1)[j] << ' ';
    cout << endl;
    for(int j=0; j<v2->size(); ++j)
        cout << (*v2)[j] << ' ';
    cout << endl;

    return 0;
}