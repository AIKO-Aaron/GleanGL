#pragma once

#define CL_SILENCE_DEPRECATION
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#ifdef __APPLE__
#  include <OpenCL/OpenCL.h>
#  define RET_TYPE
#else
#  include <CL/cl.h>
#  define RET_TYPE __stdcall
#endif

#include <iostream>
#include "util/FileUtil.h"

extern void testCL();
