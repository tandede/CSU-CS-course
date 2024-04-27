.model small
.stack 100h

.data
  message db 'Prime Numbers:$'
  newline db 10, 13, '$'
  buffer db 6
  buflen dw 0

.code
  main proc
    mov ax, @data
    mov ds, ax

    ; 初始化计数器
    mov bx, 2

    ; 输出提示信息
    mov ah, 9
    lea dx, message
    int 21h

  find_prime:
    ; 初始化判断数和除数
    mov cx, 2
    mov dx, 0

  division_check:
    ; 检查是否整除
    xor ax, ax
    mov ax, bx
    div cx
    test dx, dx
    jnz not_prime

    ; 判断数自增
    inc cx

    ; 检查是否是素数
    cmp cx, bx
    jle division_check

  prime_found:
    ; 将素数存入缓冲区
    push bx
    mov ah, 2
    mov dl, buffer[0]
    int 21h
    mov dl, 32 ; 空格
    int 21h

    ; 输出换行符
    mov ah, 9
    lea dx, newline
    int 21h

    ; 清空缓冲区
    mov byte ptr buffer[0], 0
    mov word ptr buflen, 0

  prime_increment:
    ; 计数自增
    inc bx

    ; 检查是否超过10000000
    cmp bx, 10000000
    jle find_prime

  exit_program:
    ; 退出程序
    mov ax, 4C00h
    int 21h

  not_prime:
    ; 继续寻找下一个数
    inc bx
    jmp find_prime

  main endp

end main