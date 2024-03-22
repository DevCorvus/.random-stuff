strlen:
    push    rdi         ; push to stack
    push    rcx         ; push to stack (this is our counter)
    mov     rcx, -1     ; set rcx to -1
    xor     al, al      ; set al to 0
    cld                 ; clear direction flags
    repne   scasb       ; repeat if not equal to al (0)
    neg     rcx         ; negate rcx (now it's a positive number)
    dec     rcx         ; exclude null terminator
    mov     rax, rcx    ; move value from rcx to rax
    pop     rcx         ; restore rcx
    pop     rdi         ; restore rdi
    ret                 ; return

print:
    call    strlen      ; calculate msg length
    mov     rdx, rax    ; move rax to rdx
    mov     rsi, rdi    ; move rdi to rsi
    mov     rdi, 1      ; stdout
    mov     rax, 1      ; sys_write
    syscall
    ret

read:
    mov     rdx, rdi    ; buffer to read to
    mov     rdi, 0      ; stdin
    mov     rax, 0      ; sys_read
    syscall
    ret
