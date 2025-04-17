#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

/*
Se inicializa un numero de hilos a eleccion que esperaran un valor (!DONE[i]) para empezar a verificar si N es primo.
Para verificar que N es primo, cada hilo usara un subset de candidatos a divisor impares de 3 hasta raiz cuadrada de N.
El subset que debe verificar un hilo esta dado por el indice asignado al hilo y un INCREMENTO.
El proceso principal (main) esperara que todos los hilos hayan terminado (DONE[i]) para verificar si alguno encontro un divisor (!ESPRIMO[i]).
Para evitar que dos hilos escriban/lean la misma variable al mismo tiempo, se les asigna unas banderas DONE y ESPRIMO a cada uno.

Aunque creamos los hilos una unica vez, ahorrandonos la inicializacion cada vez que los necesitamos, la version multihilo es ligeramente PEOR.
Por ejemplo, para 1M de primos, con 3 hilos la version multihilo necesita ~4650ms, mientras que la monohilo necesita ~2059ms. Casi el triple
PROBABLEMENTE esto se debe a la cantidad de logica usada en el "semaforo"
*/

unsigned int N;		// numero evaluandose
bool STOP;			// bandera de parada que controla main
bool EXIT;
bool* DONE;			// bandera de estado de hilos
bool* ESPRIMO;

// optimizaciones
int INCREMENTO;
unsigned int SQRT;	// raiz cuadrada de N

bool esPrimo(){
	unsigned int num = 3;
	while(num <= SQRT) {
		if(N%num == 0)
			return false;
		num += 2;
	}

	return true;
}

void* esPrimoConcurrente(void* arg) {
	int i = *((int*) arg);

	unsigned int num = 3+2*i;
	unsigned int aux = num;
	unsigned int n;
	unsigned int sqrt;
	while(!EXIT){
		if(!DONE[i]){
			num = aux;
			// el uso de variable locales es mas rapido
			n = N;
			sqrt = SQRT;
			while(!STOP && num <= sqrt) {
				if(n%num == 0) {
					ESPRIMO[i] = false;
					break;
				}
				num += INCREMENTO;
			}
			DONE[i] = true;
		}
	}

	return NULL;
}

int main() {
	// entrada
	int num_primos;
	cout << "===================================" << endl;
	cout << "Numero de primos: "; cin >> num_primos;

	////////////////////////////////////////////
	///////////////// MONOHILO /////////////////
	////////////////////////////////////////////
	int c = 1;
	N = 3;
	auto t = chrono::high_resolution_clock::now();
	while(c < num_primos) {
		SQRT = sqrt(N);
		if(esPrimo())
			++c;
		N += 2;
	}
	auto Tmono = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();

	cout << "Primo N°" << num_primos << ": " << N-2 << endl;
    cout << "Tmono: " << Tmono << "ms" << endl;

	/////////////////////////////////////////////
	///////////////// MULTIHILO /////////////////
	/////////////////////////////////////////////

	for(int num_threads=2; num_threads<9; ++num_threads){
		cout << "===================================" << endl;
		cout << "Numero de hilos: " << num_threads << endl;

		// inicializaciones
		INCREMENTO = 2*num_threads;
		STOP = false;
		EXIT = false;
		DONE = new bool[num_threads];
		ESPRIMO = new bool[num_threads];
		int* d = new int[num_threads];	// vamos a usar los mismos indices siempre
		c = 1;						// empezamos contando el 2
		N = 3;
		pthread_t* h = new pthread_t[num_threads];
		pthread_attr_t* attr = new pthread_attr_t[num_threads];
		cpu_set_t* cpuset = new cpu_set_t[num_threads];
		for(int i=0; i<num_threads; ++i) {
			DONE[i] = true;
			d[i] = i;					// vamos a usar siempre los mismos i
			pthread_attr_init(attr+i);
			pthread_create(h+i, attr+i,esPrimoConcurrente,(void*) (d+i));
			// asignar un core especifico a cada thread
			CPU_ZERO(cpuset+i);
			CPU_SET(i, cpuset+i);
			pthread_setaffinity_np(h[i],sizeof(cpuset[i]), cpuset+i);
		}

		int i=0;
		int esprimo = true;
		int next_sqrt = sqrt(N);
		t = chrono::high_resolution_clock::now();
		while(c < num_primos) {
			SQRT = next_sqrt;
			// "arrancar" los threads
			STOP = false;
			for(i=0; i<num_threads; ++i) {
				ESPRIMO[i] = true;
				DONE[i] = false;
			}
			esprimo = true;
			i=0;
			// precalcular la proxima sqrt mientras los hilos estan ocupados
			next_sqrt = sqrt(N+2);
			// Condicion se parada: que todos los hilos terminen (DONE)
			while(i < num_threads) {
				i=0;
				while(i<num_threads && DONE[i]) {
					// al mismo tiempo chequeamos su bandera de primo
					if(esprimo && !ESPRIMO[i]) {
						esprimo = false;
					}
					++i;
				}

				if(!esprimo) {
					STOP = true;
				}
			}

			if(esprimo)
				++c;
			N += 2;
		}
		auto Tthreads = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();
		EXIT = true;

		for(int i=0; i<num_threads; ++i) {
			pthread_cancel(h[i]);
		}

		delete[] d;
		delete[] DONE;
		delete[] ESPRIMO;

		cout << "Primo N°" << num_primos << ": " << N-2 << endl;
		cout << "Tthreads: " << Tthreads << "ms" << endl;
	}

	return 0;
}
