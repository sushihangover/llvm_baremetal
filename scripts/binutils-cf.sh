mkdir -p build/binutils\/$BUILD_TRIPLE
pushd build/binutils\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/binutils/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--program-prefix=$BUILD_TRIPLE-\
	--target=$BUILD_TRIPLE \
	--enable-static \
	--disable-shared \
	--enable-gold=no \
	--enable-ld \
	--enable-interworks \
	--enable-multilib \
	--enable-nlsi=no \
	--enable-libssp=no \
	--enable-lto \
	--enable-werror=no 
popd

