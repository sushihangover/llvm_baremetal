# using ccache causing build to fail(?)
pushd build/openocd\/$BUILD_TRIPLE
make -j 4 -l .75
popd

