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
	--enable-multilib \
	--enable-languages="c,c++" \
        --with-newlib \
	--with-float=soft \
	--with-headers=../../../sources/newlib-2.0.0/newlib/libc/include 
popd

