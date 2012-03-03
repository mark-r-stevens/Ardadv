
cd ..

rm -rf build

mkdir -p build/device
mkdir -p build/host

cd build/device
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ../../source/device
make -j 2

cd ../..
cd build/host
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE ../../source/host
make -j 2

cd ../../source

