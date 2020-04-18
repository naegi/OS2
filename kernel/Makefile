CFLAGS:=$(CFLAGS_COMMON)
CPPFLAGS:=$(CPPFLAGS_COMMON)
LDFLAGS:=$(LDFLAGS_COMMON)
LIBS:=$(LIBS_COMMON)

ARCHDIR:=arch/$(HOSTARCH)

CFLAGS:=$(CFLAGS) -ffreestanding -Werror -Weverything
CPPFLAGS:=$(CPPFLAGS) -D__is_$(OS_NAME)_kernel -I$(DESTDIR)/$(INCLUDEDIR)
LDFLAGS:=$(LDFLAGS)  -Wl,-Map=kernel.map
LIBS:=$(LIBS) -nostdlib -lgcc -lk

include def.config

include $(ARCHDIR)/make.config
include kernel/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

OBJS:=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_COMMON_OBJS) \
kernel/kernel.o \

ALL_OUR_OBJS:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ) \

OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ) \

all: compile_command.json kernel

.PHONY: all clean install install-headers install-kernel

.kernel: $(OBJ_LINK_LIST) $(ARCHDIR)/linker.ld
ifndef BEAR
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)
	BEAR=yep $(MAKE) -C .. bear 
else
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)
endif

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS) $(CONF)

%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(ASM) $(ASFLAGS) $< -o $@

clean:
	rm -f kernel $(OBJS) $(ALL_OUR_OBJS) *.o */*.o */*/*.o

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)/kernel
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)/kernel
	cp -RTv $(ARCHDIR)/include $(DESTDIR)$(INCLUDEDIR)/kernel/$(HOSTARCH)

install-kernel: kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel $(DESTDIR)$(BOOTDIR)
