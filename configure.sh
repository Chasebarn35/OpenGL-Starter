git submodule update --init --recursive
cmake -DCMAKE_TOOLCHAIN_FILE=../cross-compliation.cmake -S . -B build
