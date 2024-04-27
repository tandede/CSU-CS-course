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

    ; ��ʼ��������
    mov bx, 2

    ; �����ʾ��Ϣ
    mov ah, 9
    lea dx, message
    int 21h

  find_prime:
    ; ��ʼ���ж����ͳ���
    mov cx, 2
    mov dx, 0

  division_check:
    ; ����Ƿ�����
    xor ax, ax
    mov ax, bx
    div cx
    test dx, dx
    jnz not_prime

    ; �ж�������
    inc cx

    ; ����Ƿ�������
    cmp cx, bx
    jle division_check

  prime_found:
    ; ���������뻺����
    push bx
    mov ah, 2
    mov dl, buffer[0]
    int 21h
    mov dl, 32 ; �ո�
    int 21h

    ; ������з�
    mov ah, 9
    lea dx, newline
    int 21h

    ; ��ջ�����
    mov byte ptr buffer[0], 0
    mov word ptr buflen, 0

  prime_increment:
    ; ��������
    inc bx

    ; ����Ƿ񳬹�10000000
    cmp bx, 10000000
    jle find_prime

  exit_program:
    ; �˳�����
    mov ax, 4C00h
    int 21h

  not_prime:
    ; ����Ѱ����һ����
    inc bx
    jmp find_prime

  main endp

end main