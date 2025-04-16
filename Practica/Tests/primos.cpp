#include <pthread.h>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

int NUM_THREADS;	// cantidad de hilos utilizados
unsigned int N;		// numero evaluandose
bool DONE;			// bandera de parada
bool ESPRIMO;

// optimizaciones
int INCREMENTO;
unsigned int SQRT;	// raiz cuadrada de N

void* esPrimoConcurrente(void* arg) {
	int i = *((int*) arg);

	unsigned int num = 3+2*i;
	while(!DONE && num <= SQRT && N%num != 0) {
		num += INCREMENTO;
	}
	if(!DONE && num <= SQRT) {
		ESPRIMO = false;
		DONE = true;
	}

	return NULL;
}

int main() {
	// entrada
	int num_primos;
	cout << "Numero de hilos: "; cin >> NUM_THREADS;
	cout << "Numero de primos: "; cin >> num_primos;

	// inicializaciones
	INCREMENTO = 2*NUM_THREADS;
	int* d = new int[NUM_THREADS];	// vamos a usar los mismos indices siempre
	int c = 1;						// empezamos contando el 2
	N = 3;
	pthread_t* h = new pthread_t[NUM_THREADS];
	pthread_attr_t* attr = new pthread_attr_t[NUM_THREADS];
	for(int i=0; i<NUM_THREADS; ++i) {
		d[i] = i;					// vamos a usar siempre los mismos i
		pthread_attr_init(attr+i);
	}

	auto t = chrono::high_resolution_clock::now();
	while(c < num_primos) {
		SQRT = sqrt(N);
		ESPRIMO = true;
		DONE = false;
		for(int i=0; i<NUM_THREADS; ++i){
			pthread_create(h+i, attr+i,esPrimoConcurrente,(void*) (d+i));
		}
		for(int i=0; i<NUM_THREADS; ++i){
			pthread_join(h[i],NULL);
		}
		if(ESPRIMO)
			++c;
		N += 2;
	}
	cout << "ultimo primo: " << N-2 << endl;

	auto Tthreads = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();
    cout << "Tthreads: " << Tthreads << "ms" << endl;

	return 0;
}
