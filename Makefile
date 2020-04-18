export OS_NAME = os

export HOST?=i686-elf
export HOSTARCH:=i386

export MK_RESCUE?=grub-mkrescue

export AR=ar
export CC=clang -target ${HOST} -march=i386


export PREFIX?=
export EXEC_PREFIX?=$(PREFIX)
export BOOTDIR?=$(EXEC_PREFIX)/boot
export INCLUDEDIR?=$(PREFIX)/include
export LIBDIR?=$(EXEC_PREFIX)/lib
export DESTDIR?=$(PWD)/sysroot

export CC+= --sysroot=$(DESTDIR)

export ASM=nasm
export ASFLAGS=-felf32

export CFLAGS_COMMON:=-g -Og\
    -std=gnu11 \
    -ffreestanding -fbuiltin -Werror\
    -I=$(INCLUDEDIR) \

export CPPFLAGS_COMMON:=
export LDFLAGS_COMMON:=
export LIBS_COMMON:=

QEMU=qemu-system-$(HOSTARCH)

QEMU_FLAGS_COMMON?= -kernel kernel/kernel.kernel  -nographic -serial mon:stdio

QEMU_FLAGS?=

QEMU_DEBUG_FLAGS?= -S -s -d guest_errors

BOCHS?=bochs
BOCHS_FLAGS?=-f boshrc

.PHONY: all bear clean install-all install install-headers qemu qemu-gdb bochs

all: install-all

install-all: install-headers install


install-headers:
	$(MAKE) -C libk install-headers
	$(MAKE) -C kernel install-headers
install:
	$(MAKE) -C libk install-libs
	$(MAKE) -C kernel install-kernel
clean:
	$(MAKE) -C libk clean
	$(MAKE) -C kernel clean
	rm -f $(OS_NAME).iso
	rm -rf $(DESTDIR)
	rm -rf isodir
	rm -f compile_commands.json

qemu: all
	$(QEMU) $(QEMU_FLAGS_COMMON) $(QEMU_FLAGS)

qemu-gdb: all
	$(QEMU) $(QEMU_FLAGS_COMMON) $(QEMU_DEBUG_FLAGS)

bochs: $(OS_NAME).iso
	$(BOCHS) $(BOCHS_FLAGS)

bear:
	bear make -B install-all

compile_command.json: bear

$(OS_NAME).iso: all
	mkdir -p isodir/boot/grub

	cp sysroot/boot/kernel.kernel isodir/boot/kernel.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(MK_RESCUE) -o $(OS_NAME).iso isodir
