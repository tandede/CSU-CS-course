 .MODEL SMALL

.STACK 100H
.DATA
      STRING DB 'Please input a munber:$'
       S  DW 0
      SUR DW 0
.CODE
START: 
      MOV AX,@DATA
      MOV DS,AX
      
      MOV DX,OFFSET STRING        ;输出字符串STRING 
      MOV AH,09H
      INT 21H
      
      MOV DX,0
S1:   MOV AH,01H                  ;输入数字 
      INT 21H
      CMP AL,0DH
      JNZ S4
      MOV SUR,DX                  ;存入SUR 
      
      CALL S5
      
      MOV AX,SUR    
      XOR DX,DX
      MOV BX,10                    ;转换为十进制                         
S2:   DIV BX
      ADD DL,30H
      PUSH DX
      XOR DX,DX
      INC S
      CMP AX,0
      JNZ S2      
          
      MOV CX,S                    ;输出十进制的数字 
S3:   POP DX
      MOV AH,02H
      INT 21H      
      LOOP S3     
      JMP QUIET
            
S4:   MOV BH,0                    ;由字符转换为数字 
      MOV BL,AL            
      MOV AX,10
      MUL DX
      MOV DX,AX
      SUB BX,30H
      ADD DX,BX
      JMP S1 
      
S5:   MOV AH,02H                  ;输出回车换行 
      MOV DL,0DH
      INT 21H
      
      MOV AH,02H
      MOV DL,0AH
      INT 21H       
      RET

QUIET:MOV AX,4C00H
      INT 21H
      END START
