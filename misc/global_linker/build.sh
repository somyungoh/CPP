#!/bin/bash

echo "compiling static.cpp"
# Compile static translation unit
clang++ -std=c++14 -c -fpic static.cpp
# Produce a static library
ar rcs libstatic.a static.o

echo "compiling dynamic.cpp"
# Compile dynamic translation unit
clang++ -std=c++14 -c -fpic dynamic.cpp
# Produce dynamic library, linking against static
clang++ -shared -o libdynamic.so dynamic.o -L./ -lstatic

echo "compiling main.cpp"
# Compile main execuatble translation unit
clang++ -std=c++14 -c main.cpp
# Link executable against static and shared libraries
clang++ -L./ -Wl main.o -ldynamic -lstatic