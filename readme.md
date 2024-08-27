# Titanic-OS RuneScape Edition

This project is based on OSASK and developed in a Linux or Mac environment. The fundamental aim is to familiarize ourselves with the principles of an Operating System by developing a miniature kernel and a graphical user interface. We also intend to add our own features and make continuous improvements.

## Development Environment

The project was initially developed on Mac OS 12 on aarch64, using the `x86_64-elf-toolchain` and `qemu` or `bochs` as the development board simulation.

Dependencies for Mac/Linux environment (recommended to use package management tools like brew for one-click installation):

```
brew install x86_64-elf-binutils
brew install x86_64-elf-gcc
brew install nasm
brew install mtools
brew install make
brew install qemu-system-i386
```

### Quick Execution

Navigate to the corresponding directory, and run `make qemu` to boot up.

```shell
cd day1
make qemu
```

#### Runtime Screenshot (day5)

## Finished Product  

![Screen](./pic/day5.png)