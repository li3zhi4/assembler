# My OS

This is a project to build a simple 64-bit operating system.

## Build Environment Setup (CentOS)

To build this project, you will need the following tools:

```bash
sudo yum install -y nasm gcc make bochs
```

## Building the 64-bit OS

To build the OS, run the following commands from the root of the project:

```bash
cd 01_START
make
cd ../02_KERNEL_64
make
```

This will create a `boot.img` file in the `02_KERNEL_64` directory.

## Running the 64-bit OS in Bochs

To run the OS, you will need to create a `bochsrc.bxrc` file in the root of the project with the following content:

```
megs: 32
romimage: file=$BXSHARE/BIOS-bochs-latest, options=fastboot
vgaromimage: file=$BXSHARE/VGABIOS-lgpl-latest
floppya: 1_44=02_KERNEL_64/boot.img, status=inserted, write_protected=0
boot: floppy
log: bochsout.txt
cpu: count=1, ips=15000000, model=broadwell_ult, reset_on_triple_fault=1, cpuid_limit_winnt=0
```

Make sure to replace `$BXSHARE` with the actual path to your Bochs share directory.

Then, you can run Bochs from the root of the project:

```bash
bochs -f bochsrc.bxrc
```
log: bochsout.txt
```
