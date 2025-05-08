#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define PIPE_PATH "/tmp/fifo1"
#define SIZE 256

int main() {
    string s;
    char txt[SIZE];

    /** 1- crear nuevo archivo de fifo SI NO EXISTE
     * S_IWUSR: DUEÑO tiene permiso de ESCRITURA
     * S_IRUSR: DUEÑO tiene permiso de LECTURA
     * S_IRGRP: GRUPO tiene permiso de LECTURA
     * S_IROTH: OTROS tienen permiso de LECTURA
     */
    if(stat(PIPE_PATH,0) != 0) {
        mkfifo(PIPE_PATH, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    }

    // 2- abrir fifo para lectura y esperar que otro lo abra para escritura
    cout << "Esperando escritor..." << endl;
    int fd = open(PIPE_PATH, O_RDONLY);

    // 2- leer archivo
    cout << "Leyendo mensaje..." << endl;
    read(fd, txt, SIZE);

    // 3- mostrar mensaje
    cout << "Mensaje recibido: \"" << txt << "\"." << endl;

    // 4- cerrar descriptor de archivo
    close(fd);

    return 0;
}