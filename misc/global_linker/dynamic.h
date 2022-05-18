#pragma once

#include "static.h"
#include <string>

#if BUILD_WITH_STRUCT
extern Informer& globalGetter();
#else
extern std::string& globalGetter();
#endif