
cd ..

rm -rf build

mkdir -p build

cd build

cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ../source

make -j 2

cd ../source

