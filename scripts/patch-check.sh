pushd sources/llvm
find ../llvm-avr/llvm -name "*.diff" | xargs git apply --check
popd
