#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

int a = 0;

struct registro {
    registro(string cadena, int valor1, float valor2):
        cadena(cadena),
        valor1(valor1),
        valor2(valor2){};
    string cadena;
    int valor1;
    float valor2;
};

void* func1(void* arg) {
    ++a;
    printf("func1: %d\n",a);
    int* x = (int*)arg;
    while(1) {
        printf("x: %d\n", *x);
        sleep(5);
    }

    return nullptr;
}

void* func2(void* arg){
    ++a;
    printf("func2: %d\n",a);
    float* y = (float*)arg;
    while(1) {
        printf("y: %f\n", *y);
        sleep(5);
    }

    return nullptr;
}

void* func3(void* arg) {
    ++a;
    printf("func3: %d\n",a);
    registro* z = (registro*)arg;
    while(1) {
        printf("z->cadena: %s\nz->valor1: %d\nz->valor2: %f\n",
            z->cadena.c_str(), z->valor1, z->valor2);
        sleep(5);
    }

    return nullptr;
}

int main() {
    // init
    pthread_t h[3];
    pthread_attr_t attr[3];
    for(int i=0; i<3; ++i){
        pthread_attr_init(attr+i);
    }
    int* x = new int(15);
    float* y = new float(3.33f);
    registro* z = new registro("hola", 10, 22.22f);

    // crear hilos
    pthread_create(h,attr,func1,(void*)x);
    pthread_create(h+1,attr+1,func2,(void*)y);
    pthread_create(h+2,attr+2,func3,(void*)z);

    pthread_join(h[0],NULL);
    pthread_join(h[1],NULL);
    pthread_join(h[2],NULL);

    delete x,y,z;

    return 0;
}