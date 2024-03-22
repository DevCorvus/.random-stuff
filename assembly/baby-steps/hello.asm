format ELF64 executable 3

segment readable executable
entry main

include 'io.asm'

main:
    lea rdi, [msg]  ; address of msg into rdi
    call print      ; print msg
    lea rdi, [name] ; address of name into rdi
    call print      ; print name
    xor rdi, rdi    ; exit code 0
    mov rax, 60     ; sys_exit
    syscall

segment readable writable

msg db 'Hello world', 10, 0 ; Hello world message + \n + \0 (13 bytes)
name db 'Luis Portillo', 10, 0
