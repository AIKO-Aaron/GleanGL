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
#include "math/GleanMath.h"

// extern void testCL();

extern void initCL();
extern unsigned char *testRay(Glean::math::Vector<4> cameraPos, Glean::math::Vector<2> cameraAngles);
