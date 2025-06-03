%include "io.inc"

section .data
    bissexto_msg db "O ano é bissexto.", 0
    nao_bissexto_msg db "O ano nao é bissexto.", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp ; for correct debugging
    
    GET_DEC 4, eax ; le input e armazena em eax

    mov edx, 0 ; limpa edx para usar na divisao
    mov ebx, 4 ; insere 4 em ebx para divisao
    div ebx ; divide eax por ebx e o resto fica em edx
    cmp edx, 0 ; compara o resto em edx com 0
    jne nao_bissexto ; falhou comparação jump para caso não bissexto
    
    GET_DEC 4, ecx ; le input e armazena em ecx pois valor de eax foi modificado
    mov eax, ecx ; insere valor de ecx em eax

    ; eh divisivel por 4, precisa checar se é por 100
    mov edx, 0 ; limpa edx para usar na divisao
    mov ebx, 100 ; insere 100 em ebx para divisao
    div ebx ; divide eax por ebx e o resto fica em edx
    cmp edx, 0 ; compara o resto em edx com 0
    jne eh_bissexto ; se falhou então não é divisivel por 100 mas por 4, então eh bissexto

    ; eh divisivel por 100, precisa checar se é por 400
    mov eax, ecx    ; insere valor original de ecx em eax
    mov edx, 0 ; limpa edx para usar na divisao
    mov ebx, 400 ; insere 400 em ebx para divisao
    div ebx ; divide eax por ebx e o resto fica em edx
    cmp edx, 0 ; compara o resto em edx com 0
    jne nao_bissexto ; se falhou então é divisivel por 100 mas nao por 400, entao nao eh bissexto

eh_bissexto:
    PRINT_STRING bissexto_msg ; imprime mensagem
    jmp fim ; jump pro fim

nao_bissexto:
    PRINT_STRING nao_bissexto_msg ; imprime mensagem

fim:
    NEWLINE 
    xor eax, eax
    ret