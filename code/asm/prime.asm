assume cs:code, ss:stack
zero segment
	db 0
zero ends
 
value segment ;�浱ǰҪ����Ƿ�Ϊ������ֵ
	dw 3, 0
value ends
 
stack segment ;ջ
	dw 40H dup(0)
stack ends
 
code segment
main:
	call init ;��ʼ��ջ
	
	mov dl, '2' ;����� 2 �Ϳո�
    mov ah, 2
    int 21h 
	mov dl, ' '
    mov ah, 2
    int 21h 
 
	mov cx, 1000  ;����ѭ����ö�� 3~1e7 ��ֵ
main_s1:
	push cx
	mov cx, 10000
	main_s2:
		call check ;��鵱ǰö�ٵ��� value �Ƿ�Ϊ����
		push cx
		mov cx, ax
		jcxz main_s3
		call show
	main_s3:
		pop cx
		call get_next ;value += 2
		call get_next
		sub cx, 1
		loop main_s2
	pop cx
	loop main_s1
 
	mov ax, 4c00h
	int 21h
 
init: ;��ʼ��ջ
	mov ax, stack
	mov ss, ax
	mov sp, 40H
	ret
 
get_next: ;������һ��
	push dx
	push si
	push ax
	push bx
	push cx
	push es
	push ds
 
	mov ax, value
	mov es, ax
	mov ax, es:[0] ;ax Ϊ��λ
	mov bx, es:[2] ;bx Ϊ��λ
	add ax, 1
 
	cmp ax, 10000
	jb get_next_done
 
	mov ax, 0 ;��λ���� 10000 ���λ
	add bx, 1
get_next_done:
	mov es:[0], ax
	mov es:[2], bx
 
	pop ds
	pop es
	pop cx
	pop bx
	pop ax
	pop si
	pop dx
	ret
 
check:
	;mov ax, 1
	;ret
 
	push cx
	push dx
	push si
	push bx
	push es
 
	mov ax, value
	mov es, ax
	mov ax, es:[0]
	mov bx, es:[2]
	mov dx, 2
 
	mov cx, 9999 ;ȷ���Գ����Ͻ�
	cmp bx, 1
	jae check_s1
 
	cmp ax, 3
	jbe check_is_prime
 
	mov cx, ax
	sub cx, 1
check_s1:
	mov ax, value
	mov es, ax
	mov ax, es:[0]
	mov bx, es:[2]
	check_s2: ;ʹ�õ�ǰ cx ��ֵ�� value �����Գ�������ģ����������
		cmp ax, dx
		ja check_minus
		jb check_s3
 
		cmp bx, 0
		je check_is_not_prime ;ǡ�������������
		check_s3:
			cmp bx, 1 ;���λ��λ���費�����޷������������һ�� cx
			jb check_s4
			sub bx, 1
			add ax, 10000
			check_minus:
				sub ax, dx ;������ģ����������
				jmp check_s2
	check_s4:
	sub cx, 1
	inc dx
	cmp cx, 1
	ja check_s1
check_is_prime:
	mov ax, 1
	jmp check_done
check_is_not_prime:
	mov ax, 0
check_done:
	pop es
	pop bx
	pop si
	pop dx
	pop cx
	ret
 
 
 
 
show: ;����ַ���
	push cx
	push dx
	push si
	push ax
	push bx
	push es
 
	mov ax, zero
	mov ds, ax
  	mov ax, 0
	mov ds:[0], ax
 
	mov ax, value
	mov es, ax
	mov bx, es:[2] ;�������λ
    
	mov  cx, 1000
    call dout  
    mov  cx, 100
    call dout    
    mov  cx, 10
    call dout
    mov  cx, 1
    call dout
 
	mov bx, es:[0] ;�������λ
	mov  cx, 1000
    call dout
    mov  cx, 100
    call dout
    mov  cx, 10
    call dout
    mov  cx, 1
    call dout
 
	mov dl, ' '
    mov ah, 2
    int 21h          ;���һ���ո�
 
	pop es
	pop bx
	pop ax
	pop si
	pop dx
	pop cx
	ret
 
dout:
	push dx
	push si
	push ax
	push es
 
    mov  dx,0     ;dx��0,��cxʱ��������Ϊdx,ax
    mov  ax,bx    ;��bxֵ����һ��Ϊ������������Ϊ��������ֵ��ax
    div  cx       ;(dx,ax)��ʵ��Ϊax��dx==0������cx��cxֵ�ڵ��ó���ǰ���ã���Ϊ�������ݽ�����
    xchg ax,dx    ;ax��dx�������ݡ�������ax��Ϊ������dx��Ϊ��
    mov  bx,ax    ;��axֵ������������bx��������һ�����㣩 
                  ;����û�ǰ������65535����ô�ڵ�һ�ֳ���10000��dx��ֵΪ6��bx��ֵΪ5535
    cmp  dl,0     
    jne  outanum  ;���dx��ֵ��Ϊ0����ֱ�������Ӧ����ֵ
    
	mov ax, zero
	mov ds, ax
	mov ax, 0
	cmp ds:[0], ax   ;���dx��ֵΪ0,��ô�ж���ǰ���������0�������м��������0��
                  ;��305����ô��������д��жϽ�����00305��ͨ����λ���Բ����ǰ������0��
                  ;��������м�0��
    je   con      ;�����ǰ���������0 �������
 outanum:
    mov ax, 1
    mov ds:[0], ax ;��������һ������0�����֣����ñ�־λΪ1��ʹ���������0���ᱻ���
	
	add  dl, 30h   ;dl����ֵ����30h����ɶ�Ӧ��ASCII�롣
    mov  ah, 2
    int  21h      ;���������
con:
	pop es
	pop ax
	pop si
	pop dx
	ret           
 
code ends
end