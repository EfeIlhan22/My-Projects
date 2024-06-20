org 100h      


;  0x49265CF77AEF9045
mov ax, 0x4926
mov [0x06556], ax
mov ax, 0x5CF7
mov [0x06554], ax
mov ax, 0x7AEF
mov [0x06552], ax
mov ax, 0x9045
mov [0x06550], ax

;  0xD64EAAF89A8E0236

mov ax, 0xD64E
mov [0x0655E], ax
mov ax, 0xAAF8
mov [0x0655C], ax
mov ax, 0x9A8E
mov [0x0655A], ax
mov ax, 0x0236
mov [0x06558], ax

mov bx, 06550h ; D64EAAF89A8E0236 's address
mov si, 06558h ; 49265CF77AEF9045 's address 

mov cx, 4
outer_loop:   ;Used for traversing throught each cycle
    
    mov ax, [bx] ; Load a segment of the first number
    
    push cx
    push si
    push di
    ;Save outer loop counter and inner loop counter 
    
    mov cx, 4
    inner_loop:
        mov ax, [bx] ;b row                                                              
        mov dx, [si] ;Traverse A row
        ;ax * dx
        mul dx ; dx holds the upper 16 bits ax holds lower 16 bits        
        add [0x02000+di], ax
        adc [0x02000+di+2], dx
        CLC

        add si, 2 ; move to the next segment in the second number
        add di, 2 ; adjust result storage position
        loop inner_loop
   
   
    add bx, 2 ; bx + 2 to traverse
    ; get SI and DI from stack  
    
    pop di
    pop si 
    pop cx
    add di, 2 ; di + 2 to 

    
    loop outer_loop

ret