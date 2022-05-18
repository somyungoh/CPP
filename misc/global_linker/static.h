#pragma once

#include <iostream>
#include <string>

#ifndef BUILD_WITH_STRUCT
#   define BUILD_WITH_STRUCT   0
#endif

#if BUILD_WITH_STRUCT
extern struct Informer
{
    Informer() { std::cerr << "ctor " << this << "\n"; }
    ~Informer() { std::cerr << "dtor " << this << "\n"; }
    Informer* Get() { return this; }
} g_informer;
#else
extern std::string g_str;
#endif