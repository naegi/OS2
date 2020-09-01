# OS 2 
A simple toy OS

## Requirements

Under Archlinux, you need to install:

- `clang` for compilation
- `qemu` and `qemu-arch-extra` to run `make qemu`
- `bochs`, `libisoburn` and `mtools` to run `make bochs`
- `gdb` to run `make qemu-gdb` or `make bochs-gdb`


## Toolchain

- `make` to build
- `make clean` to clean all build files
- `make bochs` build and run with bochs
- `make qemu` build and run with qemu without graphics (Ctrl-A,C q to exit)




## References:
- A really good way to learn more and more -> [OSDev](http://wiki.osdev.org/)
- Intel Manuel (volume 2 & 3A mainly)-> [RTFM](https://software.intel.com/en-us/articles/intel-sdm)
