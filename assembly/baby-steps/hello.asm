format ELF64 executable 3

segment readable executable
entry main

include 'io.asm'

main:
    lea     rdi, [msg]      ; address of msg into rdi
    call    print           ; print msg
    lea     rdi, [prompt]   ; address of prompt into rdi
    call    print           ; print prompt
    lea     rsi, [buf]      ; buffer address into rsi
    mov     rdi, 64         ; buffer size
    call    read            ; read user input
    mov     rdi, rsi        ; move string read to rdi
    call    print           ; print buffer (user input)
    xor     rdi, rdi        ; exit code 0
    mov     rax, 60         ; sys_exit
    syscall

segment readable writable

msg     db 'Hello world', 10, 0 ; Hello world message + \n + \0 (13 bytes)
prompt  db 'Enter your name: ', 0
buf     rb 64
