
mkdir -p build/newlib2
pushd build/newlib2
#    --disable-newlib-supplied-syscalls \
../../sources/newlib-2.0.0/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE\/newlib \
	--target=$BUILD_TRIPLE \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--enable-interwork \
	--enable-multilib \
	--disable-newlib-supplied-syscalls
popd

pushd build/newlib2
make
popd

pushd build/newlib2
make install
popd

