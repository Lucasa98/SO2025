#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

const int num_iter = 100;   // N de iteraciones
const int tam_vector = 5;   // tamaño del vector
int vector[tam_vector];     // vector donde producir o consumir

int pos_productor = 0;
int pos_consumidor = 0;
int doble;

sem_t sem;  // AGREGAMOS UN SEMAFORO
// EL SEMAFORO CONTROLA LAS DOS INSTANCIAS DONDE SE ACCEDE A VECTOR[]
// INCLUIMOS TAMBIEN COUT EN LA SECCION CRITICA PARA EVITAR INTERCALADO DE TEXTO DE DISTINTAS INSTANCIAS

int producir_dato() {
    // 'dato' es static, por lo que se inicializa solo en la primer llamada a la funcion
    static int dato = 0;
    ++dato;
    return dato;
}

void duplicar_dato(int dato) {
    doble = dato*2;
    cout << "Dato duplicado: " << doble << endl;
}

void* productor(void *p) {
    // El productor produce un dato (1) en cada posicion del vector [num_iter] veces (cuando llega al final, vuelve al inicio y sigue)
    for(unsigned long i=0; i<num_iter; ++i) {
        int dato = producir_dato();
        sem_wait(&sem);     // TOMA EL CONTROL
        vector[pos_productor % tam_vector] = dato;
        ++pos_productor;
        cout << "Dato producido: " << dato << endl;
        sem_post(&sem);     // CEDE EL CONTROL
    }

    return NULL;
}

void* consumidor(void *p) {
    // El consumidor recorre el vector de la misma forma, pero consume el dato e imprime el doble.
    for(unsigned long i=0; i<num_iter; ++i) {
        sem_wait(&sem);     // TOMA EL CONTROL
        int dato = vector[pos_consumidor % tam_vector];
        ++pos_consumidor;
        duplicar_dato(dato);
        sem_post(&sem);     // CEDE EL CONTROL
    }

    return NULL;
}

int main() {
    pthread_t h[2];

    sem_init(&sem,0,1);     // INICIALIZAMOS EL SEMAFORO

    pthread_create(h, NULL, productor, NULL);
    pthread_create(h+1, NULL, consumidor, NULL);

    pthread_join(h[0], NULL);
    pthread_join(h[1], NULL);

    return 0;
}