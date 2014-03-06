mkdir -p build/qemu\/$BUILD_TRIPLE
pushd build/qemu\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/qemu/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--target-list=arm-softmmu \
	--disable-werror \
	--disable-strip \
	--disable-sdl \
	--enable-cocoa \
	--disable-bsd-user \
	--disable-guest-agent


popd

