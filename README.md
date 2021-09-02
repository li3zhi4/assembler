# 汇编语言
## 前言
包含有些小demo，仅供自己学习使用  
### BIOS中断
[INT 10H 显示服务 Video Service](https://github.com/li3zhi4/assembler/blob/master/bios/INT10H.md)  
[INT 13H 直接磁盘服务 Direct Disk Service](https://github.com/li3zhi4/assembler/blob/master/bios/INT13H.md)  
INT 14H 串行口服务 Serial Port Service  
INT 15H 杂项系统服务 Miscellaneous System Service  
[INT 16H 键盘服务 Keyboard Service](https://github.com/li3zhi4/assembler/blob/master/bios/INT16H.md)  
INT 17H 并行口服务 Parallel Port Service  
INT 1AH 时钟服务 Clock Service  
直接系统服务 Direct System Service 

### bochs
bochsrc.bxrc
BXSHARE is the path of bochs
```
megs: 32
romimage: file=$BXSHARE/BIOS-bochs-latest, options=fastboot
vgaromimage: file=$BXSHARE/VGABIOS-lgpl-latest
floppya: 1_44=boot.img, status=inserted, write_protected=0
boot: floppy
log: bochsout.txt
``` 
