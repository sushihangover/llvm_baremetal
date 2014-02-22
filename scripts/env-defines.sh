# Dot source from the root project directory
mkdir -p build/llvm

export TOOLCHAIN_DIR=`pwd`
export TOOLCHAIN_INSTALL=$TOOLCHAIN_DIR/install
export LLVM_TARGETS="ARM;AVR;X86"

export BUILD_TRIPLE=avr
export BUILD_TRIPLE=arm-none-eabi
