# Dot source from the root project directory
mkdir -p build/llvm

export TOOLCHAIN_DIR=`pwd`
export TOOLCHAIN_INSTALL=$TOOLCHAIN_DIR/install
export LLVM_TARGETS="ARM;AVR;X86"
export LLVM_TARGETS="ARM"
export CMSIS_VERSION="CMSIS-SP-00300-r3p1-00rel0"
export NEWLIB_VERSION=
# export BUILD_TRIPLE=avr
export BUILD_TRIPLE=arm-none-eabi

export CMSIS=$TOOLCHAIN_INSTALL/$BUILD_TRIPLE/CMSIS
export NEWLIB=$TOOLCHAIN_INSTALL/arm-none-eabi

export PATH=`pwd`/install/arm-none-eabi/bin:$PATH

