#include <iostream>
#include <string.h>
#include <sys/msg.h>

using namespace std;

#define SIZE 256
#define MSGKEY 0x12345

struct Msg {
    long type;
    char text[SIZE];
};

int main() {
    Msg msg;
    string s;
    int msgid = msgget(MSGKEY, 0777 | IPC_CREAT);

    while(1) {
        // Leer cadena
        cout << "Escriba un mensaje: ";
        getline(cin, s);

        // Configurar y cargar mensaje
        msg.type = 2;
        strcpy(msg.text, s.c_str());

        // Enviar mensaje
        cout << "Enviando mensaje..." << endl;
        msgsnd(msgid, (void*)&msg, SIZE, 0);

        // terminar si msg enviado es "fin"
        if(strncmp(msg.text, "chau", 3) == 0)
            break;
    }

    return 0;
}