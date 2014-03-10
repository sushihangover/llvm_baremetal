LLVM Bare Metal for ARM and AVR
=================
GitHub Repo : https://github.com/sushihangover/llvm_baremetal

Blog : http://sushihangover.github.io/blog/categories/bare-metal/

This repository is a 'super project' that is based on gitslave and contains 'attached' git repositories and a build system for LLVM that targets ARM and AVR mcu/cores bare metal development.

Currently targeting arm-none-eabi and building on OS-X:
* llvm
* clang
* clang-tools-extra
* compiler-rt
* polly
* test-suite
* lld
* gcc (arm-none-eabi-g*)
* binutils (arm-none-eabi-*)
* gdb (arm-none-eabi-gdb)
* qemu (qemu-system-arm)
* ninja
* opendocd
* ARM CMSIS
* newlib 2.0

> This is a **bleeding-edge** toolchain and is not for the weak of heart.

Along for native host LLVM builds, the build process also supports [Canadian Cross](http://en.wikipedia.org/wiki/Canadian_cross#Canadian_Cross) :
* OS-X (x86_64)
* Linux (x86_64, ARM)
* Windows (x86_64)

TODO:
* Document install steps
* Document build system
* Intergration testing (via QEMU guests)

