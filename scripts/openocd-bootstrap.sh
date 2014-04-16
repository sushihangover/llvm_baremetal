mkdir -p build/openocd\/$BUILD_TRIPLE
pushd build/openocd\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
cd ../../../sources/openocd
./bootstrap
popd

