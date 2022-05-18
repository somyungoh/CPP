#!/bin/bash

# Compile static translation unit
clang++ -std=c++14 -c -fpic static.cpp
# Produce a static library
ar rcs libstatic.a static.o

# Compile dynamic translation unit
clang++ -std=c++14 -c -fpic dynamic.cpp
# Produce dynamic library, linking against static
clang++ -shared -o libdynamic.so dynamic.o -L./ -lstatic

# Compile main execuatble translation unit
clang++ -std=c++14 -c main.cpp
# Link executable against static and shared libraries
clang++ -L./ -Wl main.o -lstatic -ldynamic