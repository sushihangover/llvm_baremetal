mkdir -p build/gdb\/$BUILD_TRIPLE
pushd build/gdb\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/gdb/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--program-prefix=$BUILD_TRIPLE-\
	--target=$BUILD_TRIPLE \
	--enable-interwork=yes \
	--enable-multilib \
	--enable-werror=no 
popd

