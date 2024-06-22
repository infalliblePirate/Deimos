#ifndef ENGINE_DMPCH_H
#define ENGINE_DMPCH_H

#include "config.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
#include <memory>

#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Deimos/Core/Log.h"
#include "Deimos/Debug/Instrumentor.h"

#ifdef DM_PLATFORM_WINDOWS
    #include <Windows.h>
#elif DM_PLATFORM_LINUX
    // #include <unistd.h>
#endif

#endif //ENGINE_DMPCH_H
