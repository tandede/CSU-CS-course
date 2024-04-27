;题目十四 编密码要求：按照以下规律编密码：
;字母 A 变为 E，a 变为 e，即变成其他的第一 4 个字母，
;W 变 A，X 变 B，Y 变 C，Z 变为 D，非字母不变。如“CHINA”变为“GLMRE！”
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
