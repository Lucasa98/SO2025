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
    long int msgtype = 0;
    int msgid = msgget(MSGKEY, 0644);

    cout << "Recibiendo mensajes..." << endl;
    while(1) {
        // Recibir mensajes
        msgrcv(msgid, (void*)&msg, SIZE, msgtype, 0);

        cout << "[" << msg.type << "] " << msg.text << endl;

        // terminar si msg  recibido es "fin"
        if(strncmp(msg.text, "chau", 3) == 0)
            break;
    }

    return 0;
}