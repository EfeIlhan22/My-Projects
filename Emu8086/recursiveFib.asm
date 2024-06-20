origin 100h

MOV CX 5

Call Fibonacci



ret



Fibonacci PROC
    
CMP CX,1
JZ CX return1

CMP CX,0
JZ return0


push cx
sub cx,1
call Fibonacci
pop cx
mov bx,ax
push bx

sub cx,2
call Fibonacci
pop bx
add bx,ax
mov ax,bx


RET

return1:
MOV AX,1
RET
return0:
MOV AX,0
RET

Fibonacci ENDP