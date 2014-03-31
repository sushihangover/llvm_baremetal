pushd build/qemu\/$BUILD_TRIPLE
CC='ccache clang -Qunused-arguments -fcolor-diagnostics'
make install
popd

