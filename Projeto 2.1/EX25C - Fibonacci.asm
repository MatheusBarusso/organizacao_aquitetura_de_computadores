%include "io.inc"

section .data
    prompt_msg dd "Digite o numero de termos (N) da sequencia de Fibonacci: ", 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp ; for correct debugging
    
    GET_DEC 4, ecx ; le input e armazena em ecx

    cmp ecx, 0 ; compara ecx com 0
    je fim ; se o valor em ecx = 0 então jump pro fim pois não precisa rodar

    PRINT_STRING "0" ; imprime 0 pois eh o valor inicial em qualquer cas oque ecx != 0
    cmp ecx, 1 ; compara ecx com 1
    je fim ; se o valor em ecx = 1 então jump pro fim pois 0 ja foi impresso 
    
    dec ecx ; decrementa o valor de ecx pois o primeiro valor ja foi impresso na linha 17
    
    mov eax, 0 ; armazena termo anterior
    mov ebx, 1 ; armazena termo atual

; loop que cria e imprime sequencia
loop_start:
    NEWLINE
    
    PRINT_DEC 4, ebx ; imprime termo atual, começando sempre em 1 para segunda posicao

    ; Calcula o próximo termo: proximo = atual + anterior
    mov edx, ebx ; salva termo atual em edx
    add edx, eax ; soma eax + ebx e armazena em edx

    ; Atualiza os valores para a próxima iteração
    mov eax, ebx ; termo de ebx (atual) agora vira termo anterior (eax)
    mov ebx, edx ; termo calculado que estava em edx agora vira o termo atual (ebx)
    
    dec ecx ; decremente ecx
    jnz loop_start ; reinicia loop se ainda não imprimiu todos termos

fim:
    NEWLINE 
    xor eax, eax
    ret