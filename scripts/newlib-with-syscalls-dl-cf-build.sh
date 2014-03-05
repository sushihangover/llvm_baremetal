
mkdir -p build/newlib-syscalls
pushd build/newlib-syscalls
#    --disable-newlib-supplied-syscalls \
../../sources/newlib-2.0.0/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE\/newlib-syscalls \
	--target=$BUILD_TRIPLE \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--disable-interwork \
	--enable-multilib
popd

pushd build/newlib-syscalls
make
popd

pushd build/newlib-syscalls
make install
popd

