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

SRCFILES := $(KERNEL_ARCH_SRC) \
	    $(KERNEL_COMMON_SRC)
ASMFILES := $(KERNEL_ARCH_ASM)

DEPFILES := $(patsubst %.c,%.c.d,$(SRCFILES))
OBJS :=  $(patsubst %.asm,%.asm.o,$(ASMFILES)) $(patsubst %.c,%.c.o,$(SRCFILES)) 
CRTI_OBJ := $(CRTI).o
CRTN_OBJ := $(CRTN).o

ALL_OUR_OBJS:=\
$(CRTI_OBJ) \
$(OBJS) \
$(CRTN_OBJ)

OBJ_LINK_LIST:=\
$(CRTI_OBJ) \
$(CRTBEGIN_OBJ) \
$(OBJS) \
$(CRTEND_OBJ) \
$(CRTN_OBJ)

INCLUDES := $(shell find include -name '*.h' ) $(shell find $(ARCHDIR)/include)

all: kernel

.PHONY: all clean install-headers install-kernel

kernel.kernel: $(OBJ_LINK_LIST) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)

%.c.o: %.c Makefile
	$(CC) -c $< -o $@ -std=gnu11 -MMD $(CFLAGS) $(CPPFLAGS) $(CONF) 

%.asm.o: %.asm Makefile
	$(ASM) $(ASFLAGS) $< -o $@

%.asm: # Cancel implicit rule

clean:
	rm -f kernel.kernel $(OBJS) $(ALL_OUR_OBJS) $(DEPFILES)

install-headers: $(DESTDIR)$(INCLUDEDIR)/kernel

$(DESTDIR)$(INCLUDEDIR)/kernel: $(INCLUDES)
	mkdir -p $(DESTDIR)$(INCLUDEDIR)/kernel
	cp -RTpv include $@
	cp -RTpv $(ARCHDIR)/include $@/$(HOSTARCH)
	touch $@ # Update timestamps

install-kernel: $(DESTDIR)$(BOOTDIR)/kernel.kernel

$(DESTDIR)$(BOOTDIR)/kernel.kernel: kernel.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel.kernel $(DESTDIR)$(BOOTDIR)

-include $(DEPFILES)
