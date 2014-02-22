export BUILD_TRIPLE=arm-none-eabi
export LLVM_TARGETS=ARM
./scripts/binutils-cf.sh 
./scripts/binutils-build.sh 
./scripts/binutils-install.sh

export BUILD_TRIPLE=avr
export LLVM_TARGETS=AVR
./scripts/binutils-cf.sh 
./scripts/binutils-build.sh 
./scripts/binutils-install.sh


