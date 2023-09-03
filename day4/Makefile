ifndef GCCPREFIX
GCCPREFIX := x86_64-elf-
endif

AS		:= nasm
CC		:= $(GCCPREFIX)gcc
LD		:= $(GCCPREFIX)ld
OBJCOPY	:= $(GCCPREFIX)objcopy
CFLAGS	:= -Wall -m32 -fno-pie
QEMU	:= qemu-system-i386

OBJS	:= ipl.bin asmhead.bin bootpack.bin func.bin
SYS		:= titanic.sys
IMG		:= titanic.img

QEMU_FLAGS :=

ifdef DEBUG
QEMU_FLAGS += -gdb tcp::1234 -S
CFLAGS += -g
endif

ipl.bin:
	$(AS) -f bin ipl.asm -o ipl.bin -l ipl.lst

asmhead.bin:
	$(AS) -f elf asmhead.asm -o asmhead.bin -l asmhead.lst

bootpack.bin:
	$(CC) $(CFLAGS) -c bootpa