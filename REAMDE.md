You can use the following commands to install your dependencies and build them with cmake and ninja

conan install . -s build_type=Release --build=missing --output-folder=build
cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
ninja