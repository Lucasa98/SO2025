#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int main() {
    for(int i=0; i<3; ++i){
        fork();
    }
    printf("Sistemas Operativos\n");
    sleep(10);

    return 0;
}
