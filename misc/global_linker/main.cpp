//
// This is following the talk from CppCon 2017
// "What C++ Developers should know about globals (and the linker)"
// https://www.youtube.com/watch?v=xVT1y0xWgww
//
//
//  Problem:
//      ctor / dtor gets called multiple times on the global variable
//  Why:
//      static, dynamic libs produce different asm code, and the final executable will
//      depend on which on you LINK FIRST. You can check the asm by using:
//      $ objdump -CS [file]
//  Lazy Solution:
//      1. Don't mix static / dynamic libraries     <- not practical
//      2. Only write globals in shared libraies    <- not practical
//      3. Change the link order                    <- hard to come up with
//  Robust Solution:
//      use "inline" global variable, then it will always get the unique instance.
//



#include "dynamic.h"
#include "static.h"

#include <iostream>

int main()
{
#if BUILD_WITH_STRUCT
    std::cerr << g_informer.Get() << "\n";
    std::cerr << globalGetter().Get() << "\n";
#else
    std::cerr << g_str << "\n";
    std::cerr << globalGetter() << "\n";
#endif

    return EXIT_SUCCESS; 
}