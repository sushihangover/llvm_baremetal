mkdir -p build/binutils\/$BUILD_TRIPLE
pushd build/binutils\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/binutils/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--program-prefix=$BUILD_TRIPLE-\
	--target=$BUILD_TRIPLE \
	--enable-gold=no \
	--enable-ld=yes \
	--enable-interwork=yes \
	--enable-multilib \
	--enable-multibibi-no \
	--enable-nlsi=no \
	--enable-libssp=no \
	--enable-lto=yes \
	--enable-werror=no 
popd

