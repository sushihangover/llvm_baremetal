mkdir -p build/openocd\/$BUILD_TRIPLE
pushd build/openocd\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/openocd/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--program-prefix=$BUILD_TRIPLE- \
	--enable-static 
popd

