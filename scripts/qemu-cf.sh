mkdir -p build/qemu\/$BUILD_TRIPLE
pushd build/qemu\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
# CC='ccache clang -Qunused-arguments -fcolor-diagnostics'
../../../sources/qemu/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE \
	--target-list=arm-softmmu \
	--disable-werror \
	--disable-strip \
	--enable-cocoa \
	--disable-bsd-user \
	--disable-guest-agent 
	# --enable-sdl \
	# --enable-debug
	# --enable-trace-backend=simple \
popd

