#include <pthread.h>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

unsigned int N = 0;
unsigned int n1 = 0;
unsigned int n2 = 0;
unsigned int n3 = 0;
float sq;
int estados;
bool esprimo = false;

void* hilo1(void* arg) {
	while(1) {
		if(n1 == 0) {
			n1 = 2;
			if(N%n1 == 0) {
				esprimo = false;
				--estados;
			} else {
				n1 = 3;
				while(n1 <= sq && N%n1 != 0) {
					n1 += 6;
				}
				
				if(n1 <= sq) {
					esprimo = false;
				}
				--estados;
			}
		}
	}
}

void* hilo2(void* arg) {
	while(1) {
		if(n2 == 0) {
			n2 = 5;
			while(n2 <= sq && N%n2 != 0) {
				n2 += 6;
			}
			
			if(n2 <= sq) {
				esprimo = false;
			}
			--estados;
		}
	}
}

void* hilo3(void* arg) {
	while(1) {
		if(n3 == 0) {
			n3 = 7;
			while(n3 <= sq && N%n3 != 0) {
				n3 += 6;
			}
			
			if(n3 <= sq) {
				esprimo = false;
			}
			--estados;
		}
	}
}

int main() {
	pthread_t* h = new pthread_t[3];
	pthread_attr_t* attr = new pthread_attr_t[3];
	for(int i=0; i<3; ++i) {
		pthread_attr_init(attr+i);
	}

	auto t = chrono::high_resolution_clock::now();
	pthread_create(h, attr, hilo1, NULL);
	pthread_create(h+1, attr+1, hilo2, NULL);
	pthread_create(h+2, attr+2, hilo3, NULL);

	int c = 0;
	int numPrimos = 10000;
	N = 5;
	while(c < numPrimos) {
		esprimo = true;
		estados = 3;
		sq = sqrt(N);
		n1 = 0;
		n2 = 0;
		n3 = 0;
		while(!esprimo && estados){}
		n1 = N;
		n2 = N;
		n3 = N;
		if(esprimo)
			++c;
		N+=2;
	}
	cout << "ultimo primo: " << N-2 << endl;

	pthread_cancel(h[0]);
	pthread_cancel(h[1]);
	pthread_cancel(h[2]);
	auto Tthreads = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t).count();

	return 0;
}
