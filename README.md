# 简易 64 位操作系统 牛马OS

这是一个从零开始构建的、用于学习目的的简易 64 位操作系统。

## 功能特性

*   **64 位长模式**：通过引导加载程序设置，成功进入 64 位长模式。
*   **基础驱动程序**：
    *   **VGA**：支持屏幕文本输出。
    *   **ATA (PIO)**：支持磁盘的读写操作。
    *   **键盘**：支持轮询模式下的键盘输入。
    *   **串口**：支持 COM1 串口通信。
*   **中断处理**：
    *   设置了中断描述符表 (IDT)。
    *   实现了对 CPU 异常（如除零错误）和硬件中断（定时器）的处理。
*   **内存管理**：
    *   实现了一个简单的基于位图的物理内存管理器 (PMM)。
*   **文件系统**：
    *   实现了一个简单的扁平化文件系统，支持文件列表和文件读取。
*   **自动化测试**：
    *   通过 `make test` 命令，使用 QEMU 在无图形界面模式下运行，并通过串口输出验证内核的正确性。

## 目录结构

```
.
├── src
│   ├── boot
│   │   └── boot.asm      # 16 位引导加载程序
│   └── kernel
│       ├── arch
│       │   └── x86_64
│       │       ├── entry.asm       # 64 位内核入口点
│       │       ├── exceptions.c    # CPU 异常处理
│       │       ├── idt.c           # 中断描述符表
│       │       ├── interrupts.asm  # 中断服务程序
│       │       ├── pic.c           # 8259 PIC 控制器
│       │       └── timer.c         # PIT 定时器
│       ├── drivers
│       │   ├── ata.c           # ATA 磁盘驱动
│       │   ├── keyboard.c      # 键盘驱动
│       │   ├── port_io.c       # I/O 端口操作
│       │   ├── print.asm       # VGA 屏幕输出
│       │   └── serial.c        # 串口驱动
│       ├── fs
│       │   └── simple_fs.c     # 简单文件系统
│       ├── include
│       │   ├── *.h             # 所有内核头文件
│       └── mm
│           └── pmm.c           # 物理内存管理
├── tools
│   └── create_fs.c       # 用于创建文件系统镜像的工具
└── Makefile              # 顶层 Makefile
```

## 编译和运行

### 环境要求

*   **Linux (CentOS/Ubuntu)**
*   `nasm`
*   `gcc`
*   `make`
*   `qemu-system-x86_64`

### 在 CentOS 上安装依赖

```bash
sudo yum install -y nasm gcc make qemu-system-x86
```

### 在 Ubuntu 上安装依赖

```bash
sudo apt-get update
sudo apt-get install -y nasm gcc make qemu-system-x86
```

### 编译

在项目根目录下运行 `make` 命令：

```bash
make
```

### 运行

运行以下命令以启动 QEMU：

```bash
make test
```

QEMU 将在无图形界面的模式下运行，并将内核的输出重定向到当前终端。
