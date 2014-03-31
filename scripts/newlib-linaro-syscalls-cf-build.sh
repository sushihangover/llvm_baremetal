#
export BUILDDIR=newlib-linaro-syscalls
#
mkdir -p build/$BUILDDIR
pushd build/$BUILDDIR
#
../../sources/newlib-linaro/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE\/$BUILDDIR \
	--target=$BUILD_TRIPLE \
	--disable-nls \
	--with-float=soft \
	--disable-werror \
	--disable-interwork \
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
