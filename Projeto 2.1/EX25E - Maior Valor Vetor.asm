%include "io.inc"

section .data
    vetor dd 77, 41, 6, 52, 18, 44, 27, 3, 1, 69
          dd 25, 11, 91, 39, 49, 9, 34, 4, 16, 50
    tam dd 20
    msg db "Maior elemento: ", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp 

    mov ecx, 0              ; indice em 0
    mov eax, [vetor]        ; inicializa eax com o primeiro valor do vetor

maior_loop:
    inc ecx
    cmp ecx, [tam]
    jge fim                 ; se ecx >= tamanho, fim do loop

    ; carrega vetor[ecx] em ebx
    mov esi, ecx
    mov ebx, [vetor + esi*4]

    ; compara valor atual com eax 
    cmp ebx, eax
    jle continuar           ; se n for maior, continua

    ; se for maior, atualiza eax
    mov eax, ebx

continuar:
    jmp maior_loop

fim:
    PRINT_STRING msg
    PRINT_DEC 4, eax
    NEWLINE

    xor eax, eax
    ret
