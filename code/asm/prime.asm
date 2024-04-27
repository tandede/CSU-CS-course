assume cs:code, ss:stack
zero segment
	db 0
zero ends
 
value segment ;存当前要检查是否为质数的值
	dw 3, 0
value ends
 
stack segment ;栈
	dw 40H dup(0)
stack ends
 
code segment
main:
	call init ;初始化栈
	
	mov dl, '2' ;先输出 2 和空格
    mov ah, 2
    int 21h 
	mov dl, ' '
    mov ah, 2
    int 21h 
 
	mov cx, 1000  ;二重循环来枚举 3~1e7 的值
main_s1:
	push cx
	mov cx, 10000
	main_s2:
		call check ;检查当前枚举到的 value 是否为质数
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
 
init: ;初始化栈
	mov ax, stack
	mov ss, ax
	mov sp, 40H
	ret
 
get_next: ;计算下一项
	push dx
	push si
	push ax
	push bx
	push cx
	push es
	push ds
 
	mov ax, value
	mov es, ax
	mov ax, es:[0] ;ax 为低位
	mov bx, es:[2] ;bx 为高位
	add ax, 1
 
	cmp ax, 10000
	jb get_next_done
 
	mov ax, 0 ;低位超过 10000 则进位
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
 
	mov cx, 9999 ;确定试除的上界
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
	check_s2: ;使用当前 cx 的值对 value 进行试除，减法模拟求余运算
		cmp ax, dx
		ja check_minus
		jb check_s3
 
		cmp bx, 0
		je check_is_not_prime ;恰好整除则非质数
		check_s3:
			cmp bx, 1 ;向高位借位，借不到则无法整除，检查下一个 cx
			jb check_s4
			sub bx, 1
			add ax, 10000
			check_minus:
				sub ax, dx ;做减法模拟求余运算
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
 
 
 
 
show: ;输出字符串
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
	mov bx, es:[2] ;先输出高位
    
	mov  cx, 1000
    call dout  
    mov  cx, 100
    call dout    
    mov  cx, 10
    call dout
    mov  cx, 1
    call dout
 
	mov bx, es:[0] ;再输出低位
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
    int 21h          ;输出一个空格
 
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
 
    mov  dx,0     ;dx清0,除cx时，被除数为dx,ax
    mov  ax,bx    ;将bx值（第一次为输入的数，随后为余数）赋值给ax
    div  cx       ;(dx,ax)，实际为ax（dx==0）除以cx（cx值在调用程序前设置，作为参数传递进来）
    xchg ax,dx    ;ax与dx交换内容。交换后：ax中为余数，dx中为商
    mov  bx,ax    ;将ax值（余数）赋予bx（进入下一轮运算） 
                  ;如果用户前面输入65535，那么在第一轮除以10000后，dx中值为6，bx中值为5535
    cmp  dl,0     
    jne  outanum  ;如果dx中值不为0，则直接输出相应的数值
    
	mov ax, zero
	mov ds, ax
	mov ax, 0
	cmp ds:[0], ax   ;如果dx中值为0,那么判断是前面无意义的0，还是中间有意义的0。
                  ;如305，那么如果不进行次判断将输入00305。通过此位可以不输出前面两个0，
                  ;但是输出中间0。
    je   con      ;如果是前面无意义的0 ，则不输出
 outanum:
    mov ax, 1
    mov ds:[0], ax ;如果输出了一个大于0的数字，则置标志位为1，使得其后所有0都会被输出
	
	add  dl, 30h   ;dl中数值加上30h，变成对应的ASCII码。
    mov  ah, 2
    int  21h      ;输出该数字
con:
	pop es
	pop ax
	pop si
	pop dx
	ret           
 
code ends
end