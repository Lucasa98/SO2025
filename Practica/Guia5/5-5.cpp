#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

using namespace std;

#define SIZE 256

int main() {
    int pipeIda[2], pipeVuelta[2];
    char txt[SIZE];
    
    pipe(pipeIda);
    pipe(pipeVuelta);
    
    int pid = fork();
    if(pid != 0) {  // Padre
        // cerrar lectura
        close(pipeIda[0]);

        cout << "PADRE>> Enviando mensaje..." << endl;
        // escribir mensaje
        strcpy(txt, "que onda che");

        // Enviar mensaje escribiendo en el pipe
        write(pipeIda[1], txt, strlen(txt)+1);

        cout << "PADRE>> Mensaje enviado" << endl;;
        // cerrar extremo de escritura
        close(pipeIda[1]);

        // Esperar mensaje
        close(pipeVuelta[1]);
        cout << "PADRE>> Esperando mensaje..." << endl;
        while(read(pipeVuelta[0], txt, sizeof(txt)) <= 0) {
            cout << "PADRE>> Esperando mensaje" << endl;
        }

        // Escribir hasta vaciar pipe
        cout << "PADRE>> Mensaje recibido de hijo: " << txt << endl;
        while(read(pipeVuelta[0], txt, sizeof(txt)) > 0) {
            cout << "PADRE>> Mensaje recibido de hijo: " << txt << endl;
        }

        close(pipeVuelta[0]);
    } else {        // Hijo
        // cerrar extremo de escritura
        close(pipeIda[1]);

        // Esperar mensajae
        cout << "HIJO>> Esperando mensaje..." << endl;
        while(read(pipeIda[0], txt, sizeof(txt)) <= 0) {
            cout << "HIJO>> Esperando mensaje de padre" << endl;
        }

        // Escribir hasta vaciar pipe
        cout << "HIJO>> Mensaje recibido de padre: " << txt << endl;
        while(read(pipeIda[0], txt, sizeof(txt)) > 0) {
            cout << "HIJO>> Mensaje recibido de padre: " << txt << endl;
        }

        // cerrar lectura
        close(pipeIda[0]);

        // Enviar mensaje
        close(pipeVuelta[0]);

        cout << "HIJO>> Enviando mensaje..." << endl;

        strcpy(txt, "todo bien viejo, que onda");

        write(pipeVuelta[1], txt, strlen(txt)+1);

        cout << "HIJO>> Mensaje enviado" << endl;

        close(pipeVuelta[1]);
    }
    waitpid(pid, NULL, 0);

    return 0;
}