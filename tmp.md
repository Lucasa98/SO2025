# Comunicación y Sincronización de Procesos

Los procesos que se ejecutados concurrentemente de forma **independiente** no afectan y no son afectados por otros del mismo sistema, como tampoco comparte datos. Al contrario, los procesos cooperativos pueden afectar como verse afectados por otros procesos, además de compartir datos.

## Comunicación

Los procesos muchas veces necesitan cooperar entre sí para:
- Compartir información: brindar un entorno que permita acceder de forma concurrente a cierta información.
- Acelerar cálculos: dividr subtareas para ejecutarlas de forma paralela.
- Modularidad: dividir funciones.
- Conveniencia: trabajar en muchas tareas al mismo tiempo (editar, imprimir, compilar, etc.).

### Mecanismos de comunicación IPC

Acá encontramos la **memoria compartida** (variables cerrojo, tuberías, semáforos, etc.) y el **paso de mensajes**
