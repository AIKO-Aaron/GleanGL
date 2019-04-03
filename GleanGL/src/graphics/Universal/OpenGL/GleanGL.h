#pragma once

#include "glcorearb.h"
#include "glext.h"
#include "../Platform.h"

#include <stdio.h>

#ifdef __APPLE__
#  define INIT_FUNC(funcname) funcname = (typeof(funcname)) Glean::library::getGLFunction(#funcname)
#else
#  define INIT_FUNC(funcname) funcname = (decltype(funcname)) Glean::library::getGLFunction(#funcname)
#endif

#include "../../../../../Scripts/autogen_header.h"
