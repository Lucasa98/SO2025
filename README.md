# Sistemas Operativos 2025

Para compilar y ejecutar helloworld (assembler)

- Instalar `nasm`
- Instalar `ld` (si no lo tenes)
- Ensamblar con nasm `nasm -f elf helloworld.asm`
- Enlazar con ld `ld -m elf_i386 -s -o helloworld helloworld.o`
- Ejecutar `./helloworld`
