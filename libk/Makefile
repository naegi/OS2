CFLAGS:=$(CFLAGS_COMMON)
CPPFLAGS:=$(CPPFLAGS_COMMON)

FREEOBJS:=\
$(ARCH_FREEOBJS)

include def.config

#include xxx/make.config

HOSTEDOBJS:=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

INCLUDES := $(shell find include -name '*.h')

all: libk.a

.PHONY: all clean install-headers install-libs todolist

todolist:
	@grep -nRi --color=always --include='*.c' --include='*.h' todo || :
	@grep -nRi --color=always --include='*.c' --include='*.h' fixme || :

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS) $(CONF)

%.o: %.asm
	$(ASM) $(ASFLAGS) -o $@ $< 

clean:
	rm -f libk.a $(OBJS)

install-headers: $(DESTDIR)$(INCLUDEDIR)/libk

$(DESTDIR)$(INCLUDEDIR)/libk: $(INCLUDES)
	mkdir -p $@
	cp -RTpv include $@
	touch $@

install-libs: $(DESTDIR)$(LIBDIR)/libk.a

$(DESTDIR)$(LIBDIR)/libk.a: libk.a
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp libk.a $@
