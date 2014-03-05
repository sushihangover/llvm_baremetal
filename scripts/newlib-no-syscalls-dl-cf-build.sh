
mkdir -p build/newlib-nosyscalls
pushd build/newlib-nosyscalls
#    --disable-newlib-supplied-syscalls \
../../sources/newlib-2.0.0/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE\/newlib-nosyscalls \
	--target=$BUILD_TRIPLE \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--enable-interwork \
	--enable-multilib \
	--disable-newlib-supplied-syscalls 
popd

pushd build/newlib-nosyscalls
make
popd

pushd build/newlib-nosyscalls
make install
popd

