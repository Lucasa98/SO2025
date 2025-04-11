#include <pthread.h>
#include <iostream>
#include <chrono>

using namespace std;

struct Data {
    Data(int* f1, int* f2, int* f3, int N): f1(f1), f2(f2), f3(f3), N(N){}
    int* f1;
    int* f2;
    int* f3;
    int N;
};

void* sumar(void* arg) {
    Data* d = (Data*)arg;

    for(int i=0; i<d->N; ++i) {
        d->f3[i] = d->f1[i] + d->f2[i];
    }

    delete d;
    return nullptr;
}

void show(int* M, int N) {
    for(int i=0; i<N; ++i) {
        cout << "| ";
        for(int j=0; j<N; ++j) {
            cout << M[i*N + j] << ' ';
        }
        cout << '|' << endl;
    }
}

int main() {
    srand(time(0));

    // dimension
    int N;
    cout << "N: "; cin >> N;

    // inicializacion
    int* M0 = new int[N*N];
    int* M1 = new int[N*N];
    int* M2 = new int[N*N];
    for(int i=0; i<N*N; ++i) {
        M0[i] = rand()%39 + 10;
        M1[i] = rand()%39 + 10;
    }

    pthread_t* h = new pthread_t[N];
    pthread_attr_t* attr = new pthread_attr_t[N];
    for(int i=0; i<N; ++i) {
        pthread_attr_init(attr+i);
    }

    auto t = chrono::high_resolution_clock::now();
    for(int i=0; i<N; ++i) {
        Data* d = new Data(M0+(i*N), M1+(i*N), M2+(i*N), N);
        pthread_create(h+i, attr+i, sumar, (void*)d);
    }

    for(int i=0; i<N; ++i) {
        pthread_join(h[i], NULL);
    }
    auto Tthreads = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();

    cout << "Tthreads: " << Tthreads << "ms" << endl;
    /*
    cout << "M0 = \n";
    show(M0,N);
    cout << "M1 = \n";
    show(M1,N);
    cout << "M2 = M0+M1 = \n";
    show(M2,N);
    */

    // Version sin threads para comparar
    for(int i=0; i<N*N; ++i) {
        M0[i] = rand()%39 + 10;
        M1[i] = rand()%39 + 10;
    }

    t = chrono::high_resolution_clock::now();
    for(int i=0; i<N*N; ++i) {
        M2[i] = M0[i] + M1[i];
    }
    auto Tmono = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();

    cout << "Tmono: " << Tmono << "ms" << endl;
    /*
    cout << "M0 = \n";
    show(M0,N);
    cout << "M1 = \n";
    show(M1,N);
    cout << "M2 = M0+M1 = \n";
    show(M2,N);
    */

    delete M0,M1,M2;
    return 0;
}