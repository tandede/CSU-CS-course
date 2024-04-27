DATAS SEGMENT
    f1 dw 0  ;f即first即第一操作数
    f2 dw 0
    f3 dw 0
    f4 dw 0
    s1 dw 0  ;s即second即第二操作数
    s2 dw 0
    s3 dw 0
    s4 dw 0
    control dw 2;因为第50项有11位，所以我以3位为一组，把11位给分隔开，变为4个3位  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    mov ax,1
    mov f1,ax   
    mov s1,ax   
    mov ax,f1
    call output
    mov ah,02
    mov dl,10
    int 21h 
    mov ax,s1
    call output
    mov ah,02
    mov dl,10
    int 21h 
xunhuan:
    mov ax,control
    inc ax
    mov control,ax ;控制变量加一
    mov ax,f1
    mov bx,s1
    mov f1,bx  ;f1往前走一步
    add ax,bx
    mov s1,ax  ;s1往前走一步，走后s1为本次的结果，也为下次的操作数2
   
    mov ax,f2
    mov bx,s2
    mov f2,bx  
    add ax,bx
    mov s2,ax
    
    mov ax,f3
    mov bx,s3
    mov f3,bx  
    add ax,bx
    mov s3,ax
   
    mov ax,f4
    mov bx,s4
    mov f4,bx  
    add ax,bx
    mov s4,ax
    ;至此加法完毕，要进行进位等操作
    
    
    
    mov ax,s1
    cmp ax,999
    jb notj2    
    sub ax,1000
    mov bx,s2
    inc bx
    mov s2,bx
notj2:   
    mov s1,ax
    mov ax,s2
    cmp ax,1000
    jb notj3
    sub ax,1000
    mov bx,s3
    inc bx
    mov s3,bx
notj3:
    mov s2,ax
    mov ax,s3
    cmp ax,999
    jb notj4
    sub ax,1000
    mov bx,s4
    inc bx
    mov s4,bx
notj4:
    mov s3,ax
    mov ax,s4
    call output
    mov ax,s3
    call output
    mov ax,s2
    call output
    mov ax,s1
    call output
    mov ah,02
    mov dl,10
    int 21h
    mov ax,control
    cmp ax,50
    jnz xunhuan
    MOV AH,4ch
    INT 21H

output proc;输出函数ax里存放要输出的数
    mov bl,0
    mov cl,10
L3: div cl
    push ax;入栈
    add bl,1;计数器加一
    mov ah,0
    cmp ax,0;当被除数为0时结束循环
    jne L3
hui:
    cmp bl,3
    je  L4
    mov ax,0
    push ax
    add bl,1
    jmp hui
L4: pop dx;出栈
    sub bl,1;计数器减一
    mov dl,dh
    add dl,48
    mov ah,2
    int 21h
    cmp bl,0;当计数器清零时结束循环
    jne L4
ret
output endp 
CODES ENDS
    END START



