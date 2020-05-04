## int 10h 显示服务 Video Service 
功能入口: AH
### AH=00H 设置显示器模式
### AH=01H 设置光标形状
CH=行扫描开始、CL=行扫描结束
如果设置CH的第5位，通常认为是隐藏光标
```assembly
MOV AH=01H
MOV CX=0607H;正常光标
MOV CX=0007H;完整块光标
INT 10H
```
### AH=02H 设置光标位置
```assembly
MOV AH,02H
MOV BH,00H  ;页码
MOV DX,0000H;光标坐标(y,x)
INT 10H
```
### AH=03H 读取光标信息
```assembly
MOV AL,03H
MOV BX,0000H;页码
INT 10H
;AX=0
;CX 行扫描开始、结束
;DX 光标坐标(y,x)
```
### AH=04H 读取光笔位置
### AH=05H 设置显示页
```
MOV AH=05H
MOV AL=00H;页码
```
### AH=06H 向上滚屏
```assembly
MOV AL,06H
MOV AL,00H  ;滚动行数，0=清除
MOV BH,07H  ;空白区域的默认属性
MOV CX,0000H;左上角坐标(y,x)(0,0)
MOV DX,184FH;左下角坐标(y,x)(24,79)
INT 10H
```
### AH=07H 向下滚屏
### AH=08H 读取光标处的字符及其属性
```
MOV AH,08H
MOV BH,00H;页码
INT 10H
;AH颜色
;AL字符
```
### AH=09H 在光标处按执行属性显示字符
```
mov ah,09h
mov al,'a'
mov bh,00h
mov bl,07h
mov cx,01h
int 10h
```
### AH=0AH 在光标处显示字符
### AH=0FH 获取当前显示模式
### AH=13H
```
MOV AX,CS
MOV ES,AX
MOV BP,00H
MOV AH,13H
MOV AL,01H;写模式
MOV BH,00H
MOV BL,07H
MOV CX,13H
MOV DX,0000H
INT 10H
```