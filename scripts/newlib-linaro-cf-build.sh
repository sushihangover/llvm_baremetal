
mkdir -p build/newlib-linaro
pushd build/newlib-linaro
#    --disable-newlib-supplied-syscalls \
../../sources/newlib-linaro/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--target=$BUILD_TRIPLE \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--enable-interwork \
	--enable-multilib
popd

pushd build/newlib-linaro
make
popd

pushd build/newlib-linaro
make install
popd

