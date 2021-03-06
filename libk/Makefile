CFLAGS:=$(CFLAGS_COMMON)
CPPFLAGS:=$(CPPFLAGS_COMMON)

PWD = $(shell pwd)

include def.config

include io/make.config
include logging/make.config
include utils/make.config
include string/make.config

HOSTEDOBJS:=\
    $(ARCH_HOSTEDOBJS) \

SRCFILES := $(LIBK_SRC)
ASMFILES := $(LIBK_ASM)

DEPFILES := $(patsubst %.c,%.c.d,$(SRCFILES))
OBJS :=  $(patsubst %.asm,%.asm.o,$(ASMFILES)) $(patsubst %.c,%.c.o,$(SRCFILES)) 


INCLUDES := $(shell find include -name '*.h')

all: libk.a

.PHONY: all clean install-headers install-libs todolist

todolist:
	@grep -nRi --color=always --include='*.c' --include='*.h' todo || :
	@grep -nRi --color=always --include='*.c' --include='*.h' fixme || :

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.c.o: %.c Makefile
	$(CC) -c $< -o $@ -MMD -std=gnu11 $(CFLAGS) $(CONF)
 
%.asm.o: %.asm Makefile
	$(ASM) $(ASFLAGS) $< -o $@

%.asm: # Cancel implicit rule


clean:
	rm -f libk.a $(OBJS) $(DEPFILES)

install-headers: $(DESTDIR)$(INCLUDEDIR)/libk

$(DESTDIR)$(INCLUDEDIR)/libk: $(INCLUDES)
	mkdir -p $@
	cp -sRTpv $(PWD)/include $@ || true
	touch $@

install-libs: $(DESTDIR)$(LIBDIR)/libk.a

$(DESTDIR)$(LIBDIR)/libk.a: libk.a
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp libk.a $@

-include $(DEPFILES)
