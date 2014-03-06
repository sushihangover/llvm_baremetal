pushd build/qemu\/$BUILD_TRIPLE
make -j 4 -l .75 all
popd

