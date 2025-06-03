%include "io.inc"

section .data
    num1 dd 0
    num2 dd 100
    msg db "i equals ", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    mov ecx, [num1] ;atribui valor inicial a ecx
    mov ebx, [num2] ;atribui valor final a ebx
    
    forloop: ;inicia loop
    cmp ecx,ebx ;compara valores em ecx e ebx
    jae exit ;se ecx = ebx jump para saída
    
    PRINT_STRING msg ;imprime msg
    PRINT_DEC 8, ecx ;imprime valor armazenado em ecx
    NEWLINE ;pula linha
    
    inc ecx ;"i++" valor de ecx
    jmp forloop ;jump p começo do loop
 exit:
    xor eax, eax
    ret