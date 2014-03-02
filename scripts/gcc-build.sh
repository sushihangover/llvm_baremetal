pushd build/gcc\/$BUILD_TRIPLE
make -j 4 -l .75 all-gcc
popd

