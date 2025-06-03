%include "io.inc"

section .data
    vetor dd 77, 41, 6, 52, 18, 44, 27, 3, 1, 69
          dd 25, 11, 91, 39, 49, 9, 34, 4, 16, 50
    tam equ 20
    msg db "Vetor ordenado:", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp 

    ; Bubble Sort - dois loops aninhados
    mov ecx, tam

loop_fora:
    dec ecx
    mov esi, 0 ; índice interno = 0

loop_dentro:
    mov eax, [vetor + esi*4]       ; carrega vetor[esi]
    mov ebx, [vetor + esi*4 + 4]   ; carrega vetor[esi+1]

    cmp eax, ebx
    jle nao_troca ; se vetor[esi] <= vetor[esi+1], não troca
    
    ; swap
    mov [vetor + esi*4], ebx
    mov [vetor + esi*4 + 4], eax

nao_troca:
    inc esi ; prox indice
    cmp esi, ecx
    jl loop_dentro ; se esi < ecx, continua o loop_dentro
    
    cmp ecx, 1 ; verifica se ainda restam loop_fora
    jg loop_fora

    ; imprime vetor ordenado
    PRINT_STRING msg
    NEWLINE

    mov ecx, 0
imprime:
    mov eax, [vetor + ecx*4]
    PRINT_DEC 4, eax
    NEWLINE
    inc ecx
    cmp ecx, tam
    jl imprime

    xor eax, eax
    ret
