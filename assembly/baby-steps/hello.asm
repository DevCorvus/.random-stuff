format ELF64 executable 3

segment readable executable
entry main

main:
    lea rdi, [msg]  ; address of msg into rdi
    call print      ; print msg
    lea rdi, [name] ; address of name into rdi
    call print      ; print name
    xor rdi, rdi    ; exit code 0
    mov rax, 60     ; sys_exit
    syscall

strlen:
    push rdi        ; push to stack
    push rcx        ; push to stack (this is our counter)
    mov rcx, -1     ; set rcx to -1
    xor al, al      ; set al to 0
    cld             ; clear direction flags
    repne scasb     ; repeat if not equal to al (0)
    neg rcx         ; negate rcx (now it's a positive number)
    dec rcx         ; exclude null terminator
    mov rax, rcx    ; move value from rcx to rax
    pop rcx         ; restore rcx
    pop rdi         ; restore rdi
    ret             ; return

print:
    call strlen     ; calculate msg length
    mov rdx, rax    ; move rax to rdx
    mov rsi, rdi    ; move rdi to rsi
    mov rdi, 1      ; stdout
    mov rax, 1      ; sys_write
    syscall
    ret

segment readable writable

msg db 'Hello world', 10, 0 ; Hello world message + \n + \0 (13 bytes)
name db 'Luis Portillo', 10, 0
