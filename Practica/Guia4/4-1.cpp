#include <stdio.h>
#include <pthread.h>

using namespace std;

void* listarNumeros(void* arg) {
    for(int i=1; i<=10; ++i) {
        printf("%d ",i);
    }
    printf("\n");

    return nullptr;
}

void* listarLetras(void* arg) {
    for(char i='a'; i <= 'z'; ++i) {
        printf("%c ",i);
    }
    printf("\n");

    return nullptr;
}

int main() {
    printf("comienzo\n");
    pthread_t h1, h2;
    pthread_attr_t attr1, attr2;
    pthread_create(&h1, &attr1, listarNumeros, NULL);
    pthread_create(&h2, &attr2, listarLetras, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    printf("final\n");

    return 0;
}