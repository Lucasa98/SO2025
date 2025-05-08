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

    // Leer mensaje
    cout << "Ingresar mensaje [max 256]: ";
    getline(cin, s);
    strcpy(txt, s.c_str());

    // 3- abrir fifo para escritura y esperar que otro lo abra para lectura
    cout << "Esperando lector..." << endl;
    int fd = open(PIPE_PATH, O_WRONLY);

    // 4- escribir archivo
    cout << "Enviando mensaje..." << endl;
    write(fd, txt, SIZE);
    cout << "Mensaje \"" << txt << "\" enviado" << endl;

    // 5- cerrar descriptor del archivo
    close(fd);

    return 0;
}