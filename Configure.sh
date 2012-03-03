
cd ..

rm -rf build

mkdir -p build

cd build

cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DECLIPSE_CDT4_GENERATE_SOURCE_PROJECT=TRUE ../source

make -j 2

#eclipse &
