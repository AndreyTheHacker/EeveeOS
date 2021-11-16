%define KDATA_SEGMENT 0x10
%define CDATA_SEGMENT 0x08

[GLOBAL gdt_flush]
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, KDATA_SEGMENT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp CDATA_SEGMENT:flush 
flush:
    ret
