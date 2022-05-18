#include "static.h"
#include <iostream>

#if BUILD_WITH_STRUCT
struct Informer g_informer;
#else
std::string g_str = "string too long for short string"
                    "optimization";
#endif