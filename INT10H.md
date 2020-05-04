## INT 10h 显示服务 Video Service
### AH=00H 设置显示器模式
### AH=01H 设置光标形状
CH=行扫描开始、CL=行扫描结束;如果设置CH的第5位，通常认为是隐藏光标
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
```assembly
MOV AH=05H
MOV AL=00H;页码
```
### AH=06H 向上滚屏
```assembly
MOV AL,06H
MOV AL,00H  ;滚动行数，AL=00H 清除
MOV BH,07H  ;空白区域的默认属性
MOV CX,0000H;左上角坐标(y,x)(0,0)
MOV DX,184FH;左下角坐标(y,x)(24,79)
INT 10H
```
### AH=07H 向下滚屏
### AH=08H 读取光标处的字符及其属性
```assembly
MOV AH,08H
MOV BH,00H;页码
INT 10H
;AH颜色
;AL字符
```
### AH=09H 在光标处按指定属性显示字符
```assembly
MOV AH,09H
MOV AL,'a';字符
MOV BH,00H;显示页码
MOV BL,07H;属性
MOV CX,01H;显示个数
INT 10H
```
### AH=0AH 在当前光标处显示字符
```assembly
MOV AH,09H
MOV AL,'a';字符
MOV BH,00H;显示页码
MOV CX,01H;显示个数
INT 10H
```
### AH=0BH 设置调色板、背景色或边框
### AH=0CH 写图形像素
### AH=0DH 读图形像素
### AH=0EH 在Teletype模式下显示字符
### AH=0FH 读取显示器模式
```assembly
MOV AH,0FH
INT 10H
;AH=屏幕字符的列数
;AL=显示模式
;BH=页码
```
### AH=10H 颜色中断
### AH=11H 字体中断
### AH=12H 显示器的配置中断
### AH=13H 在Teletype模式下显示字符串
AL=显示输出方式
AL=00H 字符串中只含显示字符，光标位置不变
AL=01H 字符串中只含显示字符，光标位置改变
AL=02H 字符串中含显示字符和属性，光标位置不变
AL=03H 字符串中含显示字符和属性，光标位置改变
```assembly
MOV AX,CS
MOV ES,AX
MOV BP,msg
MOV AH,13H
MOV AL,01H
MOV BH,00H;页码
MOV BL,07H;属性
MOV CX,0BH;显示字符长度
MOV DX,0000H
INT 10H
msg: 'hello world'
```
