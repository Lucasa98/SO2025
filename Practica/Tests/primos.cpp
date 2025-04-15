#include <pthread.h>
#include <iostream>
#include <chrono>

using namespace std;

unsigned_int N = 0;
unsigned_int n1 = 0;
unsigned_int n2 = 0;
unsigned_int n3 = 0;
int estados;
bool esonoes = false;

void* hilo1(void* arg) {
	while(1) {
		if(n1 == 0) {
			int sq = sqrt(N);
			n1 = 2;
			if(N%n1 == 0) {
				esonoes = true;
				--estados;
			} else {
				n1 = 3;
				while(n1 <= sq && N%n1 != 0) {
					n1 += 6;
				}
				
				if(n1 <= sq) {
					esonoes = true;
				}
				--estados;
			}
		}
	}
}

void* hilo2(void* arg) {
	while(1) {
		if(n2 == 0) {
			int sq = sqrt(N);
			n2 = 5;
			while(n2 <= sq && N%n2 != 0) {
				n2 += 6;
			}
			
			if(n2 <= sq) {
				esonoes = true;
			}
			--estados;
		}
	}
}

void* hilo2(void* arg) {
	while(1) {
		if(n3 == 0) {
			int sq = sqrt(N);
			n3 = 7;
			while(n3 <= sq && N%n3 != 0) {
				n3 += 6;
			}
			
			if(n3 <= sq) {
				esonoes = true;
			}
			--estados;
		}
	}
}
