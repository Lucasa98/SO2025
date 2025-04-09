#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* so(void* arg) {
    printf("Sistemas Operativos\n");
    sleep(10);

    return nullptr;
}

int main() {
    pthread_t h[8];
    pthread_attr_t attr[8];
    for(int i=0; i<8; ++i) {
        pthread_attr_init(attr+i);
        pthread_create(h+i, attr+i, so, NULL);
    }
    for(int i=0; i<8; ++i) {
        pthread_join(h[i],NULL);
    }

    return 0;
}
