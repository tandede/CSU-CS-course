DATAS SEGMENT
    f1 dw 0  ;f��first����һ������
    f2 dw 0
    f3 dw 0
    f4 dw 0
    s1 dw 0  ;s��second���ڶ�������
    s2 dw 0
    s3 dw 0
    s4 dw 0
    control dw 2;��Ϊ��50����11λ����������3λΪһ�飬��11λ���ָ�������Ϊ4��3λ  
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
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
    mov control,ax ;���Ʊ�����һ
    mov ax,f1
    mov bx,s1
    mov f1,bx  ;f1��ǰ��һ��
    add ax,bx
    mov s1,ax  ;s1��ǰ��һ�����ߺ�s1Ϊ���εĽ����ҲΪ�´εĲ�����2
   
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
    ;���˼ӷ���ϣ�Ҫ���н�λ�Ȳ���
    
    
    
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

output proc;�������ax����Ҫ�������
    mov bl,0
    mov cl,10
L3: div cl
    push ax;��ջ
    add bl,1;��������һ
    mov ah,0
    cmp ax,0;��������Ϊ0ʱ����ѭ��
    jne L3
hui:
    cmp bl,3
    je  L4
    mov ax,0
    push ax
    add bl,1
    jmp hui
L4: pop dx;��ջ
    sub bl,1;��������һ
    mov dl,dh
    add dl,48
    mov ah,2
    int 21h
    cmp bl,0;������������ʱ����ѭ��
    jne L4
ret
output endp 
CODES ENDS
    END START



