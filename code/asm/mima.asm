;��Ŀʮ�� ������Ҫ�󣺰������¹��ɱ����룺
;��ĸ A ��Ϊ E��a ��Ϊ e������������ĵ�һ 4 ����ĸ��
;W �� A��X �� B��Y �� C��Z ��Ϊ D������ĸ���䡣�硰CHINA����Ϊ��GLMRE����
.MODEL SMALL
.DATA
SOURCE BYTE "1C2H5INAZchi3na8@%&*)(*&^%$#@z!"
TARGET BYTE SIZEOF SOURCE DUP(?)
.CODE
MAIN PROC FAR
      MOV AX,@DATA
      MOV DS,AX
      LEA SI,SOURCE
      LEA DI,TARGET
      MOV CX,SIZEOF SOURCE
LOOP1:MOV AH,'A'
      CMP [SI],AH
      JB LOOP3
      MOV AH,'Z'
      CMP [SI],AH
      JA LOOP2
      MOV AH,[SI]
      ADD AH,4
      MOV [SI],AH
      MOV AH,'Z'
      CMP [SI],AH
      JB LOOP3
      MOV AH,[SI]
      SUB AH,26
      MOV [SI],AH
      JMP LOOP3       
LOOP2:MOV AH,'a'
      CMP [SI],AH
      JB LOOP3
      MOV AH,'z'
      CMP [SI],AH
      JA LOOP3
      MOV AH,[SI]
      ADD AH,4
      MOV [SI],AH
      MOV AH,'z'
      CMP [SI],AH
      JB LOOP3
      MOV AH,[SI]
      SUB AH,26
      MOV [SI],AH
      JMP LOOP3
LOOP3:MOV AH,[SI]
      MOV [DI],AH
      INC DI
      INC SI
      LOOP LOOP1
      LEA SI,TARGET
      MOV CX,SIZEOF TARGET
LOOP4:MOV DX,[SI]
      MOV AH,2H
      INT 21H
      INC SI
      LOOP LOOP4
      MOV AX,4C00H
      INT 21H      
MAIN ENDP
END
