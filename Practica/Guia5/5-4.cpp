#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

using namespace std;

#define SIZE 256

int main() {
    int piperw[2];
    char txt[SIZE];
    
    pipe(piperw);
    
    int pid = fork();
    if(pid != 0) {  // Padre
        // cerrar lectura
        close(piperw[0]);

        // Mensaje 1
        // escribir mensaje
        strcpy(txt, "un mensaje para mi hijo\n");

        // Enviar mensaje escribiendo en el pipe
        write(piperw[1], txt, strlen(txt));

        // Mensaje 2
        strcpy(txt, "otro mensaje, perdon loco re pesado");
        write(piperw[1], txt, strlen(txt)+1);

        cout << "PADRE>> Mensaje enviado" << endl;;
        // cerrar extremo de escritura
        close(piperw[1]);
    } else {        // Hijo
        // cerrar extremo de escritura
        close(piperw[1]);

        sleep(1);
        while(read(piperw[0], txt, sizeof(txt)) > 0) {
            cout << "HIJO>> Recibido mensaje del padre: " << txt << endl;
        }

        // cerrar lectura
        close(piperw[0]);
    }
    waitpid(pid, NULL, 0);

    return 0;
}