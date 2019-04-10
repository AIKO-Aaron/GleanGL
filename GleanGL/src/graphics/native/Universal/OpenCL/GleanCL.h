#pragma once

#define CL_SILENCE_DEPRECATION
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <OpenCL/OpenCL.h>
#include <iostream>
#include "util/FileUtil.h"

extern std::vector<cl_platform_id> getAllPlatforms();

extern void testCL();
