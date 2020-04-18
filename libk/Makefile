CFLAGS:=$(CFLAGS_COMMON)
CPPFLAGS:=$(CPPFLAGS_COMMON)

FREEOBJS:=\
$(ARCH_FREEOBJS)

include def.config

#include xxx/make.config

HOSTEDOBJS:=\
$(ARCH_HOSTEDOBJS) \

OBJS:=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

BINARIES=libk.a

all: $(BINARIES)

.PHONY: all clean install install-headers install-libs

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS) $(CONF)

%.o: %.asm
	$(ASM) $(ASFLAGS) -o $@ $< 

clean:
	rm -f $(BINARIES) $(OBJS) *.o */*.o */*/*.o

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)/libk
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)/libk

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)
