.global spinlock_lock
.global spinlock_unlock

spinlock_lock:
    mov 4(%esp), %ebx
    mov 4(%ebx), %eax
sl_loop:
    lock bts %eax, 0
    pause
    jc sl_loop
    ret

spinlock_unlock:
    mov 4(%esp), %ebx
    mov 4(%ebx), %eax
    mov $0, %eax
    ret
