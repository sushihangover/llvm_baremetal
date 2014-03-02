pushd sources/gcc
autogen
popd
mkdir -p build/gcc\/$BUILD_TRIPLE
pushd build/gcc\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/gcc/configure \
	--target=$BUILD_TRIPLE \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--enable-interwork \
	--enable-multilibi \
	--enable-languages="c,c++" \
        --with-newlib \
	--with-headers=../../../sources/newlib-1.18.0/newlib/libc/include 
popd

