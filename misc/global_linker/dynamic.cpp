#include "dynamic.h"
#include "static.h"


#if BUILD_WITH_STRUCT
Informer& globalGetter()
{
    return g_informer;
}
#else
std::string& globalGetter()
{
    return g_str;
}
#endif