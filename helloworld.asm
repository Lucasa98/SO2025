section .data
	msg db "hello world!", 0xa, 0x0d
	largo equ $-msg

section .text

global inicio
inicio:
	mov eax,4
	mov ebx,1
	mov ecx,msg
	mov edx,largo
	int 80h

	mov eax,1
	xor ebx,ebx
	int 0x80
