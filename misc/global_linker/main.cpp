//
// This is following the talk from CppCon 2017
// "What C++ Developers should know about globals (and the linker)"
// https://www.youtube.com/watch?v=xVT1y0xWgww


#include "dynamic.h"
#include "static.h"

#include <iostream>

int main()
{
#if BUILD_WITH_STRUCT
    std::cerr << g_informer.Get() << "\n";
    std::cerr << globalGetter().Get() << "\n";
#else
    std::cerr << &g_str << "\n";
    std::cerr << &globalGetter() << "\n";
#endif

    return EXIT_SUCCESS; 
}