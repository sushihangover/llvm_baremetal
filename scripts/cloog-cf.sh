export POLLY_SRC=$TOOLCHAIN_DIR/sources/llvm/tools/polly
export CLOOG_SRC=$TOOLCHAIN_DIR/sources/cloog_src
export CLOOG_INSTALL=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE 
${POLLY_SRC}/utils/checkout_cloog.sh ${CLOOG_SRC}
mkdir -p build/cloog\/$BUILD_TRIPLE
pushd build/cloog\/$BUILD_TRIPLE
mkdir -p $TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
../../../sources/cloog_src/configure \
	--prefix=$TOOLCHAIN_INSTALL\/$BUILD_TRIPLE
make
make install
popd

