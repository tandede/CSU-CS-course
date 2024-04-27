.model large
assume ds:data, cs:code
 
data segment
buf db ?               
db ?
db 10 dup(?)

array dw 500 dup(?)                                
number dw 1 dup(?)
symbol dw 1 dup(?)                                      
data ends
 
code segment
	
main:	
	mov [number], 0
	
input:
	lea dx, buf                                  ; �����ַ�������buf��
	mov ah, 0ah
	int 21h
	
	mov dl, 13   ; ��ӡ����
	mov ah, 02h
	int 21h
	mov dl, 0ah
	mov ah, 02h
	int 21h
	
	
	mov bl, [buf + 2]
	cmp bl, 13
	jz input_end
 
	call read                                ; ����ReadUInt���ú�����bufת������������ŵ�ax��
	
	mov si, [number]
	shl si, 1                                    ; si = si * 2��һ������ռ2���ֽڣ���˳���2
	mov [array + si], ax                           ; ����ȡ�����ִ�ŵ�������
	shr si, 1
	inc si
	mov [number], si
	jmp input
	
input_end:
	push sp
	mov si, 0                                    ; ð������i=si,j=di
	mov di, 0
L1:
	cmp si, [number]
	jge L1_END
	mov di, si                                   ; j = i + 1
	inc di
	L2:
		cmp di, [number]
		jge L2_END
		shl si, 1
		shl di, 1
		mov ax, [array+si]
		mov bx, [array+di]
		shr si, 1
		shr di, 1
		cmp ax, bx
		jg exchange
		inc di
		jmp L2
	exchange:
		shl si, 1
		shl di, 1
		mov [array+di], ax
		mov [array+si], bx
		shr si, 1
		shr di, 1
		inc di
		jmp L2
	L2_END:
		inc si
		jmp L1
	L1_END:
		
		mov bx, 0
	L3:
		cmp bx, [number]
		jge L3_END
		mov si, bx
		shl si, 1
		mov ax, [array+si]
		call print_int
		
		push bx
		push si
		
		mov dl, 13   ; ��ӡ����
		mov ah, 02h
		int 21h
		mov dl, 0ah
		mov ah, 02h
		int 21h
		
		pop si
		pop bx
		
		inc bx
		jmp L3
		
L3_END:
	pop sp
	mov ah, 4ch
	int 21h
	
read proc
	pushf
	push bx
	push cx
	push dx
	push si
	push di
 
	mov [symbol], 0
	mov cx, 0
	mov cl, [buf + 1]  ; ��ȡ�ַ�������
	lea si, [buf + 2]  ; ��ȡ�ַ�����ַ
	mov ax, 0
	mov di, 0
 
	add si, di
	mov bl, [si]
 
	cmp bl, '-'
	jne read_s1
	mov [symbol], 1
	sub cl, 1
	inc di
read_s1:
	lea si, [buf + 2]
	add si, di     ; ��ȡ��ǰ������ַ���ַ
	inc di
	mov bl, [si]   ; ��ȡ�ַ�
	sub bl, 48     ; �ַ���ȥ'0'
	mov dl, 10
	mul dl         ; ����10
	mov bh, 0
	add ax, bx     ; ��������
	loop read_s1
 
mov bx, [symbol]
cmp bx, 1
jne read_s1_end
neg ax
read_s1_end:
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	popf
	ret
read endp
 
print_int proc
	pushf            ; save eflags and register
	push bx
	push cx
	push dx
 
	mov [symbol], 0
	cmp ax, 0
	jz print_zero
	js print_minus
	jmp skip_print_zero_and_minus
print_zero:
	mov dl, '0'
	mov ah, 02h
	int 21h
	jmp print_int_end2
print_minus:
	neg ax
	mov [symbol], 1
 
skip_print_zero_and_minus:
	mov cx, 0
	mov bx, 10
print_int_loop1:
	mov dx, 0
	div bx
	add dl, 30h
	push dx
	inc cx
	cmp ax, 0
	jne print_int_loop1
 
	cmp [symbol], 1
	jnz print_int_loop2
	mov dl, '-'   
	mov ah, 02h
	int 21h
print_int_loop2:
	pop dx
	mov ah, 02h
	int 21h
	loop print_int_loop2
	
print_int_end2:
	mov dl, 13   ; ��ӡ����
	mov ah, 02h
	int 21h
	
	pop dx
	pop cx
	pop bx
    popf
	ret
print_int endp
code ends
end main    