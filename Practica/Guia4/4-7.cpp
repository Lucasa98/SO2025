#include <iostream>
#include <vector>

using namespace std;

struct Data {
    Data(vector<vector<int>>* M0, vector<vector<int>>* M1, vector<vector<int>>* M2, int k):
        M0(M0), M1(M1), M2(M2), k(k) {}
    vector<vector<int>>* M0;
    vector<vector<int>>* M1;
    vector<vector<int>>* M2;
    int k;  // indice de la fila [0,N)
};

void* mult(void* arg) {
    Data* d = (Data*)arg;
    int k = d->k;
    int N = d->M0->size();
    vector<vector<int>>& M0 = *(d->M0);
    vector<vector<int>>& M1 = *(d->M1);
    vector<vector<int>>& M2 = *(d->M2);

    for(int i=0; i<N; ++i) {
        M2[k][i] = 0;
        for(int j=0; j<N; ++j) {
            M2[k][i] += M0[k][j] * M1[j][k];
        }
    }

    delete d;

    return nullptr;
}

void show(vector<vector<int>>* M) {
    for(int i=0; i<M->size(); ++i) {
        cout << "| ";
        for(int j=0; j<M->size(); ++j) {
            cout << (*M)[i][j] << ' ';
        }
        cout << "|\n";
    }
}

int main() {
    srand(time(0));

    // dimension
    int N;
    cout << "N: "; cin >> N;

    // inicializar
    vector<vector<int>>* M0 = new vector<vector<int>>(N, vector<int>(N));
    vector<vector<int>>* M1 = new vector<vector<int>>(N, vector<int>(N));
    vector<vector<int>>* M2 = new vector<vector<int>>(N, vector<int>(N));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            (*M0)[i][j] = rand()%10;
            (*M1)[i][j] = rand()%10;
        }
    }
    pthread_t* h = new pthread_t[N];
    pthread_attr_t* attr = new pthread_attr_t[N];

    for(int i=0; i<N; ++i) {
        pthread_attr_init(attr+i);
        Data* d = new Data(M0, M1, M2, i);
        pthread_create(h+i, attr+i, mult, (void*)d);
    }

    for(int i=0; i<N; ++i) {
        pthread_join(h[i], NULL);
    }

    cout << "M0 = \n";
    show(M0);
    cout << "M1 = \n";
    show(M1);
    cout << "M2 = \n";
    show(M2);

    return 0;
}