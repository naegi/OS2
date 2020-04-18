# ApropOS
## Introduction 

My simple os, created by my own, from scratch

It aims only x86 platforms. It is tested on qemu + bochs.

What I want is not a fully fonctional system but a way to learn more on PC architecture. 

## What I want to be working on my system

based on [OSDev's recommandations](http://wiki.osdev.org/What_order_should_I_make_things_in)

- [x] Working output system for logging on screen + helpers to show numbers in hex/dec/oct numbers (printf like interface)
- [x] Working output system through serial port for debugging.
- [x] Interupts handler + dumping all needed content (regs/stack frames/address default/other debugs things)
- [x] Kcall interface
- [ ] Malloc/free -> memory model flat with headers before used/unused block
- [ ]And more...

# Let's run it
## Prerequisites

- Need a working cross-compiler (CF http://wiki.osdev.org/GCC_Cross-Compiler)
-- I use now clang, it works out of the box with archlinux's one
- Qemu
- Bochs (and mtools on archlinux) 

## The toolchain

It's a Makefile
- make qemu -> launch kernel on qemu 
- make bochs -> launch kernel on bochs
- make clean -> remove the sysroot, .o, .kernel, .map...

## Tips 
- When you are on Ctrl+A then C to get the hand over the qemu monitor
- When changing a libk/libc/ component, do a make clean

## The sources

- **kernel** -> the sources of my kernel
- **libc** -> the sources of my custom libc

# A bit of documentation

## Kernel 

### arch/i386

Architecture (here i386 systems) dependant part of the kernel.

- console.h
  Everything that deals with output on screen (VGA) in text mode.
- gdt.h
  Initialize a proper GDT. 
- idt.h
  Initialize and allow to manage interrupts (irq + isr)
- irq.h 
  Initialize IRQs. 
  Use handlers and unmask to allow to catch an IRQ.
- isr.h 
  Initialize ISRs.
- serial.h
  Everything that deals with serial outputs/inputs (only COM1).
  Inputs don't really works.


### kernel/

Architecture independant part of the kernel.


## Libc 

I should adapt a newlib 

---------------
# References:
- A really good way to learn more and more -> [OSDev](http://wiki.osdev.org/)
- Intel Manuel (volume 2 & 3A mainly)-> [RTFM](https://software.intel.com/en-us/articles/intel-sdm)
