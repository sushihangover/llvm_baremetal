#
export BUILDDIR=newlib-linaro-nosyscalls
#
mkdir -p build/$BUILDDIR
pushd build/$BUILDDIR
#
../../sources/newlib-linaro/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE\/newlib-linaro-no-syscalls \
	--target=$BUILD_TRIPLE \
	--disable-newlib-supplied-syscalls \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--enable-interwork \
	--enable-multilib
#
popd
#
pushd build/$BUILDDIR
make -j 3 -l .75
popd
#
pushd build/$BUILDDIR
make install
popd
#
